package sugarlyzer.util

import java.io.File
import scala.sys.process._
import os.Path
import cats.effect.Resource
import cats.effect.IO
import cats.syntax.all._
import cats.Show
import java.io.{PrintWriter, FileWriter}
import scala.concurrent.duration.FiniteDuration
import java.util.concurrent.TimeoutException

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

  import CommandBuilder.{LogFile, ResultFile}
  def runWithFileRedirects(
      outputFile: Path,
      logFile: Path,
      timeout: Option[FiniteDuration] = None
  ): IO[(ResultFile, LogFile)] = {
    val pb = build
    val stdoutWriter = Resource.fromAutoCloseable(
      IO.blocking(PrintWriter(FileWriter(File(outputFile.toURI))))
    )
    val stderrWriter = Resource.fromAutoCloseable(
      IO.blocking(PrintWriter(FileWriter(File(logFile.toURI))))
    )
    (stdoutWriter, stderrWriter).tupled.use { (stdoutWriter, stderrWriter) =>
      val pLogger = ProcessLogger(
        fout = line => stdoutWriter.println(line),
        ferr = line => stderrWriter.println(line)
      )
      val flush =
        IO.blocking(stdoutWriter.flush()) >> IO.blocking(stderrWriter.flush())
      timeout match {
        case None =>
          IO.blocking(pb.!(pLogger)).flatMap { status =>
            IO.println(status) >> flush >> IO.pure((ResultFile(outputFile), LogFile(logFile)))
          }
        case Some(duration) =>
          IO.blocking(pb.run(pLogger)).flatMap { process =>
            val waitForProcess    = IO.blocking(process.exitValue())
            val killAfterTimeout  = IO.sleep(duration) >> IO.blocking(process.destroy())
            IO.race(waitForProcess, killAfterTimeout).flatMap {
              case Left(status) =>
                IO.println(status) >> flush >> IO.pure((ResultFile(outputFile), LogFile(logFile)))
              case Right(_) =>
                IO.raiseError(new TimeoutException(s"Process timed out after $duration"))
            }
          }
      }
    }
  }
}

object CommandBuilder {
  opaque type ResultFile = Path
  opaque type LogFile    = Path

  object ResultFile {
    def apply(p: os.Path): ResultFile = p
  }

  object LogFile {
    def apply(p: os.Path): LogFile = p
  }

  given Show[CommandBuilder] with {
    def show(t: CommandBuilder): String = {
      val envStr = t.env.map((k, v) => s"$k=$v").mkString(" ")
      val cwdStr = t.workingDir.map(d => s"(in ${d.getPath})").getOrElse("")
      val cmdStr = (t.program +: t.args).mkString(" ")
      Seq(envStr, cmdStr, cwdStr).filter(_.nonEmpty).mkString(" ")
    }
  }
}
