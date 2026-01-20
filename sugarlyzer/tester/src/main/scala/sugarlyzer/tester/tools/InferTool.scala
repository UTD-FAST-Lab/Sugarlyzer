package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

import cats.effect.{IO}
import os._
import sugarlyzer.tester.parsing._
import cats.effect.syntax.all._
import io.circe._
import io.circe.jawn.decodeFile

case class InferAlarm(
    bug_type: String,
    qualifier: String,
    line: Int,
    column: Int,
    procedure_start_line: Int,
    file: String
) derives Decoder

object InferTool extends AnalysisTool {
  def name(): String = { "Infer" }

  def run(spec: ProgramSpecification): IO[List[Alarm]] = {
    for {
      _        <- IO.println(s"Running spec ${spec}")
      _        <- applyConfiguration(spec)
      commands <- getCompileCommands(spec)
      _        <- IO.println(s"Found ${commands.size} commands")
      alarms   <- analyzeFiles(spec, commands)
    } yield (alarms)
  }

  def analyzeFiles(
      spec: ProgramSpecification,
      compileCommands: List[CompileCommand]
  ): IO[List[Alarm]] = {
    val indexedCommands = compileCommands.zipWithIndex

    indexedCommands.parTraverseN(Runtime.getRuntime().availableProcessors()) {
      case (cmd, i) =>
        IO.blocking {
          val uniqueResultsDir =
            os.Path(spec.targetDir) / "infer_results" / s"out-$i"
          if (os.exists(uniqueResultsDir)) os.remove.all(uniqueResultsDir)
          val reportJsonLocation = uniqueResultsDir / "report.json"

          val proc = os.proc(
            "infer",
            "run",
            "--pulse-only",
            "--results-dir",
            uniqueResultsDir.toString,
            "--",
            cmd.arguments
          ).call(
            cwd = os.Path(cmd.directory),
            stdout = os.Inherit,
            mergeErrIntoOut = true,
            check = false
          )

          if (proc.exitCode != 0)
            throw new RuntimeException("Failed to run infer analysis")

          reportJsonLocation
        }.flatMap { path =>
          parseOutput(path)
        }
    }.map(_.flatten)
  }

  def getCompileCommands(spec: ProgramSpecification)
      : IO[List[CompileCommand]] = {

    val targetPath          = os.Path(spec.targetDir)
    val compileCommandsFile = targetPath / os.up / "compile_commands.json"

    val runBear = IO.blocking {
      val proc = os.proc(
        "bear",
        "--output",
        compileCommandsFile.toString,
        "--",
        "make"
      ).call(cwd = targetPath)
      if (proc.exitCode != 0)
        throw new RuntimeException("Failed to run bear")
    }

    for {
      _        <- runBear
      commands <- CompileCommands.parse(compileCommandsFile)
    } yield commands
  }

  def applyConfiguration(spec: ProgramSpecification): IO[Unit] = IO.blocking {
    val proc = os.proc("bash", "-c", spec.buildCommand).call(
      cwd = os.Path(spec.targetDir)
    )
    if (proc.exitCode != 0) {
      throw new RuntimeException(
        s"Failed to run build command: ${spec.buildCommand}"
      )
    }
  }

  def parseOutput(resultPath: Path): IO[List[Alarm]] = IO.blocking {
    val file = resultPath.toIO

    decodeFile[List[Alarm]](file) match {
      case Right(alarms) => alarms
      case Left(error) => throw new RuntimeException(
          s"Failed to parse alarms from $resultPath: $error"
        )
    }
  }
}
