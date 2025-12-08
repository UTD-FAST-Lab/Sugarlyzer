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

  /** Builds the command for desugaring, exposed for testing */
  private[sugarc] def buildDesugarCommand(
      fileToDesugar: Path,
      rsFileOpt: Option[Path],
      noStdLibs: Boolean,
      keepMem: Boolean,
      makeMain: Boolean,
      includedFiles: Iterable[Path],
      includedDirectories: Iterable[Path],
      commandLineDeclarations: Iterable[String]
  ): CommandBuilder = {
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
    cmd.in(File(fileToDesugar.toURI).getParentFile())
  }

  /** Computes the output file path for a desugared file */
  private[sugarc] def getOutputPath(fileToDesugar: Path): Path =
    fileToDesugar / os.up / (fileToDesugar.baseName + ".desugared.c")

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
      val cmd = buildDesugarCommand(
        fileToDesugar,
        rsFileOpt,
        noStdLibs,
        keepMem,
        makeMain,
        includedFiles,
        includedDirectories,
        commandLineDeclarations
      )
      cmd.runWithFileRedirects(getOutputPath(fileToDesugar), logFile)
    }
  }

  def processAlarms(
      alarms: Iterable[Alarm],
      desugaredFile: Path
  ): Iterable[Alarm] =

}

case class Alarm()