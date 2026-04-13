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
          _ <- {
            // Run the specific phase of the program
            config.phase match {
              /* Build phase to create the shared directory, build the
               * base/master source. Basically every prereq for running the tool */
              case Phase.BUILD =>
                for {
                  _ <- IO.println("[TESTER] Running build logic...")
                  _ <- strategy.build(config, spec)
                } yield ExitCode.Success
              case Phase.ANALYZE =>
                for {
                  _ <- IO.println("[TESTER] Running analysis logic...")
                  // Get the tools object and run the analysis
                  tool <- IO(AnalysisTool(config.tool))
                  alarms <- strategy.analyze(
                    config,
                    spec,
                    tool
                  )
                  _ <- IO.println(s"[TESTER] Found ${alarms.length} alarms")

                  deduplicated_alarms <- IO(strategy.deduplicate(alarms))

                  _ <- IO.println(
                    s"[TESTER] deduplicated (length: ${deduplicated_alarms.length})"
                  )

                  _ <- strategy.exportAlarms(deduplicated_alarms)
                } yield ExitCode.Success
            }
          }
        } yield ExitCode.Success
      case None => IO(ExitCode.Error)
    }
  }
}
