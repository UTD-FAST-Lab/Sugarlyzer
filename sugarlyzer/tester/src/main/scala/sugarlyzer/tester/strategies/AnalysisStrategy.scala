package sugarlyzer.tester.strategies

import cats.effect.{IO}

import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.common.Config.AppConfig
import sugarlyzer.common.Config.Strategy
import sugarlyzer.models.ProgramSpecification
import sugarlyzer.tester.tools.StrategyAlarm

trait AnalysisStrategy {
  type Alarm <: StrategyAlarm
  def analyze(
      appConfig: AppConfig,
      spec: ProgramSpecification,
      tool: AnalysisTool
  ): IO[List[Alarm]]
  def build(appConfig: AppConfig, spec: ProgramSpecification): IO[Unit]
}

object StrategyFactory {
  // Whenever there is a new strategy, add it here
  def create(strategy: Strategy): AnalysisStrategy =
    strategy match {
      case Strategy.PRODUCT => ProductStrategy
      case Strategy.TRANSFORMATION =>
        throw RuntimeException("Not implemented yet")
      case Strategy.FAMILY => throw RuntimeException("Not implemented yet")
    }
}
