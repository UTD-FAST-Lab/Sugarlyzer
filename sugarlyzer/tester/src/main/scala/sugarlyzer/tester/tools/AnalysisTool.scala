package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

trait Alarm {} // Prop for now

trait AnalysisTool {
  def name(): String
  def run(programSpec: ProgramSpecification): String
  def parseOutput(rawOutput: String): List[String]
}

object ToolFactory {
  def create(name: String): AnalysisTool = name.toLowerCase() match {
    case "infer" => InferTool
    case other   => throw new IllegalArgumentException(s"Unkown Tool ${name}")
  }
}
