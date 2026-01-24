package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

import cats.effect.{IO}
import os._
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
      _             <- IO.println(s"Running spec ${spec}")
      _             <- applyConfiguration(spec)
      commandDBPath <- getCompileCommands(spec)
      alarms        <- analyzeFiles(spec, commandDBPath)
    } yield (alarms)
  }

  def analyzeFiles(
      spec: ProgramSpecification,
      compileCommandsPath: os.Path
  ): IO[List[Alarm]] = {
    val procCapture = os.proc(
      "infer",
      "capture",
      "--compilation-database",
      compileCommandsPath.toString
    )
      .call(cwd = os.Path(spec.targetDir))

    if (procCapture.exitCode != 0)
      throw new RuntimeException("Failed to run infer")

    val proc = os.proc(
      "infer",
      "analyze"
    ).call(cwd = os.Path(spec.targetDir))
    if (proc.exitCode != 0)
      throw new RuntimeException("Failed to run infer")

    val reportJsonPath = os.Path(spec.targetDir) / "infer-out" / "report.json"
    parseOutput(reportJsonPath)
  }

  def getCompileCommands(spec: ProgramSpecification)
      : IO[os.Path] = {

    val targetPath          = os.Path(spec.targetDir)
    val compileCommandsFile = targetPath / "compile_commands.json"

    val runBear = IO.blocking {
      val procBear = os.proc("make", "clean").call(
        cwd = os.Path(spec.targetDir)
      )
      if (procBear.exitCode != 0)
        throw new RuntimeException("Failed to run make clean")

      val proc = os.proc(
        "bear",
        "--",
        "make"
      ).call(cwd = targetPath)
      if (proc.exitCode != 0)
        throw new RuntimeException("Failed to run bear")
    }

    for {
      _ <- runBear
    } yield compileCommandsFile
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
