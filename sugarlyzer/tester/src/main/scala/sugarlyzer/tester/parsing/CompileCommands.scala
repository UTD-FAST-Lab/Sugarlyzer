package sugarlyzer.tester.parsing

import cats.effect.{IO}

import io.circe.Decoder
import io.circe.jawn.decodeFile
import os._

case class CompileCommand (
  directory: String,
  file: String,
  output: String,
  arguments: List[String]
  ) derives Decoder


object CompileCommands {
  def parse(jsonPath: Path): IO[List[CompileCommand]] = IO.blocking {
    val file = jsonPath.toIO

    decodeFile[List[CompileCommand]](file) match {
      case Right(commands) => commands
      case Left(error) => throw new RuntimeException(s"Failed to parse compile commands json file: $error")
    }

  }
}
