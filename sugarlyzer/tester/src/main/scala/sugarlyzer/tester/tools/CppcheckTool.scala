package sugarlyzer.tester.strategies

import cats.effect.IO
import cats.syntax.all._
import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.models.ProgramSpecification
import sugarlyzer.common.Config.AppConfig
import sugarlyzer.tester.tools.ToolAlarm
import sugarlyzer.tester.parsing.CompileCommands
import scala.xml.XML
import scala.util.control.NonFatal

object CppcheckTool extends AnalysisTool {
  def name(): String = { "Cppcheck" }
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

    for {
      commands <- CompileCommands.parse(compileCommandsPath)

      alarms <- commands.zipWithIndex.traverse {
        case (cmd, i) =>
          IO.blocking {
            val uniqueResultsDir =
              rootDir / "cppcheck_results" / s"out-$i"
            os.remove.all(uniqueResultsDir)
            os.makeDir.all(uniqueResultsDir)

            val reportXMLLocation = uniqueResultsDir / "report.xml"

            val start = System.nanoTime()

            val includeFlags = cmd.arguments.filter(_.startsWith("-I"))
            val cppcheckArgs = Seq(
              "cppcheck",
              "--enable=all",
              "--xml",
              "--force",
              "--quiet",
              s"--output-file=${reportXMLLocation.toString}"
            ) ++ includeFlags :+ cmd.file

            val proc = os.proc(cppcheckArgs).call(
              cwd = os.Path(cmd.directory),
              stdout = os.Inherit,
              mergeErrIntoOut = true,
              check = false
            )

            val end          = System.nanoTime()
            val analysisTime = (end - start) / 1e9

            if (proc.exitCode != 0)
              println(
                s"Cppcheck command failed: ${proc.out.text()}, command: ${cmd}"
              )

            (reportXMLLocation, analysisTime)
          }
            .flatMap { case (path, time) =>
              parseOutput(spec, path, time)
            }
      }
    } yield alarms.flatten
  }

  def parseOutput(
      spec: ProgramSpecification,
      resultPath: os.Path,
      analysisTime: Double
  ): IO[List[ToolAlarm]] = IO.blocking {
    if (!os.exists(resultPath)) {
      List.empty[ToolAlarm]
    } else {
      try {
        val xmlRoot    = XML.loadFile(resultPath.toIO)
        val errorNodes = xmlRoot \ "errors" \ "error"
        val rootDir    = os.Path(spec.rootDir)

        errorNodes.toList.flatMap { node =>
          val bugType     = (node \ "@id").text
          val description = (node \ "@msg").text
          val locations   = node \ "location"

          if (locations.isEmpty) {
            List(
              ToolAlarm(
                alarmType = bugType,
                description = description,
                line = 0,
                fileLocation = "Unknown",
                analysisTime = analysisTime
              )
            )
          } else {
            locations.map { loc =>
              val relativeFile = (loc \ "@file").text
              val line         = (loc \ "@line").text.toIntOption.getOrElse(0)

              val absolutePath =
                try {
                  (rootDir / os.RelPath(relativeFile)).toString()
                } catch {
                  case NonFatal(_) => relativeFile
                }

              ToolAlarm(
                alarmType = bugType,
                description = description,
                line = line,
                fileLocation = absolutePath,
                analysisTime = analysisTime
              )
            }.toList
          }
        }
      } catch {
        case NonFatal(e) =>
          println(s"Failed to parse XML at $resultPath: ${e.getMessage}")
          List.empty[ToolAlarm]
      }
    }
  }
}
