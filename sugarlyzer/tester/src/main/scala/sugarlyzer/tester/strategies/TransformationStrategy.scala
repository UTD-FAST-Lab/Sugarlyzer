package sugarlyzer.tester.strategies

import cats.effect.{IO}

import sugarlyzer.tester.tools.AnalysisTool

object TransformationStrategy extends AnalysisStrategy{
  def execute(program: String, tool: AnalysisTool): IO[Unit] {}
}
