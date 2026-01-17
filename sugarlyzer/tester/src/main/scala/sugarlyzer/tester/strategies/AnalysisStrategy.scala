package sugarlyzer.tester.strategies

import cats.effect.{IO}

import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.common.Config.AppConfig
import sugarlyzer.common.Config.Strategy

trait AnalysisStrategy {
  def execute(appConfig: AppConfig, tool: AnalysisTool): IO[Unit]
}

object StrategyFactory {
  def create(strategy: Strategy): AnalysisStrategy = strategy match {
    case Strategy.PRODUCT => ProductStrategy
  }
}
