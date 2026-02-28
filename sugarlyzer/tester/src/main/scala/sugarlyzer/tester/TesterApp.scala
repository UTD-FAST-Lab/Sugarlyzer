package sugarlyzer.tester

import cats.effect.{IOApp, IO, ExitCode}
import scopt.OParser
import sugarlyzer.common.Config

import sugarlyzer.common.Config.Phase
import sugarlyzer.models.ProgramFactory
import sugarlyzer.tester.strategies.StrategyFactory
import sugarlyzer.tester.tools.ToolFactory

object TesterApp extends IOApp {

  override def run(args: List[String]): IO[ExitCode] = {
    OParser.parse(Config.parser, args, Config.AppConfig()) match {
      case Some(config) =>
        for {
          // Load the spec from specific program configuration file
          spec <- ProgramFactory.load(config.program)
          // Get the strategy object
          strategy <- IO(StrategyFactory.create(config.strategy))
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
                  tool <- IO(ToolFactory.create(config.tool))
                  alarms <- strategy.analyze(
                    config,
                    spec,
                    tool
                  )
                  _ <- IO.println(s"Found ${alarms.length} alarms")
                  _ <- IO.println(s"Alarms: ${alarms.mkString("\n")}")
                } yield ExitCode.Success
            }
          }
        } yield ExitCode.Success
      case None => IO(ExitCode.Error)
    }
  }
}
