package sugarlyzer.tester.tools

import cats.effect.IO
import sugarlyzer.models.ProgramSpecification

object PhasarTool extends AnalysisTool {
  def name(): String = { "Phasar" }

  def run(spec: ProgramSpecification): IO[List[Alarm]] = {
    for {
      _      <- IO.println(s"Running WLLVM strategy for ${spec}")
      _      <- buildWithWLLVM(spec)
      bcFile <- extractBitcode(spec.targetDir, "axssl")
      alarms <- runPhasarOnFile(spec.targetDir, bcFile)
    } yield alarms
  }

  def buildWithWLLVM(spec: ProgramSpecification): IO[Unit] = IO.blocking {
    val proc = os.proc("make", "CC=wllvm")
      .call(
        cwd = os.Path(spec.targetDir),
        stdout = os.Inherit,
        mergeErrIntoOut = true
      )

    if (proc.exitCode != 0)
      throw new RuntimeException(s"WLLVM Build failed: ${proc.out.text()}")
  }

  def extractBitcode(targetDir: String, binaryName: String): IO[String] =
    IO.blocking {
      val binaryPath = os.walk(os.Path(targetDir))
        .find(p => p.last == binaryName && os.isFile(p))
        .getOrElse(throw new RuntimeException(
          s"Could not find binary named '$binaryName' in $targetDir"
        ))

      println(s"Found binary at: $binaryPath")

      val proc = os.proc("extract-bc", binaryPath.toString)
        .call(
          cwd = os.Path(targetDir)
        )

      if (proc.exitCode != 0)
        throw new RuntimeException(s"extract-bc failed: ${proc.err.text()}")

      val bcPath = s"${binaryPath}.bc"
      if (!os.exists(os.Path(bcPath)))
        throw new RuntimeException(
          s"extract-bc ran but output file missing: $bcPath"
        )

      println(s"Extracted bitcode to: $bcPath")
      bcPath
    }

  def runPhasarOnFile(targetDir: String, bcFile: String): IO[List[Alarm]] =
    IO.blocking {
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

      if (proc.exitCode != 0)
        throw new RuntimeException(s"Phasar failed: ${proc.err.text()}")

      val reportFileOpt = os.walk(resultsDir)
        .find(_.last == "psr-report.txt")

      reportFileOpt match {
        case Some(reportFile) =>
          println(s"Found report at: $reportFile")
          parseOutput(os.read(reportFile))
        case None =>
          println(
            s"Warning: 'psr-report.txt' not found anywhere in $resultsDir. " +
              s"Root contents: ${os.list(resultsDir).map(_.last).mkString(", ")}"
          )
          List.empty[Alarm]
      }

    }

  def parseOutput(content: String): List[Alarm] = {
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
        } yield Alarm(
          bug_type = "UninitializedVariable",
          qualifier = s"Uninitialized variable potential in $func",
          line = line,
          column = 0,
          file = file
        )
    }.toList
  }

}
