package sugarlyzer.tester.sugarc

import cats.effect.IO
import os.Path
import java.io.File
import com.typesafe.scalalogging.Logger
import sugarlyzer.util.CommandBuilder

object SugarCRunner {

  val logger = Logger[SugarCRunner.type]

  private def getTempFile(): IO[Path] =
    IO.blocking(os.temp())

  private def writeToFile(file: Path, content: Iterable[String]): IO[Unit] =
    IO.blocking(os.write(file, content))

  def desugarFile(
      fileToDesugar: Path,
      logFile: Path,
      recommendedSpace: Option[Iterable[String]] = None,
      noStdLibs: Boolean = false,
      keepMem: Boolean = false,
      makeMain: Boolean = false,
      includedFiles: Iterable[Path] = Seq(),
      includedDirectories: Iterable[Path] = Seq(),
      commandLineDeclarations: Iterable[String] = Nil
  ): IO[(Path, Path)] = {
    /* If recommended space exists, write it to a file, and add it to the
     * included files */
    val recommendedSpaceFileIO: IO[Option[Path]] = recommendedSpace match {
      case Some(rs) =>
        for {
          fi <- getTempFile()
          _  <- writeToFile(fi, rs)
        } yield Some(fi)
      case None => IO.pure(None)
    }

    recommendedSpaceFileIO.flatMap { rsFileOpt =>
      val allIncludedFiles = rsFileOpt.toSeq ++ includedFiles

      var cmd = CommandBuilder(
        program = Seq(
          "java",
          "-Xmx32g",
          "superc.SugarC",
          "-showActions",
          "-useBDD"
        ).mkString(" ")
      ).args(
        allIncludedFiles.map(p => s"-include ${p.toString()}").toSeq*
      ).args(
        includedDirectories.map(p => s"-I ${p.toString()}").toSeq*
      ).args(
        commandLineDeclarations.toSeq*
      )

      if noStdLibs then cmd = cmd.arg("-nostdinc")
      if keepMem then cmd = cmd.arg("-keep-mem")
      if makeMain then cmd = cmd.arg("-make-main")
      cmd = cmd.in(File(fileToDesugar.toURI).getParentFile())
      cmd.runWithFileRedirects(
        (fileToDesugar / os.up / (fileToDesugar.baseName + ".desugared.c")),
        logFile
      )
    }
  }
}
