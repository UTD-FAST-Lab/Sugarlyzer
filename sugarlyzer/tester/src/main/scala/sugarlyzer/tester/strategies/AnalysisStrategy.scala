package sugarlyzer.tester.strategies

import cats.effect.{IO}

import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.common.Config.AppConfig
import sugarlyzer.common.Config.Strategy
import sugarlyzer.models.ProgramSpecification
import sugarlyzer.tester.tools.Alarm

trait AnalysisStrategy {
  def analyze(
      appConfig: AppConfig,
      spec: ProgramSpecification,
      tool: AnalysisTool
  ): IO[List[Alarm]]
  def build(appConfig: AppConfig, spec: ProgramSpecification): IO[Unit]
}

object StrategyFactory {
  def create(strategy: Strategy): AnalysisStrategy = strategy match {
    case Strategy.PRODUCT => ProductStrategy
  }
}
