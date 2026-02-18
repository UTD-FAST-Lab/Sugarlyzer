package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

import cats.effect.{IO}

case class Alarm(
    alarmType: String,
    description: String,
    sanitizedDescription: Option[String],
    line: Int,
    lineInputFile: Option[Int],
    fileLocation: String,
    configFile: Option[String],
    model: Option[String],
    feasible: Option[Boolean],
    desugaringTime: Option[Double],
    analysisTime: Double
)

trait AnalysisTool {
  def name(): String
  def run(spec: ProgramSpecification): IO[List[Alarm]]
}

object ToolFactory {
  // Whenever there is a new tool, add it here
  def create(name: String): AnalysisTool = name.toLowerCase() match {
    case "infer"  => InferTool
    case "clang"  => ClangTool
    case "phasar" => PhasarTool
    case other    => throw new IllegalArgumentException(s"Unkown Tool ${other}")
  }
}
