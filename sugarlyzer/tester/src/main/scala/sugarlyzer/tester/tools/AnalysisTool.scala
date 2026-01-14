package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

import cats.effect.{IO}
import io.circe.Decoder

case class Alarm(
    bug_type: String,
    qualifier: String,
    line: Int,
    column: Int,
    procedure_start_line: Int,
    file: String
) derives Decoder

trait AnalysisTool {
  def name(): String
  def run(spec: ProgramSpecification): IO[List[Alarm]]
}

object ToolFactory {
  def create(name: String): AnalysisTool = name.toLowerCase() match {
    case "infer" => InferTool
    case other   => throw new IllegalArgumentException(s"Unkown Tool ${other}")
  }
}
