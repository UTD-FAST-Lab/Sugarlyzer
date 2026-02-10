package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

import cats.effect.{IO}
import os._
import io.circe._
import io.circe.jawn.decodeFile

object InferTool extends AnalysisTool {
  def name(): String = { "Infer" }

  def run(spec: ProgramSpecification): IO[List[Alarm]] = {
    for {
      _      <- IO.println(s"[TOOL] Running spec ${spec}")
      alarms <- analyzeFiles(spec)
      _      <- IO.println(s"[TOOL] Got ${alarms.length} alarms")
    } yield (alarms)
  }

  def analyzeFiles(
      spec: ProgramSpecification
  ): IO[List[Alarm]] = {
    val rootDir             = os.Path(spec.rootDir)
    val compileCommandsPath = rootDir / "compile_commands.json"

    os.proc(
      "sed",
      "-i",
      "s/-fno-guess-branch-probability//g",
      compileCommandsPath.toString
    ).call(cwd = rootDir): Unit

    val procCapture = os.proc(
      "infer",
      "capture",
      "--compilation-database",
      compileCommandsPath.toString
    ).call(cwd = rootDir, stdout = os.Inherit, stderr = os.Inherit)
    if (procCapture.exitCode != 0)
      throw new RuntimeException("Failed to run infer")

    val proc = os.proc(
      "infer",
      "analyze"
    ).call(cwd = rootDir, stdout = os.Inherit, stderr = os.Inherit)
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
