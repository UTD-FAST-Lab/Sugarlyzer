package sugarlyzer.tester.strategies

import cats.effect.{IO}

import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.common.Config.Mode

trait AnalysisStrategy {
  def execute(programName: String, tool: AnalysisTool): IO[Unit]
}

object StrategyFactory {
  def create(mode: Mode): AnalysisStrategy = mode match {
    case Mode.PRODUCT => ProductStrategy
  }
}
