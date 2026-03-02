package sugarlyzer.tester.strategies

import cats.effect.IO
import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.models.*
import sugarlyzer.common.Config.AppConfig
import cats.effect.syntax.all._
import os._
import sugarlyzer.tester.tools.ProductAlarm
import sugarlyzer.common.Config
import cats.effect.kernel.Resource
import sugarlyzer.common.Config.Tool
import scala.util.Using
import scala.io.Source

object ProductStrategy extends AnalysisStrategy {
  type Alarm = ProductAlarm

  def analyze(
      appConfig: AppConfig,
      spec: ProgramSpecification,
      tool: AnalysisTool
  ): IO[List[ProductAlarm]] = {
    println(s"Running analysis for ${spec.name}")

    (0 until appConfig.sampleSize).toList.parTraverseN(appConfig.jobs) { i =>
      val iterDir    = os.Path(appConfig.sharedPath) / s"$i" / spec.rootDir
      val configFile = s"$i.config"
      for {
        _           <- IO.println(s"Running analysis for sample $i")
        rawFindings <- tool.run(spec.copy(rootDir = iterDir.toString))
        model <- IO.blocking {
          val configResourcePath = s"programs/${spec.name}/configs/$configFile"
          Using.resource(Source.fromResource(configResourcePath)) { source =>
            source.getLines()
              .map(_.trim)
              .filter(_.nonEmpty)
              .map { line =>
                if (line.startsWith("#")) {
                  val key = line.substring(1).trim.split(" ").head
                  (key, "false")
                } else {
                  val toks = line.split("=", 2)
                  (toks(0).trim, toks(1).trim)
                }
              }.toList
          }
        }
        alarms <- IO.blocking {
          rawFindings.map { finding =>
            ProductAlarm(
              finding = finding,
              configFiles = List[String](configFile),
              model = model,
              numConfigs = List[Int](model.length)
            )
          }
        }

      } yield (alarms)
    }.map(_.flatten)
  }

  def build(appConfig: AppConfig, spec: ProgramSpecification): IO[Unit] = for {
    _ <- IO.println("Preparing to build...")
    _ <- Configurator.stageAndBuild(appConfig, spec)
    _ <- prepareAndBuildSamples(appConfig, spec)
  } yield ()

  private def prepareAndBuildSamples(
      appConfig: AppConfig,
      spec: ProgramSpecification
  ): IO[Unit] = {
    val sharedPath   = os.Path(appConfig.sharedPath)
    val masterSource = sharedPath / spec.rootDir

    (0 until appConfig.sampleSize).toList.parTraverseN(appConfig.jobs) { i =>
      val iterDir   = sharedPath / s"$i"
      val finalDest = iterDir / masterSource.last

      for {
        _ <- setupWorkspace(iterDir, masterSource, finalDest)
        _ <- injectConfig(i, spec, iterDir)
        _ <- runBuild(i, spec, iterDir, appConfig)
        _ <- IO.println(s"Finished preparing sample $i.")
      } yield ()
    }.void
  }

  private def setupWorkspace(
      iterDir: os.Path,
      masterSource: os.Path,
      finalDest: os.Path
  ): IO[Unit] = IO.blocking {
    if (os.exists(iterDir)) os.remove.all(iterDir)
    os.makeDir.all(iterDir)
    os.copy(masterSource, finalDest)
  }

  private def injectConfig(
      i: Int,
      spec: ProgramSpecification,
      iterDir: os.Path
  ): IO[Unit] = {
    val destConfigFile = iterDir / os.RelPath(spec.configFileLocation)
    val configResource = s"programs/${spec.name}/configs/$i.config"

    Resource.fromAutoCloseable(
      IO(getClass.getClassLoader.getResourceAsStream(configResource))
    ).use { stream =>
      IO.raiseWhen(stream == null)(
        new RuntimeException(s"Missing resource: $configResource")
      ) *>
        IO.blocking(os.write.over(destConfigFile, stream))
    }
  }

  private def runBuild(
      sampleId: Int,
      spec: ProgramSpecification,
      iterDir: os.Path,
      config: Config.AppConfig
  ): IO[Unit] = IO.blocking {
    val workingDir = iterDir / spec.rootDir

    os.proc("make", "clean")
      .call(
        cwd = workingDir,
        check = false,
        stdout = os.Inherit,
        stderr = os.Inherit
      ): Unit

    val configResult = os.proc("sh", "-c", "yes | make oldconfig")
      .call(
        cwd = workingDir,
        check = false,
        stdout = os.Inherit,
        stderr = os.Inherit
      )

    if (configResult.exitCode != 0) {
      throw new RuntimeException(
        s"Build config failed for sample $sampleId. Code: ${configResult.exitCode}"
      )
    }

    // If the tool we are using is phasar we need to use wllvm
    if (config.tool == Tool.PHASAR) {
      val proc = os.proc("make", "CC=wllvm")
        .call(
          cwd = workingDir,
          stdout = os.Inherit,
          mergeErrIntoOut = true,
          env = Map(
            "CFLAGS"   -> "-g -Wignored-optimization-argument",
            "CXXFLAGS" -> "-g -Wignored-optimization-argument"
          )
        )
      if (proc.exitCode != 0)
        println(s"WLLVM Build failed: ${proc.err.text()}")
    } else {
      val proc = os.proc("bear", "make")
        .call(
          cwd = workingDir,
          check = false,
          stdout = os.Inherit,
          stderr = os.Inherit
        )
      if (proc.exitCode != 0)
        throw new RuntimeException(s"Bear Build failed: ${proc.err.text()}")

      val jsonPath = workingDir / "compile_commands.json"
      if (!os.exists(jsonPath) || os.size(jsonPath) < 50)
        throw new RuntimeException(
          s"Bear failed to generate a valid compile_commands.json for sample $sampleId"
        )
    }

  }

  def deduplicate(alarms: List[ProductAlarm]): List[ProductAlarm] = {
    alarms
      .groupBy(a =>
        (
          a.finding.fileLocation,
          a.finding.line,
          a.finding.alarmType,
          a.finding.description
        )
      )
      .values
      .map { groupedAlarms =>
        groupedAlarms.reduceLeft { (acc, curr) =>
          val model = acc.model.toSet.intersect(curr.model.toSet).toList
          acc.copy(
            configFiles = (acc.configFiles ++ curr.configFiles).distinct,
            model = model,
            numConfigs = (acc.numConfigs :+ model.length)
          )
        }
      }
      .toList
  }
}
