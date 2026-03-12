package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

import cats.effect.{IO}
import os._
import io.circe._
import io.circe.jawn.decodeFile

case class InferAlarm(
    bug_type: String,
    qualifier: String,
    column: Int,
    line: Int,
    file: String
) derives Decoder

object InferTool extends AnalysisTool {
  def name(): String = { "Infer" }

  def run(spec: ProgramSpecification): IO[List[ToolAlarm]] = {
    for {
      _      <- IO.println(s"[TOOL] Running spec ${spec}")
      alarms <- analyzeFiles(spec)
      _      <- IO.println(s"[TOOL] Got ${alarms.length} alarms")
    } yield (alarms)
  }

  def analyzeFiles(
      spec: ProgramSpecification
  ): IO[List[ToolAlarm]] = {
    val rootDir             = os.Path(spec.rootDir)
    val compileCommandsPath = rootDir / "compile_commands.json"
    val reportJsonPath = os.Path(spec.rootDir) / "infer-out" / "report.json"

    for {
      analysisTime <- IO.blocking {
        os.proc(
          "sed",
          "-i",
          "s/-fno-guess-branch-probability//g",
          compileCommandsPath.toString
        ).call(cwd = rootDir): Unit

        val start = System.nanoTime()

        val procCapture = os.proc(
          "infer",
          "capture",
          "--keep-going",
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

        val end = System.nanoTime()
        (end - start) / 1e9d
      }
      alarms <- parseOutput(spec, reportJsonPath, analysisTime)
    } yield alarms
  }

  def parseOutput(
      spec: ProgramSpecification,
      resultPath: Path,
      analysisTime: Double
  ): IO[List[ToolAlarm]] = {
    IO.blocking {
      decodeFile[List[InferAlarm]](resultPath.toIO) match {
        case Right(alarms) => normalizeAlarms(spec, alarms, analysisTime)
        case Left(error)   => throw new RuntimeException(s"Parse error: $error")
      }
    }
  }

  def normalizeAlarms(
      spec: ProgramSpecification,
      inferAlarms: List[InferAlarm],
      analysisTime: Double
  ): List[ToolAlarm] = {
    inferAlarms.map { ia =>
      ToolAlarm(
        alarmType = ia.bug_type,
        description = ia.qualifier,
        line = ia.line,
        fileLocation = spec.rootDir + "/" + ia.file,
        analysisTime = analysisTime
      )
    }
  }
}
