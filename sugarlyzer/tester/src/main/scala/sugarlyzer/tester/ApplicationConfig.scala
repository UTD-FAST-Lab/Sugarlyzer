package sugarlyzer.tester

import scala.util.Try

object Config {

  opaque type Tool    = String
  opaque type Program = String

  case class SampleSize(i: Int) {
    require(i >= 0)
    require(i <= 1000)
  }

  enum Mode {
    case PRODUCT, FAMILY, TRANSFORMATION
  }

  case class AnalysisConfig(
      tool: Tool,
      program: Program,
      mode: Mode,
      sampleSize: SampleSize
  )

  def fromEnvironment(): Try[AnalysisConfig] = {
    Try(
      AnalysisConfig(
        tool = sys.env.getOrElse("ANALYSIS_TOOL", "clang"),
        program = sys.env.getOrElse("TARGET_PROGRAM", "axtls"),
        mode = Mode.valueOf(sys.env.getOrElse(
          "ANALYSIS_MODE",
          "PRODUCT"
        ).toUpperCase()),
        sampleSize =
          SampleSize(Integer.valueOf(sys.env.getOrElse("SAMPLE_SIZE", "1000")))
      )
    )
  }
}
