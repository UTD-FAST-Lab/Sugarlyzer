package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

import cats.effect.{IO}
import os._
import sugarlyzer.tester.parsing._
import cats.effect.syntax.all._
import com.dd.plist.PropertyListParser
import com.dd.plist.NSDictionary
import com.dd.plist.NSArray
import sugarlyzer.common.Config.AppConfig

object ClangTool extends AnalysisTool {
  def name(): String = { "Clang" }

  def run(spec: ProgramSpecification)(using
      config: AppConfig
  ): IO[List[ToolAlarm]] = {
    for {
      _      <- IO.println(s"[TOOL] Running spec ${spec}")
      alarms <- analyzeFiles(spec)
      _      <- IO.println(s"[TOOL] Got ${alarms.length} alarms")
    } yield (alarms)
  }

  def analyzeFiles(
      spec: ProgramSpecification
  )(using config: AppConfig): IO[List[ToolAlarm]] = {
    val rootDir             = os.Path(spec.rootDir)
    val compileCommandsPath = rootDir / "compile_commands.json"

    os.proc(
      "sed",
      "-i",
      "s/-fno-guess-branch-probability//g",
      compileCommandsPath.toString
    ).call(cwd = rootDir): Unit

    for {
      commands <- CompileCommands.parse(compileCommandsPath)

      alarms <- commands.zipWithIndex.traverse {
        case (cmd, i) =>
          IO.blocking {
            val uniqueResultsDir =
              rootDir / "clang_results" / s"out-$i"
            os.remove.all(uniqueResultsDir)
            os.makeDir.all(uniqueResultsDir)

            val reportXMLLocation = uniqueResultsDir / "report.plist"

            def filterFlags(args: List[String]): List[String] = {
              args match {
                case head :: tail if head.startsWith("gcc") || head == "cc" =>
                  filterFlags(tail)
                case "-o" :: _ :: tail =>
                  filterFlags(tail)
                case "" :: tail =>
                  filterFlags(tail)
                case "-fno-guess-branch-probability" :: tail =>
                  filterFlags(tail)
                case head :: tail =>
                  head :: filterFlags(tail)
                case Nil =>
                  Nil
              }
            }

            val cleanCmdArgs = filterFlags(cmd.arguments)

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
              stdout = os.Inherit,
              mergeErrIntoOut = true,
              check = false
            )

            if (proc.exitCode != 0)
              println(
                s"Clang command failed: ${proc.out.text()}, command: ${cmd}"
              )
            reportXMLLocation
          }
            .flatMap { path =>
              parseOutput(spec, path)
            }
      }
    } yield alarms.flatten
  }

  def parseOutput(
      spec: ProgramSpecification,
      resultPath: os.Path
  ): IO[List[ToolAlarm]] = IO.blocking {
    if (!os.exists(resultPath)) {
      List.empty[ToolAlarm]
    } else {
      val file = resultPath.toIO

      val rootDict = PropertyListParser.parse(file).asInstanceOf[NSDictionary]

      val filesArray = rootDict.objectForKey("files").asInstanceOf[NSArray]
      val fileNames  = filesArray.getArray.map(_.toString)

      val diagnostics =
        rootDict.objectForKey("diagnostics").asInstanceOf[NSArray]

      (0 until diagnostics.count()).map { i =>
        val bugDict = diagnostics.objectAtIndex(i).asInstanceOf[NSDictionary]

        val bugType = bugDict.objectForKey("check_name").toString

        val description = bugDict.objectForKey("description").toString

        val locDict =
          bugDict.objectForKey("location").asInstanceOf[NSDictionary]
        // val col     = locDict.objectForKey("col").toString.toInt
        val line    = locDict.objectForKey("line").toString.toInt
        val fileIdx = locDict.objectForKey("file").toString.toInt

        val fileName =
          if (fileIdx < fileNames.length) fileNames(fileIdx) else "Unknown"

        ToolAlarm(
          alarmType = bugType,
          description = description,
          line = line,
          fileLocation = spec.rootDir + "/" + fileName,
          analysisTime = 0.0
        )
      }.toList
    }
  }
}
