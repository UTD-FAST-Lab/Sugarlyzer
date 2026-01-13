package sugarlyzer.tester.strategies

import cats.effect.{IO}

import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.common.Config.Mode
import sugarlyzer.common.Config.AppConfig

trait AnalysisStrategy {
  def execute(appConfig: AppConfig, tool: AnalysisTool): IO[Unit]
}

object StrategyFactory {
  def create(mode: Mode): AnalysisStrategy = mode match {
    case Mode.PRODUCT => ProductStrategy
  }
}
