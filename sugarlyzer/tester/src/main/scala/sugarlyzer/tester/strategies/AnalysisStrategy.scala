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
  def deduplicate(alarms: List[Alarm]): List[Alarm]
  def exportAlarms(alarms: List[Alarm]): IO[Unit]
}

object AnalysisStrategy {
  def apply(strategy: Strategy): AnalysisStrategy =
    strategy match {
      case Strategy.PRODUCT        => ProductStrategy
      case Strategy.TRANSFORMATION => TransformationStrategy
      case Strategy.FAMILY => throw new RuntimeException("Not implemented yet")
    }
}
