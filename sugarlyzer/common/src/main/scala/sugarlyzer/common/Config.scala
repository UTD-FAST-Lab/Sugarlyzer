package sugarlyzer.common

import scopt.OParser

object Config {
  enum Mode {
    case PRODUCT, FAMILY, TRANSFORMATION
  }

  case class AppConfig(
      tool: String = "",
      program: String = "",
      mode: Mode = Mode.PRODUCT,
      sampleSize: Int = 100,
      jobs: Int = Runtime.getRuntime().availableProcessors(),
      verbose: Boolean = false
  )

  val builder = OParser.builder[AppConfig]
  val parser = {
    import builder._
    OParser.sequence(
      programName("Sugarlyzer 2.0"),
      head("Sugarlyzer", "2.0"),
      opt[String]('t', "tool")
        .required()
        .action((x, c) => c.copy(tool = x))
        .text("Tool to run (e.g., clang)"),
      opt[String]('p', "program")
        .required()
        .action((x, c) => c.copy(program = x))
        .text("Target program (e.g., axtls)"),
      opt[Int]('s', "sample_size")
        .action((x, c) => c.copy(sampleSize = x)),
      opt[String]('m', "mode")
        .action((x, c) => c.copy(mode = Mode.valueOf(x.toUpperCase)))
        .text("Mode: product, transformation, family"),
      opt[Int]('j', "jobs")
        .action((x, c) => c.copy(jobs = x))
        .text("number of parallel jobs"),
      opt[Unit]('v', "verbose")
        .action((_, c) => c.copy(verbose = true))
        .text("Enable verbose logging")
    )
  }
}
