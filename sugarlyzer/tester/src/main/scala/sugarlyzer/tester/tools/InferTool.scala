package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

object InferTool extends AnalysisTool {
  def name(): String = { "Infer" }

  def run(programSpec: ProgramSpecification): String = {
    "O"
  }
  def parseOutput(rawOutput: String): List[String] = {
    List("O")
  }
}
