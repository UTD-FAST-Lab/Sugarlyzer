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
      _      <- IO.println(s"Running spec ${spec}")
      alarms <- analyzeFiles(spec)
    } yield (alarms)
  }

  def analyzeFiles(
      spec: ProgramSpecification
  ): IO[List[Alarm]] = {
    val rootDir             = os.Path(spec.rootDir)
    val compileCommandsPath = rootDir / "compile_commands.json"

    os.proc(
      "sed",
      "-i",
      "s/-fno-guess-branch-probability//g",
      compileCommandsPath.toString
    )
      .call(cwd = rootDir)

    for {
      commands <- CompileCommands.parse(compileCommandsPath)

      alarms <- commands.zipWithIndex.parTraverseN(
        Runtime.getRuntime().availableProcessors()
      ) {
        case (cmd, i) =>
          IO.blocking {
            val uniqueResultsDir =
              os.Path(spec.rootDir) / "clang_results" / s"out-$i"
            os.remove.all(uniqueResultsDir)
            os.makeDir.all(uniqueResultsDir)

            val reportXMLLocation = uniqueResultsDir / "report.plist"

            def filterOutputFlag(args: List[String]): List[String] =
              args match {
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
              cleanCmdArgs.drop(1)
            ).call(
              cwd = os.Path(cmd.directory),
              stdout = os.Inherit,
              mergeErrIntoOut = true,
              check = false
            )

            if (proc.exitCode != 0)
              throw new RuntimeException("Failed to run clang analysis")

            reportXMLLocation
          }
            .flatMap { path =>
              parseOutput(path)
            }
      }
    } yield alarms.flatten
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
        file = fileName
      )
    }.toList
  }

}
