package sugarlyzer.tester

import cats.effect.{IOApp, IO, ExitCode}
import scopt.OParser
import sugarlyzer.common.Config

import sugarlyzer.common.Config.Phase
import sugarlyzer.models.ProgramFactory
import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.tester.strategies.AnalysisStrategy

object TesterApp extends IOApp {

  override def run(args: List[String]): IO[ExitCode] = {
    OParser.parse(Config.parser, args, Config.AppConfig()) match {
      case Some(config) =>
        for {
          // Load the spec from specific program configuration file
          spec <- ProgramFactory.load(config.program)
          // Get the strategy object
          strategy <- IO(AnalysisStrategy(config.strategy))
          _        <- IO.println(s"[TESTER] Configuration: $config")
          _ <- {
            // Run the specific phase of the program
            config.phase match {
              /* Build phase to create the shared directory, build the
               * base/master source. Basically every prereq for running the tool */
              case Phase.BUILD =>
                for {
                  _ <- IO.println("[TESTER] Running build logic...")
                  start_time = System.currentTimeMillis()
                  _ <- strategy.build(config, spec)
                  end_time = System.currentTimeMillis()
                  _ <- IO.println(
                    "Build time: " + (end_time - start_time) + " ms"
                  )
                } yield ExitCode.Success
              case Phase.ANALYZE =>
                for {
                  _ <- IO.println("[TESTER] Running analysis logic...")
                  // Get the tools object and run the analysis
                  tool <- IO(AnalysisTool(config.tool))
                  analysis_start_time = System.currentTimeMillis()
                  alarms <- strategy.analyze(
                    config,
                    spec,
                    tool
                  )
                  analysis_end_time = System.currentTimeMillis()
                  _ <- IO.println(s"[TESTER] Found ${alarms.length} alarms")
                  _ <- IO.println(
                    "Analysis time: " + (analysis_end_time - analysis_start_time) + " ms"
                  )
                  deduplicated_start_time = System.currentTimeMillis()
                  deduplicated_alarms <- IO(strategy.deduplicate(alarms))
                  deduplicated_end_time = System.currentTimeMillis()
                  _ <- IO.println(
                    "Deduplication time: " + (deduplicated_end_time - deduplicated_start_time) + " ms"
                  )
                  _ <- IO.println(
                    s"[TESTER] deduplicated (length: ${deduplicated_alarms.length})"
                  )

                  _ <- strategy.exportAlarms(config, deduplicated_alarms)
                } yield ExitCode.Success
            }
          }
        } yield ExitCode.Success
      case None => IO(ExitCode.Error)
    }
  }
}
