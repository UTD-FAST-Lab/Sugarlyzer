package sugarlyzer.tester

import cats.effect.{IOApp, IO, ExitCode}
import scopt.OParser
import sugarlyzer.common.Config

import sugarlyzer.tester.strategies.*
import sugarlyzer.tester.tools.*

object TesterApp extends IOApp {

  override def run(args: List[String]): IO[ExitCode] = {
    OParser.parse(Config.parser, args, Config.AppConfig()) match {
      case Some(config) =>
        for {
          _        <- IO.println("[TESTER] Running analysis logic...")
          tool     <- IO(ToolFactory.create(config.tool))
          strategy <- IO(StrategyFactory.create(config.strategy))
          _        <- IO.println(s"[TESTER] Strategy is ${config.strategy}")
          _        <- IO.println(s"[TESTER] Tool is ${config.tool}")
          _        <- strategy.execute(config, tool)

        } yield ExitCode.Success
      case None => IO(ExitCode.Error)
    }
  }
}
