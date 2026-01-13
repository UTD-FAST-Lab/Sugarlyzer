package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

import cats.effect.{IO}

trait Alarm {} // Prop for now

trait AnalysisTool {
  def name(): String
  def run(spec: ProgramSpecification): IO[String]
  def parseOutput(rawOutput: String): List[String]
}

object ToolFactory {
  def create(name: String): AnalysisTool = name.toLowerCase() match {
    case "infer" => InferTool
    case other   => throw new IllegalArgumentException(s"Unkown Tool ${name}")
  }
}
