package sugarlyzer.tester.tools

import cats.effect.{IO}

trait Alarm { } // Prop for now

trait AnalysisTool {
  def name(): String
  def runAnalysis(targetDir: String): IO[String]
  def parseOutput(rawOutput: String): List[Alarm]
}

object ToolFactory {
  def create(name: String): AnalysisTool = name.toLowerCase() match {
    case "clang" => ClangTool
    case "infer" => InferTool
    case "Phasar" => PhasarTool
    case other => throw new IllegalArgumentException(s"Unkown Tool ${name}")
  }
}
