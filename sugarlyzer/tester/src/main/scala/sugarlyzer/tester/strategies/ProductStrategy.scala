package sugarlyzer.tester.strategies

import os._
import cats.effect.IO
import cats.effect.syntax.all._
import cats.effect.kernel.Resource
import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.tester.tools.ProductAlarm
import sugarlyzer.common.Config.AppConfig
import sugarlyzer.common.Config.Tool
import sugarlyzer.models.*
import scala.util.Using
import scala.io.Source
import io.circe.generic.auto.*
import io.circe.syntax.*
import org.eclipse.cdt.core.dom.ast.gnu.c.GCCLanguage
import org.eclipse.cdt.core.parser.FileContent
import org.eclipse.cdt.core.parser.ScannerInfo
import org.eclipse.cdt.core.parser.DefaultLogService
import org.eclipse.cdt.core.parser.IncludeFileContentProvider
import org.eclipse.cdt.core.model.ILanguage
import com.typesafe.scalalogging.Logger

object ProductStrategy extends AnalysisStrategy {
  val logger = Logger[ProductStrategy.type]

  type Alarm = ProductAlarm

  def analyze(
      appConfig: AppConfig,
      spec: ProgramSpecification,
      tool: AnalysisTool
  ): IO[List[ProductAlarm]] = {
    given AppConfig = appConfig
    println(s"Running analysis for ${spec.name}")
    if spec.name == "varbugs" then {
      val sharedPath = os.Path(appConfig.sharedPath)
      val sourceDir  = sharedPath / spec.rootDir

      for {
        // Each config is paired with the specific file it was derived from
        fileConfigs <- IO.blocking {
          os.walk(sourceDir)
            .filter(_.ext == "c")
            .toList
            .flatMap(f => exhaustivelySample(f).map(config => (f, config)))
        }
        results <- fileConfigs.zipWithIndex.parTraverseN(appConfig.jobs) {
          case ((file, macroSet), i) =>
            val iterDir = sharedPath / s"$i"
            val model = macroSet.toList.map { flag =>
              if flag.startsWith("-D") then (flag.drop(2), "true")
              else (flag.drop(2), "false")
            }
            for {
              _ <- IO.println(
                s"Running exhaustive varbugs analysis for config $i (${file.last})"
              )
              rawFindings <- tool.run(spec.copy(rootDir = iterDir.toString))
            } yield rawFindings.map { finding =>
              ProductAlarm(
                finding = finding,
                configFiles = List.empty,
                model = model,
                numConfigs = List(model.length)
              )
            }
        }
      } yield results.flatten
    } else {
      (0 until appConfig.sampleSize).toList.parTraverseN(appConfig.jobs) { i =>
        val iterDir    = os.Path(appConfig.sharedPath) / s"$i" / spec.rootDir
        val configFile = s"$i.config"
        for {
          _           <- IO.println(s"Running analysis for sample $i")
          rawFindings <- tool.run(spec.copy(rootDir = iterDir.toString))
          model <- IO.blocking {
            val configResourcePath =
              s"programs/${spec.name}/configs/$configFile"
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
                finding = finding.copy(fileLocation =
                  finding.fileLocation.replaceAll(s"/workspace/$i/", "")
                ),
                configFiles = List[String](configFile),
                model = model,
                numConfigs = List[Int](model.length)
              )
            }
          }

        } yield (alarms)
      }.map(_.flatten)
    }
  }

  def build(appConfig: AppConfig, spec: ProgramSpecification): IO[Unit] = for {
    _ <- IO.println("Preparing to build...")
    _ <- {
      if (!spec.configFileLocation.isEmpty) {
        Configurator.stageAndBuild(appConfig, spec)
      } else {
        Configurator.stage(appConfig, spec)
      }
    }
    _ <- prepareAndBuildSamples(appConfig, spec)
  } yield ()

  /** Given a file, outputs all potential binary combinations of macros defined in the file
    */
  private[tester] def exhaustivelySample(file: os.Path)
      : Set[Set[String]] = {
    // Extension to take the cartesian product of a list of lists
    extension [A](lists: List[List[A]]) {
      def cartesian: List[List[A]] =
        lists match {
          case Nil => List(Nil)
          case head :: tail =>
            for {
              x  <- head
              xs <- tail.cartesian
            } yield x :: xs
        }
    }

    // Read in the file content, set up eclipse CDT stuff
    val fileContent =
      FileContent.create(file.baseName, os.read(file).toCharArray())
    val scanInfo      = ScannerInfo(java.util.HashMap(), Array[String]())
    val parserLog     = DefaultLogService()
    val emptyIncludes = IncludeFileContentProvider.getEmptyFilesProvider()

    // Parse the code
    val translationUnit =
      GCCLanguage.getDefault().getASTTranslationUnit(
        fileContent,
        scanInfo,
        emptyIncludes,
        null,
        ILanguage.OPTION_IS_SOURCE_UNIT,
        parserLog
      )

    // Get the preprocessor statements
    val preprocessorStatements = translationUnit.getAllPreprocessorStatements()

    // Get the macros, by checking for anything that includes #if
    val definedPattern = """!?defined\((.*)\)""".r
    val macros =
      preprocessorStatements.map(m => m.getRawSignature()).filter(p =>
        p.toLowerCase().contains("#if")
      ).map(s => s.split(" ")(1)).map(s =>
        s match {
          case definedPattern(mac) => mac
          case _                   => s
        }
      ).map(s => s.stripPrefix("(").stripSuffix(")"))

    logger.debug(s"Macros are ${macros}")

    // Pair with -U and -D
    val macroSets = macros.map(m =>
      List("-U", "-D").map(pref => s"${pref}${m}")
    ).toList

    // Take the cartesian product
    macroSets.cartesian.map(a => a.toSet).toSet
  }

  private def prepareAndBuildSamples(
      appConfig: AppConfig,
      spec: ProgramSpecification
  ): IO[Unit] = {
    val sharedPath   = os.Path(appConfig.sharedPath)
    val masterSource = sharedPath / spec.rootDir

    if (spec.configFileLocation == "") {
      for {
        _ <- IO.println("Exhaustively sampling configurations from source.")
        fileConfigs <- IO.blocking {
          os.walk(masterSource)
            .filter(_.ext == "c")
            .toList
            .flatMap(f => exhaustivelySample(f).map(config => (f, config)))
        }
        _ <- fileConfigs.zipWithIndex.parTraverseN(appConfig.jobs) {
          case ((file, macroSet), i) =>
            IO.blocking {
              val iterDir = sharedPath / s"$i"
              if (os.exists(iterDir)) os.remove.all(iterDir)
              os.makeDir.all(iterDir)
              writeCompileCommands(iterDir, file, macroSet.toList)
            } *> IO.println(
              s"Finished preparing varbugs config $i (${file.last})."
            )
        }
      } yield ()
    } else {
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

  private def writeCompileCommands(
      iterDir: os.Path,
      sourceFile: os.Path,
      macroFlags: List[String]
  ): Unit = {
    val path    = sourceFile.toString
    val command = s"cc -c $path ${macroFlags.mkString(" ")}"
    val args    = command.split(" ").map(f => s"\"$f\"").mkString(", ")
    val json =
      s"""[{"directory":"$iterDir","file":"$path","command":"$command","arguments":[$args]}]"""
    os.write.over(iterDir / "compile_commands.json", json)
  }

  private def runBuild(
      sampleId: Int,
      spec: ProgramSpecification,
      iterDir: os.Path,
      config: AppConfig
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

  def exportAlarms(alarms: List[Alarm]): IO[Unit] = IO.blocking {
    val destPath = os.Path("/results")
    if (!os.exists(destPath)) os.makeDir.all(destPath)
    val targetFile = destPath / "results.json"
    os.write.over(targetFile, alarms.asJson.spaces2, createFolders = true)
  }
}
