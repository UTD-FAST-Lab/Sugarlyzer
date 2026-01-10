package sugarlyzer.tester.strategies

import cats.effect.{IO}

import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.common.Config.Mode

trait AnalysisStrategy {
  def execute(program: String, tool: AnalysisTool): IO[Unit]
}


object StrategyFactory {
  def create(mode: Mode): AnalysisStrategy = mode match {
    case Mode.PRODUCT => ProductStrategy
    case Mode.FAMILY => FamilyStrategy
    case Mode.TRANSFORMATION => TransformationStrategy
    case other => throw new IllegalArgumentException(s"Strategy does not exist: ${mode}")
  }
}
