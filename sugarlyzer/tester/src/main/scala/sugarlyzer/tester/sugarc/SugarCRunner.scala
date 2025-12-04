package sugarlyzer.tester.sugarc

import cats.effect.IO
import os.Path

object SugarCRunner {

  private def getTempFile(): IO[Path] =
    IO.blocking(os.temp())

  private def writeToFile(file: Path, content: Iterable[String]): IO[Unit] =
    IO.blocking(os.write(file, content))

  def desugarFile(
      fileToDesugar: Path,
      recommendedSpace: Option[Iterable[String]] = None,
      outputFile: Option[Path] = None,
      logFile: Option[Path] = None,
      configPrefix: Option[String] = None,
      noStdLibs: Boolean = false,
      keepMem: Boolean = false,
      makeMain: Boolean = false,
      includedFiles: Iterable[Path] = Seq(),
      includedDirectories: Iterable[Path] = Seq(),
      commandLineDeclarations: Iterable[String] = Nil
  ): IO[Path] = {
    // If recommended space exists, write it to a file, and add it to the
    val recommendedSpaceFile = recommendedSpace.map { rs =>
      for fi <- getTempFile()
      _      <- writeToFile(fi, rs)
      yield ()
    }
  }
}
