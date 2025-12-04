package sugarlyzer.tester

import cats.effect.IOApp
import cats.effect.IO

object Application extends IOApp.Simple {

  override def run: IO[Unit] =
    for {
      _      <- IO.println("Starting analysis run")
      config <- IO.fromTry(Config.fromEnvironment())
    } yield ()

}
