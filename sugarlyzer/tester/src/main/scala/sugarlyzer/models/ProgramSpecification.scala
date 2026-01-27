package sugarlyzer.models

import cats.effect.{IO}
import io.circe.parser._
import scala.io.Source
import io.circe._

case class ProgramSpecification(
    name: String = "",
    rootDir: String = "",
    buildCommand: String = "",
    configFileLocation: String = "",
    configHeaderLocation: String = ""
) derives Decoder

object ProgramFactory {
  def load(programName: String): IO[ProgramSpecification] = IO.blocking {
    val resourcePath = s"programs/$programName/$programName.json"
    val stream       = getClass.getClassLoader.getResourceAsStream(resourcePath)

    if (stream == null) {
      throw new RuntimeException(s"Program definition not found: $resourcePath")
    }

    val jsonContent = Source.fromInputStream(stream).mkString

    decode[ProgramSpecification](jsonContent) match {
      case Right(spec) => spec
      case Left(error) =>
        throw new RuntimeException(s"Invalid JSON for $programName: $error")
    }
  }
}
