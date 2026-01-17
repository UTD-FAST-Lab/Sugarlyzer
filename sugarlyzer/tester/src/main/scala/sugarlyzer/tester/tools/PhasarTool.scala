package sugarlyzer.tester.tools

import cats.effect.IO
import sugarlyzer.models.ProgramSpecification

object PhasarTool extends AnalysisTool {
  def name(): String = { "Phasar" }
  def run(spec: ProgramSpecification): IO[List[Alarm]] = {
    IO(List(Alarm(
      "Phasar",
      "Phasar is not implemented yet",
      0,
      0,
      0,
      "Unknown"
    )))
  }
}
