package sugarlyzer.tester.test

import cats.effect.IOApp
import cats.effect.IO
import sugarlyzer.tester.sugarc.SugarCRunner
import sugarlyzer.util.CommandBuilder.ResultFile
import sugarlyzer.util.CommandBuilder.LogFile
import com.microsoft.z3.*
import sugarlyzer.tester.sugarc.PresenceConditionParser
import sugarlyzer.tester.tools.ToolAlarm

object MainApp extends IOApp.Simple {
  def run: IO[Unit] = {
    val sample1 = "/resources/sample1.c"
    for {
      _ <- IO.println("Starting tester integration tests...")
      _ <- IO.println("=== INTEGRATION TEST 1: SugarC Integration ===")
      _ <- IO.println(s"Testing on ${sample1}")
      (resFile, logFile) <- analyzeFile(sample1)
      _ <- IO.println(s"Logfile at $logFile, resFile at $resFile")
      _ <- IO.println("=== INTEGRATION TEST 2: Z3 Test ===")
      _ <- IO.println("Checking that Z3 works")
      _ <- testZ3()
      _ <-
        IO.println("=== INTEGRATION TEST 3: Presence Condition Extraction ===")
      _ <- IO.println("Testing presence condition extraction for sample1")
      _ <- testAlarmPresenceCondition()
      _ <- IO.println("=== INTEGRATION TEST 4: Presence Condition Parser ===")
      _ <-
        IO.println("Testing presence condition parser with sample expression")
      _ <- IO.println("=== INTEGRATION TEST 5: Macro Combinations ===")
      _ <- testExhaustively(sample1)
    } yield ()
  }

  def testExhaustively(file: String): IO[Unit] = {
    IO.println(
      s"Exhaustive sample for ${file} are ${ProductStrategy.exhaustivelySample(os.Path(file))}"
    )
  }

  def analyzeFile(file: String): IO[(ResultFile, LogFile)] =
    SugarCRunner.desugarFile(
      fileToDesugar = os.Path(file),
      logFile = os.Path("/log.txt"),
      recommendedSpace = None,
      noStdLibs = true,
      keepMem = true,
      makeMain = true,
      includedFiles = List(
        "/SugarlyzerConfig/baseInc.h"
      ),
      includedDirectories = List(
        "/SugarlyzerConfig",
        "/SugarlyzerConfig/stdinc/usr/include",
        "/SugarlyzerConfig/stdinc/usr/include/x86_64-linux-gnu",
        "/SugarlyzerConfig/stdinc/usr/lib/gcc/x86_64-linux-gnu/9/include"
      ),
      commandLineDeclarations = List.empty
    )

  def testZ3(): IO[Unit] = {
    println("Creating Z3 context")
    val ctx = Context()

    // Simple boolean example
    val boolExprX = ctx.mkBoolConst("x")
    val boolExprY = ctx.mkBoolConst("y")
    val solver    = ctx.mkSolver()
    solver.add(ctx.mkAnd(boolExprX, ctx.mkNot(boolExprY)))

    if (solver.check() == Status.SATISFIABLE) {
      println("SAT")
      println("Model: " + solver.getModel())
    }

    ctx.close()
    IO.println("Success!")
  }

  def testAlarmPresenceCondition(): IO[Unit] = {
    val alarm = ToolAlarm(
      fileLocation = "/resources/sample1.desugared.c",
      line = 32,
      alarmType = "Sample",
      description = "Sample",
      analysisTime = 1.0
    )
    val model = SugarCRunner.findPresenceCondition(
      alarm,
      os.Path("/resources/sample1.desugared.c")
    )
    IO.println(s"Model: ${model}")
  }

  def testPresenceConditionParser(): IO[Unit] = {
    val ctx = Context()
    val expr = PresenceConditionParser.parse(
      ctx,
      "(defined cond1) && ((defined cond2) || !(defined cond3) && (cond4 == 5))"
    )
    IO.println(s"Parsed expression: $expr")
  }
}
