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
          spec     <- ProgramFactory.load(config.program)
          strategy <- IO(StrategyFactory.create(config.strategy))
          _ <- {
            config.phase match {
              case Phase.BUILD =>
                for {
                  _ <- IO.println("[TESTER] Running build logic...")
                  _ <- strategy.build(config, spec)
                } yield ExitCode.Success
              case Phase.ANALYZE =>
                for {
                  _ <- IO.println("[TESTER] Running analysis logic...")
                  alarms <- strategy.analyze(
                    config,
                    spec,
                    ToolFactory.create(config.tool)
                  )
                  _ <- IO.println(s"Found ${alarms.length} alarms")
                } yield ExitCode.Success
            }
          }
        } yield ExitCode.Success
      case None => IO(ExitCode.Error)
    }
  }
}
