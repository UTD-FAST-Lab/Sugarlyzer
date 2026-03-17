package sugarlyzer.tester.parsing

import cats.effect.{IO}

import io.circe.Decoder
import io.circe.Encoder
import io.circe.jawn.decodeFile
import os._
import scala.annotation.tailrec

case class CompileCommand(
    directory: String,
    file: String,
    output: Option[String],
    arguments: List[String]
) derives Decoder, Encoder

case class CommandContext(
    file: os.Path,
    incDirs: List[os.Path],
    incFiles: List[os.Path],
    cmdLineDefs: List[String]
)

object CompileCommands {
  def parse(jsonPath: Path): IO[List[CompileCommand]] = IO.blocking {
    val file = jsonPath.toIO

    decodeFile[List[CompileCommand]](file) match {
      case Right(commands) => commands
      case Left(error) => throw new RuntimeException(
          s"Failed to parse compile commands json file (${jsonPath.toString}): $error"
        )
    }
  }

  def extractContext(cmd: CompileCommand): CommandContext = {
    val baseDir    = os.Path(cmd.directory, os.pwd)
    val sourceFile = os.Path(cmd.file, baseDir)

    @tailrec
    def parseArgs(
        remaining: List[String],
        incDirs: List[os.Path] = Nil,
        incFiles: List[os.Path] = Nil,
        defines: List[String] = Nil
    ): (List[os.Path], List[os.Path], List[String]) = remaining match {
      case Nil =>
        (incDirs.reverse, incFiles.reverse, defines.reverse)

      case "-I" :: path :: tail =>
        parseArgs(tail, os.Path(path, baseDir) :: incDirs, incFiles, defines)

      case "-include" :: file :: tail =>
        parseArgs(tail, incDirs, os.Path(file, baseDir) :: incFiles, defines)

      case (flag @ ("-D" | "-U")) :: macroDef :: tail =>
        parseArgs(tail, incDirs, incFiles, macroDef :: flag :: defines)

      case arg :: tail if arg.startsWith("-D") || arg.startsWith("-U") =>
        val flag     = arg.substring(0, 2)
        val macroDef = arg.substring(2)
        parseArgs(tail, incDirs, incFiles, macroDef :: flag :: defines)

      case arg :: tail if arg.startsWith("-I") =>
        parseArgs(
          tail,
          os.Path(arg.substring(2), baseDir) :: incDirs,
          incFiles,
          defines
        )
      case _ :: tail =>
        parseArgs(tail, incDirs, incFiles, defines)
    }

    val (dirs, files, defs) = parseArgs(cmd.arguments)
    CommandContext(
      file = sourceFile,
      incDirs = dirs,
      incFiles = files,
      cmdLineDefs = defs
    )
  }
}
