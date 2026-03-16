package sugarlyzer.tester.tools

import cats.effect.IO
import sugarlyzer.models.ProgramSpecification
import cats.implicits._
import sugarlyzer.common.Config.AppConfig

object PhasarTool extends AnalysisTool {
  def name(): String = { "Phasar" }

  def run(spec: ProgramSpecification)(using
      config: AppConfig
  ): IO[List[ToolAlarm]] = {
    for {
      _       <- IO.println(s"Running WLLVM strategy for ${spec}")
      bcFiles <- extractBitcode(spec.rootDir, spec.targetBinaries)
      alarms <-
        bcFiles.traverse {
          case (bcFile) => runPhasarOnFile(spec, bcFile)
        }
      flatAlarms = alarms.flatten
      _ <- IO.println(s"[TOOL] Got ${flatAlarms.length} alarms")
    } yield flatAlarms
  }

  def extractBitcode(
      targetDir: String,
      targetBinaries: List[String]
  ): IO[List[String]] = {
    val targetPath = os.Path(targetDir)

    targetBinaries.traverse { targetBinary =>
      IO.blocking {
        val binaryPath = targetPath / os.RelPath(targetBinary)
        if (os.exists(binaryPath)) {
          val proc = os.proc("extract-bc", binaryPath.toString)
            .call(
              cwd = os.Path(targetDir)
            )

          if (proc.exitCode != 0)
            throw new RuntimeException(
              s"extract-bc failed: ${proc.err.text()}"
            )

          val bcPath = s"${binaryPath}.bc"
          if (!os.exists(os.Path(bcPath)))
            println(s"extract-bc ran but output file missing: $bcPath")

          Some(bcPath)
        } else {
          println(s"${binaryPath} does not exist")
          None
        }
      }
    }.map(_.flatten)
  }

  def runPhasarOnFile(
      spec: ProgramSpecification,
      bcFile: String
  ): IO[List[ToolAlarm]] =
    IO.blocking {
      val targetDir  = spec.rootDir
      val bcName     = os.Path(bcFile).baseName
      val resultsDir = os.Path(targetDir) / s"${bcName}_results"
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

      if (proc.exitCode != 0) {
        println(s"Phasar Failed. Exit code: ${proc.exitCode}")
        List.empty[ToolAlarm]: Unit
      }

      val reportFileOpt = os.walk(resultsDir)
        .find(_.last == "psr-report.txt")

      reportFileOpt match {
        case Some(reportFile) =>
          parseOutput(spec, os.read(reportFile))
        case None =>
          List.empty[ToolAlarm]
      }

    }

  def parseOutput(
      spec: ProgramSpecification,
      content: String
  ): List[ToolAlarm] = {
    val lineRegex = """Line\s+:\s+(\d+)""".r
    val fileRegex = """File\s+:\s+(.+)""".r
    val funcRegex = """Function\s+:\s+(.+)""".r

    content.split("---------------------------------").drop(1).flatMap {
      chunk =>
        for {
          line <- lineRegex.findFirstMatchIn(chunk).map(_.group(1).toInt)
          file <- fileRegex.findFirstMatchIn(chunk).map(_.group(1))
          if file != "Unknown"
          func <- funcRegex.findFirstMatchIn(chunk).map(_.group(1))
          if func != "Unknown"
        } yield ToolAlarm(
          alarmType = "UninitializedVariable",
          description = s"Uninitialized variable potential in $func",
          line = line,
          fileLocation = spec.rootDir + "/" + file,
          analysisTime = 0.0
        )
    }.toList
  }

}
