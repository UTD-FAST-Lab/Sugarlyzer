package sugarlyzer.tester.test

import cats.effect.IOApp
import cats.effect.IO
import sugarlyzer.tester.sugarc.SugarCRunner
object MainApp extends IOApp.Simple {
  def run: IO[Unit] = {
    val sample1 = "/resources/sample1.c"
    val io = for {
      _                  <- IO.println("Starting tester integration tests...")
      _                  <- IO.println(s"Testing on ${sample1}")
      (resFile, logFile) <- analyzeFile(sample1)
    } yield (println(s"Logfile at $logFile, resFile at $resFile"))
    io
  }

  def analyzeFile(file: String) = SugarCRunner.desugarFile(
    fileToDesugar = os.Path(file),
    logFile = os.Path("/log.txt"),
    recommendedSpace = None,
    noStdLibs = false,
    keepMem = true,
    makeMain = false,
    includedFiles = List.empty,
    includedDirectories = List.empty,
    commandLineDeclarations = List.empty
  )
}
