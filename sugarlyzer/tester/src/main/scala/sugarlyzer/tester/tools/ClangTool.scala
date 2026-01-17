package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

import cats.effect.{IO}
import os._
import sugarlyzer.tester.parsing._
import cats.effect.syntax.all._
import com.dd.plist.PropertyListParser
import com.dd.plist.NSDictionary
import com.dd.plist.NSArray

object ClangTool extends AnalysisTool {
  def name(): String = { "Clang" }

  def run(spec: ProgramSpecification): IO[List[Alarm]] = {
    for {
      _        <- IO.println(s"Running spec ${spec}")
      _        <- applyConfiguration(spec)
      commands <- getCompileCommands(spec)
      _        <- IO.println(s"Found ${commands.size} commands")
      alarms   <- analyzeFiles(spec, commands)
    } yield (alarms)
  }

  def analyzeFiles(
      spec: ProgramSpecification,
      compileCommands: List[CompileCommand]
  ): IO[List[Alarm]] = {
    val indexedCommands = compileCommands.zipWithIndex

    indexedCommands.parTraverseN(Runtime.getRuntime().availableProcessors()) {
      case (cmd, i) =>
        IO.blocking {
          val uniqueResultsDir =
            os.Path(spec.targetDir) / "clang_results" / s"out-$i"
          if (os.exists(uniqueResultsDir)) os.remove.all(uniqueResultsDir)
          val reportXMLLocation = uniqueResultsDir / "report.plist"

          if (!os.exists(reportXMLLocation)) {
            os.makeDir.all(uniqueResultsDir)
          }

          def filterOutputFlag(args: List[String]): List[String] = args match {
            case "-o" :: _ :: tail => filterOutputFlag(tail)
            case head :: tail      => head :: filterOutputFlag(tail)
            case Nil               => Nil
          }

          val cleanCmdArgs = filterOutputFlag(cmd.arguments)

          val proc = os.proc(
            "clang-11",
            "--analyze",
            "-Xanalyzer",
            "-analyzer-output=plist",
            "-o",
            reportXMLLocation.toString,
            cleanCmdArgs
          ).call(
            cwd = os.Path(cmd.directory),
            stderr = os.Pipe,
            mergeErrIntoOut = true,
            check = false
          )

          println(s"Clang command: ${proc.command}")

          if (proc.exitCode != 0)
            throw new RuntimeException("Failed to run infer analysis")

          reportXMLLocation
        }
          .flatMap { path =>
            parseOutput(path)
          }
    }.map(_.flatten)
  }

  def getCompileCommands(spec: ProgramSpecification)
      : IO[List[CompileCommand]] = {

    val targetPath          = os.Path(spec.targetDir)
    val compileCommandsFile = targetPath / os.up / "compile_commands.json"

    val runBear = IO.blocking {
      val proc = os.proc(
        "bear",
        "--output",
        compileCommandsFile.toString,
        "--",
        "make"
      ).call(cwd = targetPath)
      if (proc.exitCode != 0)
        throw new RuntimeException("Failed to run bear")
    }

    for {
      _        <- runBear
      commands <- CompileCommands.parse(compileCommandsFile)
    } yield commands
  }

  def applyConfiguration(spec: ProgramSpecification): IO[Unit] = IO.blocking {
    val proc = os.proc("bash", "-c", spec.buildCommand).call(
      cwd = os.Path(spec.targetDir)
    )
    if (proc.exitCode != 0) {
      throw new RuntimeException(
        s"Failed to run build command: ${spec.buildCommand}"
      )
    }
  }

  def parseOutput(resultPath: os.Path): IO[List[Alarm]] = IO.blocking {
    val file = resultPath.toIO

    val rootDict = PropertyListParser.parse(file).asInstanceOf[NSDictionary]

    val filesArray = rootDict.objectForKey("files").asInstanceOf[NSArray]
    val fileNames  = filesArray.getArray.map(_.toString)

    val diagnostics = rootDict.objectForKey("diagnostics").asInstanceOf[NSArray]

    (0 until diagnostics.count()).map { i =>
      val bugDict = diagnostics.objectAtIndex(i).asInstanceOf[NSDictionary]

      val bugType = bugDict.objectForKey("check_name").toString

      val description = bugDict.objectForKey("description").toString

      val locDict = bugDict.objectForKey("location").asInstanceOf[NSDictionary]
      val line    = locDict.objectForKey("line").toString.toInt
      val col     = locDict.objectForKey("col").toString.toInt
      val fileIdx = locDict.objectForKey("file").toString.toInt

      val fileName =
        if (fileIdx < fileNames.length) fileNames(fileIdx) else "Unknown"

      Alarm(
        bug_type = bugType,
        qualifier = description,
        line = line,
        column = col,
        procedure_start_line = 0,
        file = fileName
      )
    }.toList
  }

}
