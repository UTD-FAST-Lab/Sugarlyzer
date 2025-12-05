package sugarlyzer.tester.sugarc

import cats.effect.IO
import os.Path
import scala.sys.process._
import java.io.File
import cats.Show
import com.typesafe.scalalogging.Logger

object SugarCRunner {

  val logger = Logger[SugarCRunner.type]

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
    val cmd = CommandBuilder(
      program = Seq(
        "java",
        "-Xmx32g",
        "superc.SugarC",
        "-showActions",
        "-useBDD"
      ).mkString(" ")
    ).args(
      includedFiles.map(p => s"-include ${p.toString()}").toSeq*
    ).args(
      includedDirectories.map(p => s"-I ${p.toString()}").toSeq*
    )

  }
}

case class CommandBuilder(
    program: String,
    args: Vector[String] = Vector.empty,
    env: Map[String, String] = Map.empty,
    workingDir: Option[File] = None
) {
  def arg(a: String): CommandBuilder    = copy(args = args :+ a)
  def args(as: String*): CommandBuilder = copy(args = args ++ as)
  def env(key: String, value: String): CommandBuilder =
    copy(env = env + (key -> value))
  def in(dir: File): CommandBuilder = copy(workingDir = Some(dir))

  def build: ProcessBuilder = {
    Process(program +: args, workingDir, env.toSeq*)
  }

  def run(): Int = build.!
  def runWithOutput(): (Int, String, String) = {
    val stdout = StringBuilder()
    val stderr = StringBuilder()
    val code = build.!(ProcessLogger(
      s => stdout.append(s + "\n"),
      s => stderr.append(s + "\n")
    ))
    (code, stdout.toString.trim, stderr.toString.trim)
  }
}

object CommandBuilder {
  given Show[CommandBuilder] with
    def show(t: CommandBuilder): String = {
      val envStr = t.env.map((k, v) => s"$k=$v").mkString(" ")
      val cwdStr = t.workingDir.map(d => s"(in ${d.getPath})").getOrElse("")
      val cmdStr = (t.program +: t.args).mkString(" ")
      Seq(envStr, cmdStr, cwdStr).filter(_.nonEmpty).mkString(" ")
    }
}