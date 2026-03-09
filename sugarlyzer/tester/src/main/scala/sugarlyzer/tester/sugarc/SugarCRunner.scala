package sugarlyzer.tester.sugarc

import cats.effect.IO
import os.Path
import java.io.File
import com.typesafe.scalalogging.Logger
import sugarlyzer.util.CommandBuilder
import cats.implicits.*
import scala.util.matching.Regex
import com.microsoft.z3.Context
import sugarlyzer.tester.tools.TransformationAlarm
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
      commandLineDeclarations: Iterable[String],
      restrict: Boolean = false
  ): CommandBuilder = {
    val allIncludedFiles = rsFileOpt.toSeq ++ includedFiles

    var cmd = CommandBuilder(
      program = "java"
    ).args(
      "-Djava.library.path=/opt/z3/bin",
      "-Xmx32g",
      "superc.SugarC",
      "-showActions",
      "-useBDD"
    ).args(
      allIncludedFiles.flatMap(p => Seq("-include", p.toString())).toSeq*
    ).args(
      includedDirectories.flatMap(p => Seq("-I", p.toString())).toSeq*
    ).args(
      commandLineDeclarations.toSeq*
    )

    if noStdLibs then cmd = cmd.arg("-nostdinc")
    if keepMem then cmd = cmd.arg("-keep-mem")
    if makeMain then cmd = cmd.arg("-make-main")
    if restrict then cmd = cmd.args("-restrictConfigToPrefix", "_KGENMACRO")
    cmd = cmd.args(fileToDesugar.toString)
    logger.debug(s"Sugarc cmd is ${cmd.show}")
    cmd.in(File(fileToDesugar.toURI).getParentFile())
  }

  /** Computes the output file path for a desugared file */
  private[sugarc] def getOutputPath(fileToDesugar: Path): Path =
    fileToDesugar / os.up / (fileToDesugar.baseName + ".desugared.c")

  def desugarFile(
      fileToDesugar: Path,
      logFile: Path,
      recommendedSpace: Option[Iterable[String]] = None,
      noStdLibs: Boolean = true,
      keepMem: Boolean = true,
      makeMain: Boolean = true,
      includedFiles: Iterable[Path] = Seq(),
      includedDirectories: Iterable[Path] = Seq(),
      commandLineDeclarations: Iterable[String] = Nil
  ): IO[(CommandBuilder.ResultFile, CommandBuilder.LogFile)] = {
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

  def findPresenceCondition(
      alarm: TransformationAlarm,
      file: Path
  ): PresenceCondition = {
    // Open the file
    var results = List.empty[String]
    val lines   = os.read(file).split("\n").toList
    // Find the line with the alarm
    val alarmLine    = alarm.finding.line
    var counter      = 0
    val regex: Regex = raw"if \((__static_condition_default_\d+)\(\)\).*".r

    // Walk backwards from the alarm line
    for {
      i <- (alarmLine - 1) to 0 by -1
    } do {
      val line = lines(i)
      counter -= line.count(_ == '{')
      counter += line.count(_ == '}')
      if counter < 0 then line match {
        case regex(condition) =>
          logger.debug(
            s"Found presence condition for alarm at line ${alarmLine} at line " + i
          )
          results = condition :: results
        case _ =>
      }
    }
    // For each presence condition, parse the actual condition expression
    val conditionRegex: Regex =
      """__static_condition_renaming\(\"(.*)\", \"(.*)\"\);""".r
    val ctx = new Context()
    val exprs = for {
      r <- results
      l <- lines.filter(_.contains(s"__static_condition_renaming(\"$r\""))
      expr <- l match {
        case conditionRegex(oldName, newName) =>
          logger.debug(
            s"Found renamed presence condition: $oldName -> $newName"
          )
          Some(PresenceConditionParser.parse(ctx, newName))
        case _ =>
          logger.debug("Couldn't match regular expression")
          None
      }
    } yield expr

    val combined = exprs match {
      case Nil      => ctx.mkTrue()
      case e :: Nil => e
      case _        => ctx.mkAnd(exprs*)
    }
    PresenceCondition(ctx, combined)
  }
}
