package sugarlyzer.tester.tools

import cats.effect.{IO}

object PhasarTool extends AnalysisTool {
  def name(): String = {}
  def runAnalysis(): IO[String] = {}
  def parseOutput(rawOutput: String): List[Alarm] = {}
}
