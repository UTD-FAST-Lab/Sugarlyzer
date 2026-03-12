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

  def analyze(
      appConfig: AppConfig,
      spec: ProgramSpecification,
      tool: AnalysisTool
  ): IO[List[TransformationAlarm]] = {
    println(s"Running analysis for ${spec.name}")
    val workingDir = os.Path(appConfig.sharedPath) / os.RelPath(spec.rootDir)
    for {
      rawFindings <- tool.run(spec.copy(rootDir = workingDir.toString))
      alarms <- IO.blocking {
        rawFindings.map { finding =>
          TransformationAlarm(
            finding = finding,
            sanitizedDescription = "",
            lineInputFile = 0,
            presenceCondition =
              SugarCRunner.findPresenceCondition(
                finding,
                os.Path(finding.fileLocation)
              ).toString(),
            model = "",
            feasible = false,
            desugaringTime = 0.0
          )
        }
      }
    } yield (alarms)
  }

  def build(appConfig: AppConfig, spec: ProgramSpecification): IO[Unit] = {
    for {
      _           <- IO.println("Preparing to build...")
      _           <- Configurator.stageAndBuild(appConfig, spec)
      compileCmds <- getCompileCommands(appConfig, spec)
      contexts = compileCmds.map(CompileCommands.extractContext)
      _ <- contexts.parTraverseN(appConfig.jobs) { ctx =>
        val logFilePath = ctx.file / os.up / s"${ctx.file.last}.log"
        desugarFile(
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

  // TODO: Implement this
  def deduplicate(alarms: List[TransformationAlarm])
      : List[TransformationAlarm] = {
    List.empty[TransformationAlarm]
  }

  def exportAlarms(alarms: List[Alarm]): IO[Unit] = IO.blocking {
    val destPath = os.Path("/results")
    if (!os.exists(destPath)) os.makeDir.all(destPath)
    val targetFile = destPath / "results.json"
    os.write.over(targetFile, alarms.asJson.spaces2, createFolders = true)
  }
}
