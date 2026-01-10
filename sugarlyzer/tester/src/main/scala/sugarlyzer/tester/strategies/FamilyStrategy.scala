package sugarlyzer.tester.strategies

import cats.effect.{IO}

import sugarlyzer.tester.tools.AnalysisTool

object FamilyStrategy extends AnalysisStrategy{
  def execute(program: String, tool: AnalysisTool): IO[Unit] {}
}
