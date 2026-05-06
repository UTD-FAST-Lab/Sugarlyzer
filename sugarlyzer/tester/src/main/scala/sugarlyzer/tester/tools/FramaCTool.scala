package sugarlyzer.tester.tools

import sugarlyzer.common.Config.AppConfig

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

import scala.util.control.NonFatal

object FramaCTool extends AnalysisTool {
  def name(): String = "Frama-C"

  def run(spec: ProgramSpecification)(using
      config: AppConfig
  ): IO[List[ToolAlarm]] = {
    for {
      _      <- IO.println(s"[TOOL] Running spec ${spec}")
      alarms <- analyzeFiles(spec)
      _      <- IO.println(s"[TOOL] Got ${alarms.length} alarms")
    } yield alarms
  }

  def analyzeFiles(spec: ProgramSpecification)(using
      config: AppConfig
  ): IO[List[ToolAlarm]] = {
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

    val csvOutput    = resultDir / "report.csv"
    val incFlags     = ctx.incDirs.flatMap(d => List("-I", d.toString))
    val includeFlags = ctx.incFiles.flatMap(f => List("-include", f.toString))

    val start = System.nanoTime()

    val proc = os.proc(
      List("frama-c", "-eva", "-main", funcName) ++
        incFlags ++ includeFlags ++ ctx.cmdLineDefs ++
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

    parseCSV(csvOutput, analysisTime)
  }

  def parseCSV(csvPath: os.Path, analysisTime: Double): List[ToolAlarm] = {
    if (!os.exists(csvPath)) return List.empty
    try {
      val lines = os.read.lines(csvPath).toList
      if (lines.size <= 1) return List.empty

      val headers = parseCSVRow(lines.head).map(_.toLowerCase.trim)
      val fileIdx = headers.indexWhere(h => h == "source file" || h == "file")
      val lineIdx = headers.indexWhere(h => h == "line")
      val kindIdx =
        headers.indexWhere(h => h.contains("kind") || h == "property")
      val statusIdx = headers.indexWhere(h => h == "status")
      val descIdx   = headers.indexWhere(h => h.contains("desc"))

      lines.tail.flatMap { rawLine =>
        val cols = parseCSVRow(rawLine)
        def col(idx: Int): String =
          if (idx >= 0 && idx < cols.length) cols(idx) else ""

        val file   = col(fileIdx)
        val lineNo = col(lineIdx).toIntOption.getOrElse(0)
        val kind   = col(kindIdx)
        val status = col(statusIdx)
        val desc   = col(descIdx)

        if (file.nonEmpty) {
          val fullDesc = if (status.nonEmpty) s"[$status] $desc" else desc
          Some(ToolAlarm(
            alarmType = kind,
            description = fullDesc,
            fileLocation = file,
            line = lineNo,
            analysisTime = analysisTime
          ))
        } else None
      }
    } catch {
      case NonFatal(e) =>
        println(s"Failed to parse CSV at $csvPath: ${e.getMessage}")
        List.empty
    }
  }

  private def parseCSVRow(line: String): List[String] = {
    val buf      = scala.collection.mutable.ListBuffer[String]()
    val field    = new StringBuilder
    var inQuotes = false
    var i        = 0
    while (i < line.length) {
      line.charAt(i) match {
        case '"'
            if inQuotes && i + 1 < line.length && line.charAt(i + 1) == '"' =>
          field.append('"')
          i += 1
        case '"' =>
          inQuotes = !inQuotes
        case ',' if !inQuotes =>
          buf += field.toString
          field.clear()
        case c =>
          field.append(c)
      }
      i += 1
    }
    buf += field.toString
    buf.toList
  }
}
