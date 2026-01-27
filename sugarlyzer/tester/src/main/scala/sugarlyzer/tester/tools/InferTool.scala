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
      _      <- IO.println(s"Running spec ${spec}")
      alarms <- analyzeFiles(spec)
    } yield (alarms)
  }

  def analyzeFiles(
      spec: ProgramSpecification
  ): IO[List[Alarm]] = {
    val rootDir             = os.Path(spec.rootDir)
    val compileCommandsPath = rootDir / "compile_commands.json"

    val procCapture = os.proc(
      "infer",
      "capture",
      "--compilation-database",
      compileCommandsPath.toString
    ).call(cwd = os.Path(spec.rootDir))
    if (procCapture.exitCode != 0)
      throw new RuntimeException("Failed to run infer")

    val proc = os.proc(
      "infer",
      "analyze"
    ).call(cwd = os.Path(spec.rootDir))
    if (proc.exitCode != 0)
      throw new RuntimeException("Failed to run infer")

    val reportJsonPath = os.Path(spec.rootDir) / "infer-out" / "report.json"
    parseOutput(reportJsonPath)
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
