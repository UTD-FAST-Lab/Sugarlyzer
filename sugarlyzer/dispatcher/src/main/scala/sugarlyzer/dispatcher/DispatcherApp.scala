package sugarlyzer.dispatcher

import cats.effect.{IOApp, IO, ExitCode}
import scopt.OParser
import sugarlyzer.common.Config

object DispatcherApp extends IOApp {

  override def run(args: List[String]): IO[ExitCode] = {
    OParser.parse(Config.parser, args, Config.AppConfig()) match {
      case Some(config) => {
        for {
          _ <- IO.println(
            s"[HOST] Preparing to run ${config.tool} on ${config.program}"
          )

          _ <- IO.println("[HOST] Preparing/Launching docker environment")

        } yield ExitCode.Success
      }
      case None => IO(ExitCode.Error)
    }
  }
}
