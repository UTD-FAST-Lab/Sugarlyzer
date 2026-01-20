package sugarlyzer.tester.tools

import cats.effect.IO
import sugarlyzer.models.ProgramSpecification
import sugarlyzer.tester.parsing._
import cats.effect.syntax.all._

object PhasarTool extends AnalysisTool {
  def name(): String = { "Phasar" }

  def run(spec: ProgramSpecification): IO[List[Alarm]] = {
    for {
      _        <- IO.println(s"Running spec ${spec}")
      _        <- applyConfiguration(spec)
      commands <- getCompileCommands(spec)
      _        <- IO.println(s"Found ${commands.size} commands")
      alarms   <- analyzeFiles(spec, commands)
    } yield alarms
  }

  def analyzeFiles(
      spec: ProgramSpecification,
      compileCommands: List[CompileCommand]
  ): IO[List[Alarm]] = {

    val compileStep: IO[List[String]] =
      compileCommands.parTraverseN(Runtime.getRuntime().availableProcessors()) {
        case (cmd) => toLLVM(cmd)
      }

    for {
      llFiles <- compileStep
      filteredFiles = llFiles.filterNot { file =>
        val lower        = file.toLowerCase
        val isLibrary    = lower.contains("/ssl/") || lower.contains("/crypto/")
        val isEntryPoint = lower.endsWith("samples/c/axssl.c.ll")
        isLibrary || isEntryPoint
      }

      _ <- IO.println(
        s"Filtering: Reduced ${llFiles.size} files to ${filteredFiles.size} to avoid duplicate mains."
      )

      bcFile <- linkBitcode(spec.targetDir, filteredFiles)

      alarms <- runPhasarOnFile(spec.targetDir, bcFile)
    } yield alarms
  }

  def runPhasarOnFile(targetDir: String, bcFile: String) = IO.blocking {
    val resultsDir = os.Path(targetDir) / "phasar_results"
    if (os.exists(resultsDir)) os.remove.all(resultsDir)
    os.makeDir.all(resultsDir)

    val proc = os.proc(
      "/phasar/build/tools/phasar-llvm/phasar-llvm",
      "-D",
      "IFDSUninitializedVariables",
      "-m",
      bcFile,
      "-O",
      resultsDir.toString,
      "--emit-text-report"
    ).call(
      cwd = os.Path(targetDir),
      stdout = os.Inherit,
      mergeErrIntoOut = true,
      check = false
    )
    println(s"Running phasar-llvm cmd: ${proc.command}")

    if (proc.exitCode != 0)
      throw new RuntimeException(
        s"Failed to run phasar-llvm. Exit Code: ${proc.exitCode}"
      )

    val reportFile = os.list(resultsDir).find(_.ext == "txt").getOrElse(
      throw new RuntimeException("Failed to find phasar report file")
    )

    parseOutput(os.read(reportFile))
  }

  def linkBitcode(targetDir: String, llFiles: List[String]): IO[String] =
    IO.blocking {
      val outFile = os.Path(targetDir) / "whole_program.bc"

      val proc = os.proc(
        "llvm-link",
        "-o",
        outFile.toString,
        llFiles
      ).call(cwd = os.Path(targetDir))

      if (proc.exitCode != 0)
        throw new RuntimeException(s"Failed to link bitcode files")

      outFile.toString
    }

  def toLLVM(cmd: CompileCommand): IO[String] = IO.blocking {
    val llFile = s"${cmd.file}.ll"

    def filterOutputFlag(args: List[String]): List[String] = args match {
      case "-o" :: _ :: tail => filterOutputFlag(tail)
      case head :: tail      => head :: filterOutputFlag(tail)
      case Nil               => Nil
    }

    val argsWithoutCompiler =
      if (cmd.arguments.nonEmpty) cmd.arguments.drop(1) else Nil

    val cleanCmdArgs = filterOutputFlag(argsWithoutCompiler).distinct

    println(s"Running clang-12 cmd: ${cleanCmdArgs}")
    println(s"Output file: $llFile")

    val toLLProc = os.proc(
      "clang-12",
      "-emit-llvm",
      "-S",
      "-fno-discard-value-names",
      "-c",
      "-g",
      cleanCmdArgs,
      "-o",
      llFile
    ).call(
      cwd = os.Path(cmd.directory),
      stderr = os.Pipe,
      mergeErrIntoOut = true,
      check = false
    )

    if (toLLProc.exitCode != 0)
      throw new RuntimeException(s"Failed to compile ${cmd.file} to llvm")

    llFile
  }

  def parseOutput(content: String): List[Alarm] = {
    val lineRegex = """Line\s+:\s+(\d+)""".r
    val fileRegex = """File\s+:\s+(.+)""".r
    val funcRegex = """Function\s+:\s+(.+)""".r

    content.split("---------------------------------").drop(1).map { chunk =>
      val line =
        lineRegex.findFirstMatchIn(chunk).map(_.group(1).toInt).getOrElse(0)
      val file =
        fileRegex.findFirstMatchIn(chunk).map(_.group(1)).getOrElse("Unknown")
      val func =
        funcRegex.findFirstMatchIn(chunk).map(_.group(1)).getOrElse("Unknown")

      Alarm(
        bug_type = "UninitializedVariable",
        qualifier = s"Uninitialized variable potential in $func",
        line = line,
        column = 0,
        file = file
      )
    }.toList
  }

  def getCompileCommands(spec: ProgramSpecification)
      : IO[List[CompileCommand]] = {
    val targetPath          = os.Path(spec.targetDir)
    val compileCommandsFile = targetPath / os.up / "compile_commands.json"

    val runBear = IO.blocking {
      if (os.exists(compileCommandsFile)) os.remove(compileCommandsFile): Unit

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
}
