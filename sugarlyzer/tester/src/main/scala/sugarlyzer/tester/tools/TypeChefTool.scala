package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

import cats.effect.{IO}
import sugarlyzer.common.Config.AppConfig


object TypeChefTool extends AnalysisTool{
  def name(): String ={"TypeChef"}

  def run(spec: ProgramSpecification)(using config: AppConfig): IO[List[ToolAlarm]] = {
    ???
  }

  def analyzeFiles(spec: ProgramSpecification)(using config: AppConfig): IO[List[ToolAlarm]] = {
    ???
  }

  def parseOutput(spec: ProgramSpecification, resultPath: os.Path, analysisTime: Double): IO[List[ToolAlarm]] = {
    ???
  }

}
