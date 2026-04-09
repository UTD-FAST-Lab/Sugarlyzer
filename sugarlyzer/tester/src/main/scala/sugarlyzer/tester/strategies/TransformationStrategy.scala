package sugarlyzer.tester.strategies

import os._
import cats.effect.IO
import cats.effect.syntax.all._
import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.tester.tools.TransformationAlarm
import sugarlyzer.common.Config.AppConfig
import sugarlyzer.models.*
import io.circe.generic.auto.*
import io.circe.syntax.*
import sugarlyzer.models.Configurator
import sugarlyzer.tester.parsing.CompileCommand
import sugarlyzer.tester.parsing.CompileCommands
import sugarlyzer.tester.sugarc.SugarCRunner.desugarFile
import sugarlyzer.tester.sugarc.SugarCRunner

object TransformationStrategy extends AnalysisStrategy {
  type Alarm = TransformationAlarm

  def sanitizeDescription(description: String): String = {
    val pattern = """__(.*)_(?:\d*)""".r
    pattern.replaceAllIn(description, m => m.group(1))
  }
  def analyze(
      appConfig: AppConfig,
      spec: ProgramSpecification,
      tool: AnalysisTool
  ): IO[List[TransformationAlarm]] = {
    given AppConfig = appConfig
    println(s"Running analysis for ${spec.name}")
    val workingDir = os.Path(appConfig.sharedPath) / os.RelPath(spec.rootDir)
    for {
      rawFindings <- tool.run(spec.copy(rootDir = workingDir.toString))
      telemetryMap <- IO.blocking {
        val telemetryPath = workingDir / "desugar_telemetry.json"
        if (os.exists(telemetryPath))
          io.circe.parser.decode[Map[
            String,
            Double
          ]](os.read(telemetryPath)).getOrElse(Map.empty)
        else Map.empty[String, Double]
      }
      _ <- IO.println("Telemetry map: " + telemetryMap.toString)
      alarms <- IO.blocking {
        rawFindings.map { finding =>
          val absoluteFilePath = workingDir / os.RelPath(finding.fileLocation)

          val model = SugarCRunner.findPresenceCondition(
            finding,
            absoluteFilePath
          )

          val time = telemetryMap.getOrElse(
            absoluteFilePath.toString,
            0.0
          )

          println(s"Time for $absoluteFilePath: $time")

          TransformationAlarm(
            finding = finding,
            sanitizedDescription = sanitizeDescription(finding.description),
            lineInputFile = 0,
            presenceCondition = model,
            model = model.getModel,
            feasible = model.isSatisfiable,
            desugaringTime = time
          )
        }
      }
      _ <- IO.println("Alarms: " + alarms.map(_.toString).mkString("\n"))
    } yield (alarms.filter(_.feasible))
  }

  def build(appConfig: AppConfig, spec: ProgramSpecification): IO[Unit] = {
    for {
      _           <- IO.println("Preparing to build...")
      _           <- Configurator.stageAndBuild(appConfig, spec)
      compileCmds <- getCompileCommands(appConfig, spec)
      contexts = compileCmds.map(CompileCommands.extractContext)
      timingsIO <- contexts.parTraverseN(appConfig.jobs) { ctx =>
        val logFilePath = ctx.file / os.up / s"${ctx.file.last}.log"
        val operation = desugarFile(
          fileToDesugar = ctx.file,
          logFile = logFilePath,
          includedFiles = ctx.incFiles ++ List(
            os.root / "SugarlyzerConfig" / "baseInc.h",
            os.root / "SugarlyzerConfig" / s"${spec.name}Inc.h",
            os.root / "SugarlyzerConfig" / s"${spec.name}Config.h"
          ),
          includedDirectories = ctx.incDirs ++ List(
            os.root / "SugarlyzerConfig",
            os.root / "SugarlyzerConfig" / "stdinc" / "usr" / "include",
            os.root / "SugarlyzerConfig" / "stdinc" / "usr" / "include" / "x86_64-linux-gnu",
            os.root / "SugarlyzerConfig" / "stdinc" / "usr" / "lib" / "gcc" / "x86_64-linux-gnu" / "9" / "include"
          ),
          commandLineDeclarations = ctx.cmdLineDefs,
          restrict = spec.name.toLowerCase() == "busybox"
        )

        operation.timed.map { case (duration, _) =>
          ctx.file.toString -> duration.toMillis.toDouble
        }
      }
      _ <- IO.blocking {
        val timingsMap = timingsIO.toMap
        val workingDir =
          os.Path(appConfig.sharedPath) / os.RelPath(spec.rootDir)
        val telemetryPath = workingDir / "desugar_telemetry.json"
        os.write.over(telemetryPath, timingsMap.asJson.spaces2)
      }
      _ <- IO.blocking {
        val updatedCmds = compileCmds.map { cmd =>
          val desugaredFile =
            cmd.file.replaceFirst("\\.[a-zA-Z0-9]+$", ".desugared.c")
          val updatedArgs =
            cmd.arguments.map(_.replace(cmd.file, desugaredFile))
          cmd.copy(file = desugaredFile, arguments = updatedArgs)
        }
        val workingDir =
          os.Path(appConfig.sharedPath) / os.RelPath(spec.rootDir)
        val jsonPath = workingDir / "compile_commands.json"
        os.write.over(jsonPath, updatedCmds.asJson.spaces2)
      }
    } yield ()
  }

  def getCompileCommands(
      appConfig: AppConfig,
      spec: ProgramSpecification
  ): IO[List[CompileCommand]] = {
    IO.blocking {
      val workingDir = os.Path(appConfig.sharedPath) / os.RelPath(spec.rootDir)

      os.proc("make", "clean")
        .call(
          cwd = workingDir,
          check = false,
          stdout = os.Inherit,
          stderr = os.Inherit
        ): Unit

      os.proc("make", "oldconfig")
        .call(
          cwd = workingDir,
          check = false,
          stdout = os.Inherit,
          stderr = os.Inherit
        ): Unit

      os.proc("bear", "make")
        .call(
          cwd = workingDir,
          check = false,
          stdout = os.Inherit,
          stderr = os.Inherit
        ): Unit

      val jsonPath = workingDir / "compile_commands.json"
      if (!os.exists(jsonPath) || os.size(jsonPath) < 50)
        throw new RuntimeException(
          s"Bear failed to generate a valid compile_commands.json file"
        )

      jsonPath
    }.flatMap(jsonPath => CompileCommands.parse(jsonPath))
  }

  def deduplicate(alarms: List[TransformationAlarm])
      : List[TransformationAlarm] = {
    alarms.groupBy(al =>
      (
        al.sanitizedDescription,
        al.lineInputFile,
        al.finding.fileLocation,
        al.finding.alarmType
      )
    ).values.flatMap(groupedAlarms =>
      List(groupedAlarms.reduce((a, b) =>
        a.copy(presenceCondition = a.presenceCondition.||(b.presenceCondition))
      ))
    ).toList
  }

  def exportAlarms(alarms: List[Alarm]): IO[Unit] = IO.blocking {
    val destPath = os.Path("/results")
    if (!os.exists(destPath)) os.makeDir.all(destPath)
    val targetFile = destPath / "results.json"
    os.write.over(targetFile, alarms.asJson.spaces2, createFolders = true)
  }
}
