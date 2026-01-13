package sugarlyzer.tester.strategies

import cats.effect.{IO}
import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.models.*

object ProductStrategy extends AnalysisStrategy {
  def execute(programName: String, tool: AnalysisTool): IO[Unit] = {
    for {
      _           <- IO.println("Loading program from factory")
      programSpec <- ProgramFactory.load(programName)
      _           <- IO.println(programSpec)

    } yield ()

  }
}
