package sugarlyzer.tester.tools

import cats.effect.IO
import cats.syntax.all.*

import sugarlyzer.models.ProgramSpecification
import sugarlyzer.tester.parsing.{
  CompileCommand,
  CommandContext,
  CompileCommands
}

import org.eclipse.cdt.core.dom.ast.gnu.c.GCCLanguage
import org.eclipse.cdt.core.dom.ast.IASTFunctionDefinition
import org.eclipse.cdt.core.parser.FileContent
import org.eclipse.cdt.core.parser.ScannerInfo
import org.eclipse.cdt.core.parser.DefaultLogService
import org.eclipse.cdt.core.parser.IncludeFileContentProvider
import org.eclipse.cdt.core.model.ILanguage

import com.github.tototoshi.csv.CSVReader
import scala.util.control.NonFatal
import com.typesafe.scalalogging.Logger
import com.github.tototoshi.csv.DefaultCSVFormat

object FramaCTool extends AnalysisTool {
  val logger         = Logger[FramaCTool.type]
  def name(): String = "Frama-C"

  def run(spec: ProgramSpecification): IO[List[ToolAlarm]] = {
    for {
      _      <- IO.println(s"[TOOL] Running spec ${spec}")
      alarms <- analyzeFiles(spec)
      _      <- IO.println(s"[TOOL] Got ${alarms.length} alarms")
    } yield alarms
  }

  def analyzeFiles(spec: ProgramSpecification): IO[List[ToolAlarm]] = {
    val rootDir             = os.Path(spec.rootDir)
    val compileCommandsPath = rootDir / "compile_commands.json"

    for {
      commands <- CompileCommands.parse(compileCommandsPath)
      alarms <- commands.zipWithIndex.traverse { case (cmd, cmdIdx) =>
        for {
          ctx       <- IO.blocking(CompileCommands.extractContext(cmd))
          functions <- IO.blocking(parseFunctions(ctx.file))
          results <- functions.zipWithIndex.traverse {
            case (funcName, funcIdx) =>
              runFramaC(
                spec,
                cmd,
                ctx,
                cmdIndex = cmdIdx,
                funcIndex = funcIdx,
                funcName
              )
          }
        } yield results.flatten
      }
    } yield alarms.flatten
  }

  def parseFunctions(file: os.Path): List[String] = {
    if (!os.exists(file)) return List.empty
    try {
      val fileContent =
        FileContent.create(file.toString, os.read(file).toCharArray())
      val scanInfo      = ScannerInfo(java.util.HashMap(), Array[String]())
      val parserLog     = DefaultLogService()
      val emptyIncludes = IncludeFileContentProvider.getEmptyFilesProvider()

      val tu = GCCLanguage.getDefault().getASTTranslationUnit(
        fileContent,
        scanInfo,
        emptyIncludes,
        null,
        ILanguage.OPTION_IS_SOURCE_UNIT,
        parserLog
      )

      tu.getDeclarations().toList.collect {
        case fd: IASTFunctionDefinition =>
          fd.getDeclarator().getName().toString
      }.filter(_.nonEmpty)
    } catch {
      case NonFatal(e) =>
        println(s"Failed to parse functions from $file: ${e.getMessage}")
        List.empty
    }
  }

  def runFramaC(
      spec: ProgramSpecification,
      cmd: CompileCommand,
      ctx: CommandContext,
      cmdIndex: Int,
      funcIndex: Int,
      funcName: String
  ): IO[List[ToolAlarm]] = IO.blocking {
    val rootDir  = os.Path(spec.rootDir)
    val safeFunc = funcName.replaceAll("[^a-zA-Z0-9_]", "_")
    val resultDir =
      rootDir / "framac_results" / s"out-${cmdIndex}-${funcIndex}-${safeFunc}"
    os.remove.all(resultDir)
    os.makeDir.all(resultDir)

    val csvOutput = resultDir / "report.csv"
    val incFlags  = ctx.incDirs.flatMap(d => List("-I", d.toString))

    // -D/-U and -include must go through -cpp-extra-args in Frama-C
    val defArgs = ctx.cmdLineDefs.grouped(2).collect { case List(f, v) =>
      s"$f$v"
    }.toList
    val includeArgs = ctx.incFiles.map(f => s"-include ${f.toString}")
    val cppExtras   = defArgs ++ includeArgs
    val cppExtraArg =
      if (cppExtras.nonEmpty)
        List(s"""-cpp-extra-args="${cppExtras.mkString(" ")}"""")
      else List.empty

    val start = System.nanoTime()

    val proc = os.proc(
      List("frama-c", "-eva", "-main", funcName) ++
        incFlags ++ cppExtraArg ++
        List(
          ctx.file.toString,
          "-then",
          "-report",
          "-report-csv",
          csvOutput.toString
        )
    ).call(
      cwd = os.Path(cmd.directory),
      stdout = os.Inherit,
      mergeErrIntoOut = true,
      check = false
    )

    val end          = System.nanoTime()
    val analysisTime = (end - start) / 1e9

    if (proc.exitCode != 0)
      println(
        s"Frama-C failed for $funcName in ${ctx.file.last}: exit ${proc.exitCode}"
      )

    val alarms = parseCSV(csvOutput, analysisTime)
    logger.info(s"Alarms are ${alarms}")
    alarms
  }

  def parseCSV(csvPath: os.Path, analysisTime: Double): List[ToolAlarm] = {
    if (!os.exists(csvPath)) return List.empty
    try {
      logger.info(s"Opening $csvPath")
      given csvFormat: DefaultCSVFormat {
        override val delimiter: Char = '\t'
      }
      val reader = CSVReader.open(csvPath.toIO)
      try {
        reader.allWithHeaders().flatMap { row =>
          logger.info(s"row is $row")
          val file   = row.getOrElse("file", "")
          val lineNo = row.get("line").flatMap(_.toIntOption).getOrElse(0)
          val kind   = row.getOrElse("property kind", "")
          val status = row.getOrElse("status", "")
          if (file.nonEmpty) {
            val fullDesc = if (status.nonEmpty) s"[$kind] $status" else kind
            Some(ToolAlarm(
              alarmType = kind,
              description = fullDesc,
              fileLocation = file,
              line = lineNo,
              analysisTime = analysisTime
            ))
          } else None
        }
      } finally {
        reader.close()
      }
    } catch {
      case NonFatal(e) =>
        println(s"Failed to parse CSV at $csvPath: ${e.getMessage}")
        List.empty
    }
  }
}
