package sugarlyzer.tester

import munit.CatsEffectSuite
import com.microsoft.z3.{Context, Status}
import scala.util.Using
import sugarlyzer.tester.sugarc.{PresenceConditionParser, SugarCRunner}
import sugarlyzer.tester.strategies.ProductStrategy

/** Integration tests that need SugarC on the classpath and /SugarlyzerConfig.
  * They run inside the Docker `integration` stage and skip themselves elsewhere.
  */
class IntegrationSuite extends CatsEffectSuite {

  private val configDir = os.root / "SugarlyzerConfig"

  private def hasSugarC: Boolean =
    try { Class.forName("superc.SugarC"); true }
    catch { case _: ClassNotFoundException => false }

  // SugarC is only on the java CLASSPATH env var, not the sbt classpath, so
  // check for the superc checkout as well.
  private def sugarCAvailable: Boolean =
    os.exists(configDir) && (hasSugarC || os.exists(os.root / "superc" / "classes"))

  private def sample1: os.Path = {
    val src = os.Path(java.nio.file.Paths.get(getClass.getClassLoader.getResource("sample1.c").toURI))
    val dir = os.temp.dir()
    os.copy.into(src, dir)
    dir / "sample1.c"
  }

  test("SugarC desugars sample1.c") {
    assume(sugarCAvailable, "SugarC / /SugarlyzerConfig not available")
    val file = sample1
    SugarCRunner.desugarFile(
      fileToDesugar = file,
      logFile = file / os.up / "sample1.log",
      includedFiles = List(configDir / "baseInc.h"),
      includedDirectories = List(
        configDir,
        configDir / "stdinc" / "usr" / "include",
        configDir / "stdinc" / "usr" / "include" / "x86_64-linux-gnu",
        configDir / "stdinc" / "usr" / "lib" / "gcc" / "x86_64-linux-gnu" / "9" / "include"
      )
    ).value.map { result =>
      assert(result.isDefined, "desugarFile returned None")
      val desugared = file / os.up / "sample1.desugared.c"
      assert(os.exists(desugared), s"$desugared was not created")
    }
  }

  test("Z3 native library loads and solves") {
    Using.resource(new Context()) { ctx =>
      val solver = ctx.mkSolver()
      solver.add(ctx.mkAnd(ctx.mkBoolConst("x"), ctx.mkNot(ctx.mkBoolConst("y"))))
      assertEquals(solver.check(), Status.SATISFIABLE)
    }
  }

  test("PresenceConditionParser parses SugarC-style conditions") {
    Using.resource(new Context()) { ctx =>
      val expr = PresenceConditionParser.parse(
        ctx,
        "(defined cond1) && ((defined cond2) || !(defined cond3) && (cond4 == 5))"
      )
      assert(expr.isBool)
    }
  }

  test("exhaustivelySample enumerates macro combinations of sample1.c") {
    val samples = ProductStrategy.exhaustivelySample(sample1)
    assert(samples.nonEmpty)
    assert(samples.forall(_.forall(f => f.startsWith("-D") || f.startsWith("-U"))))
  }
}
