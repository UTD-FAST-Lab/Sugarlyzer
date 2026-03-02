package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

import cats.effect.{IO}
import sugarlyzer.common.Config.Tool

case class ToolAlarm(
    alarmType: String,
    description: String,
    fileLocation: String,
    line: Int,
    analysisTime: Double
)

sealed trait StrategyAlarm {
  def finding: ToolAlarm
}

case class ProductAlarm(
    finding: ToolAlarm,
    configFiles: List[String],
    model: List[(String, String)]
) extends StrategyAlarm

case class TransformationAlarm(
    finding: ToolAlarm,
    sanitizedDescription: String,
    lineInputFile: Int,
    presenceCondition: String,
    model: String,
    feasible: Boolean,
    desugaringTime: Double
) extends StrategyAlarm

trait AnalysisTool {
  def name(): String
  def run(spec: ProgramSpecification): IO[List[ToolAlarm]]
}

object AnalysisTool {
  def apply(tool: Tool): AnalysisTool = tool match {
    case Tool.INFER  => InferTool
    case Tool.CLANG  => ClangTool
    case Tool.PHASAR => PhasarTool
  }
}
