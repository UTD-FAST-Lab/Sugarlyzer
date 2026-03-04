package sugarlyzer.tester.strategies

import os._
import cats.effect.IO
import sugarlyzer.tester.tools.TransformationAlarm
import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.models.ProgramSpecification
import sugarlyzer.common.Config.AppConfig
import io.circe.generic.auto.*
import io.circe.syntax.*
import sugarlyzer.models.Configurator
import sugarlyzer.tester.parsing.CompileCommand
import sugarlyzer.tester.parsing.CompileCommands

object TransformationStrategy extends AnalysisStrategy {
  type Alarm = TransformationAlarm

  // TODO: Implement this
  def analyze(
      appConfig: AppConfig,
      spec: ProgramSpecification,
      tool: AnalysisTool
  ): IO[List[TransformationAlarm]] = {
    IO.blocking {
      val alarms = List.empty[TransformationAlarm]
      alarms
    }
  }

  // TODO: Implement this
  def build(appConfig: AppConfig, spec: ProgramSpecification): IO[Unit] = {
    // Setup workspace
    // Install program
    // Build program
    for {
      _           <- IO.println("Preparing to build...")
      _           <- Configurator.stageAndBuild(appConfig, spec)
      compileCmds <- getCompileCommands(appConfig, spec)
      _           <- IO.println(s"compile commands: ${compileCmds}")
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

      os.proc("make", "allyesconfig")
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
