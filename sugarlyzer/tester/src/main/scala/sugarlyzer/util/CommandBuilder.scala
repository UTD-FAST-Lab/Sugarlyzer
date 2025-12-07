package sugarlyzer.util

import java.io.File
import scala.sys.process._
import os.Path
import cats.effect.Resource
import cats.effect.IO
import cats.syntax.all._
import cats.Show
import java.io.{PrintWriter, FileWriter}

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
  def runWithFileRedirects(
      outputFile: Path,
      logFile: Path
  ): IO[(Path, Path)] = {
    val pb = build
    val stdoutWriter = Resource.fromAutoCloseable(
      IO.blocking(PrintWriter(FileWriter(File(outputFile.toURI))))
    )
    val stderrWriter = Resource.fromAutoCloseable(
      IO.blocking(PrintWriter(FileWriter(File(logFile.toURI))))
    )

    (stdoutWriter, stderrWriter).tupled.use { (stdoutWriter, stderrWriter) =>
      IO.blocking {
        pb.!(ProcessLogger(
          fout = line => stdoutWriter.println(line),
          ferr = line => stderrWriter.println(line)
        ))
      }.flatMap { status =>
        if status == 0 then IO.pure((outputFile, logFile))
        else IO.raiseError(RuntimeException(
          s"Desugaring to file ${outputFile.toString} ended with ${status} exit code."
        ))
      }
    }
  }
}

object CommandBuilder {
  given Show[CommandBuilder] with {
    def show(t: CommandBuilder): String = {
      val envStr = t.env.map((k, v) => s"$k=$v").mkString(" ")
      val cwdStr = t.workingDir.map(d => s"(in ${d.getPath})").getOrElse("")
      val cmdStr = (t.program +: t.args).mkString(" ")
      Seq(envStr, cmdStr, cwdStr).filter(_.nonEmpty).mkString(" ")
    }
  }
}
