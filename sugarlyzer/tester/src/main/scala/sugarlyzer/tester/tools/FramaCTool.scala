package sugarlyzer.tester.tools

import sugarlyzer.common.Config.AppConfig

import cats.effect.IO

import sugarlyzer.models.ProgramSpecification

object FramaCTool extends AnalysisTool {
  def name(): String = "Frama-C"

  def run(spec: ProgramSpecification)(using
      config: AppConfig
  ): IO[List[ToolAlarm]] = {
    for {
      _      <- IO.println(s"[TOOL] Running spec ${spec}")
      alarms <- analyzeFiles(spec)
      _      <- IO.println(s"[TOOL] Got ${alarms.length} alarms")
    } yield (alarms)
  }

  def analyzeFiles(spec: ProgramSpecification)(using
      config: AppConfig
  ): IO[List[ToolAlarm]]
}
