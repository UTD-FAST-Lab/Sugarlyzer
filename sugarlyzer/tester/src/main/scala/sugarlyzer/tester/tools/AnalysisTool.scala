package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

import cats.effect.{IO}
import sugarlyzer.common.Config.Tool
import sugarlyzer.common.Config.AppConfig
import sugarlyzer.tester.sugarc.PresenceCondition

case class ToolAlarm(
    alarmType: String,
    description: String,
    fileLocation: String,
    line: Int,
    analysisTime: Double
)

sealed trait StrategyAlarm {
  def originalAlarm: ToolAlarm
}

case class ProductAlarm(
    originalAlarm: ToolAlarm,
    configFiles: List[String],
    model: List[(String, String)],
    numConfigs: List[Int]
) extends StrategyAlarm

case class TransformationAlarm(
    originalAlarm: ToolAlarm,
    originalFile: String,
    sanitizedDescription: String,
    lineInputFile: Option[(Int, Int)],
    presenceCondition: PresenceCondition,
    model: String,
    feasible: Boolean,
    desugaringTime: Double
) extends StrategyAlarm

case class FamilyAlarm(
    originalAlarm: ToolAlarm
) extends StrategyAlarm

trait AnalysisTool {
  def name(): String
  def run(spec: ProgramSpecification)(using AppConfig): IO[List[ToolAlarm]]
}

object AnalysisTool {
  def apply(tool: Tool): AnalysisTool = tool match {
    case Tool.INFER    => InferTool
    case Tool.CLANG    => ClangTool
    case Tool.PHASAR   => PhasarTool
    case Tool.TYPECHEF => TypeChefTool
  }
}
