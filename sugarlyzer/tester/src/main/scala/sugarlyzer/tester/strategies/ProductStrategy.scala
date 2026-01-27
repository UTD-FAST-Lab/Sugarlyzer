package sugarlyzer.tester.strategies

import cats.effect.IO
import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.models.*
import sugarlyzer.common.Config.AppConfig
import cats.effect.syntax.all._
import os._
import sugarlyzer.tester.tools.Alarm
import scala.util.Using

object ProductStrategy extends AnalysisStrategy {

  def analyze(
      appConfig: AppConfig,
      spec: ProgramSpecification,
      tool: AnalysisTool
  ): IO[List[Alarm]] = {
    IO.println(s"Running analysis for ${spec.name}")

    (0 until appConfig.sampleSize).toList.parTraverseN(appConfig.jobs) { i =>
      val iterDir = os.Path(appConfig.sharedPath) / s"$i" / spec.rootDir

      for {
        _      <- IO.println(s"Running analysis for sample $i")
        alarms <- tool.run(spec.copy(rootDir = iterDir.toString))

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
        _ <- runBuild(iterDir, spec, i)
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
  ): IO[Unit] = IO.blocking {
    val destConfigFile = iterDir / os.RelPath(spec.configFileLocation)

    if (!os.exists(destConfigFile / os.up)) {
      throw new RuntimeException(
        s"Parent directory for config does not exist: ${destConfigFile / os.up}"
      )
    }

    val configResource = s"programs/${spec.name}/configs/$i.config"
    val stream = getClass.getClassLoader.getResourceAsStream(configResource)

    if (stream == null) {
      throw new RuntimeException(s"Missing resource config: $configResource")
    }

    Using.resource(stream) { s =>
      os.write.over(destConfigFile, s)
    }
  }

  private def runBuild(
      iterDir: os.Path,
      spec: ProgramSpecification,
      sampleId: Int
  ): IO[Unit] = IO.blocking {
    val workingDir = iterDir / spec.rootDir

    val configResult = os.proc("sh", "-c", "yes | make oldconfig")
      .call(cwd = workingDir, check = false)

    if (configResult.exitCode != 0) {
      throw new RuntimeException(
        s"Build config failed for sample $sampleId. Code: ${configResult.exitCode}"
      )
    }

    val bearResult = os.proc("bear", "make")
      .call(cwd = workingDir, check = false)

    if (bearResult.exitCode != 0) {
      throw new RuntimeException(
        s"Bear make failed for sample $sampleId. Code: ${bearResult.exitCode}"
      )
    }
  }
}
