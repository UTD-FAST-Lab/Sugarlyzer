package sugarlyzer.tester.sugarc

import munit.FunSuite
import cats.syntax.show.*
import os.Path
import sugarlyzer.util.CommandBuilder

class SugarCRunnerTest extends FunSuite {

  // ============================================================
  // Base Command Tests
  // ============================================================

  test(
    "buildDesugarCommand: includes java with correct memory and SugarC args"
  ) {
    val fileToDesugar = os.Path("/tmp/test/file.c")
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = false,
      keepMem = false,
      makeMain = false,
      includedFiles = Seq.empty,
      includedDirectories = Seq.empty,
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show
    assert(cmdStr.contains("java"), s"Command should contain 'java': $cmdStr")
    assert(
      cmdStr.contains("-Xmx32g"),
      s"Command should contain '-Xmx32g': $cmdStr"
    )
    assert(
      cmdStr.contains("superc.SugarC"),
      s"Command should contain 'superc.SugarC': $cmdStr"
    )
    assert(
      cmdStr.contains("-showActions"),
      s"Command should contain '-showActions': $cmdStr"
    )
    assert(
      cmdStr.contains("-useBDD"),
      s"Command should contain '-useBDD': $cmdStr"
    )
  }

  test("buildDesugarCommand: sets working directory to parent of file") {
    val fileToDesugar = os.Path("/project/src/module/file.c")
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = false,
      keepMem = false,
      makeMain = false,
      includedFiles = Seq.empty,
      includedDirectories = Seq.empty,
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show
    assert(
      cmdStr.contains("(in /project/src/module)"),
      s"Command should have working dir: $cmdStr"
    )
  }

  // ============================================================
  // Included Files Tests
  // ============================================================

  test("buildDesugarCommand: adds -include for each included file") {
    val fileToDesugar = os.Path("/tmp/test/file.c")
    val includedFiles = Seq(
      os.Path("/config/header1.h"),
      os.Path("/config/header2.h")
    )
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = false,
      keepMem = false,
      makeMain = false,
      includedFiles = includedFiles,
      includedDirectories = Seq.empty,
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show
    assert(
      cmdStr.contains("-include /config/header1.h"),
      s"Command should include header1.h: $cmdStr"
    )
    assert(
      cmdStr.contains("-include /config/header2.h"),
      s"Command should include header2.h: $cmdStr"
    )
  }

  test(
    "buildDesugarCommand: recommendedSpace file is prepended to included files"
  ) {
    val fileToDesugar = os.Path("/tmp/test/file.c")
    val rsFile        = os.Path("/tmp/recommended_space.txt")
    val includedFiles = Seq(os.Path("/config/header.h"))

    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = Some(rsFile),
      noStdLibs = false,
      keepMem = false,
      makeMain = false,
      includedFiles = includedFiles,
      includedDirectories = Seq.empty,
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show
    // Both files should be included
    assert(
      cmdStr.contains("-include /tmp/recommended_space.txt"),
      s"Command should include recommended space file: $cmdStr"
    )
    assert(
      cmdStr.contains("-include /config/header.h"),
      s"Command should include header.h: $cmdStr"
    )

    // Recommended space should come before other includes
    val rsIndex     = cmdStr.indexOf("-include /tmp/recommended_space.txt")
    val headerIndex = cmdStr.indexOf("-include /config/header.h")
    assert(
      rsIndex < headerIndex,
      s"Recommended space should come before other includes: $cmdStr"
    )
  }

  test("buildDesugarCommand: no included files produces no -include args") {
    val fileToDesugar = os.Path("/tmp/test/file.c")
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = false,
      keepMem = false,
      makeMain = false,
      includedFiles = Seq.empty,
      includedDirectories = Seq.empty,
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show
    assert(
      !cmdStr.contains("-include"),
      s"Command should not contain -include: $cmdStr"
    )
  }

  // ============================================================
  // Included Directories Tests
  // ============================================================

  test("buildDesugarCommand: adds -I for each included directory") {
    val fileToDesugar = os.Path("/tmp/test/file.c")
    val includedDirs = Seq(
      os.Path("/usr/include"),
      os.Path("/project/include"),
      os.Path("/project/src")
    )
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = false,
      keepMem = false,
      makeMain = false,
      includedFiles = Seq.empty,
      includedDirectories = includedDirs,
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show
    assert(
      cmdStr.contains("-I /usr/include"),
      s"Command should include /usr/include: $cmdStr"
    )
    assert(
      cmdStr.contains("-I /project/include"),
      s"Command should include /project/include: $cmdStr"
    )
    assert(
      cmdStr.contains("-I /project/src"),
      s"Command should include /project/src: $cmdStr"
    )
  }

  test("buildDesugarCommand: no included directories produces no -I args") {
    val fileToDesugar = os.Path("/tmp/test/file.c")
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = false,
      keepMem = false,
      makeMain = false,
      includedFiles = Seq.empty,
      includedDirectories = Seq.empty,
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show
    assert(!cmdStr.contains("-I "), s"Command should not contain -I: $cmdStr")
  }

  // ============================================================
  // Command Line Declarations Tests
  // ============================================================

  test("buildDesugarCommand: adds command line declarations") {
    val fileToDesugar = os.Path("/tmp/test/file.c")
    val declarations  = Seq("-D DEBUG", "-D VERSION=1.0", "-U NDEBUG")

    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = false,
      keepMem = false,
      makeMain = false,
      includedFiles = Seq.empty,
      includedDirectories = Seq.empty,
      commandLineDeclarations = declarations
    )

    val cmdStr = cmd.show
    assert(
      cmdStr.contains("-D DEBUG"),
      s"Command should contain -D DEBUG: $cmdStr"
    )
    assert(
      cmdStr.contains("-D VERSION=1.0"),
      s"Command should contain -D VERSION=1.0: $cmdStr"
    )
    assert(
      cmdStr.contains("-U NDEBUG"),
      s"Command should contain -U NDEBUG: $cmdStr"
    )
  }

  // ============================================================
  // Boolean Flags Tests
  // ============================================================

  test("buildDesugarCommand: noStdLibs=true adds -nostdinc") {
    val fileToDesugar = os.Path("/tmp/test/file.c")
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = true,
      keepMem = false,
      makeMain = false,
      includedFiles = Seq.empty,
      includedDirectories = Seq.empty,
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show
    assert(
      cmdStr.contains("-nostdinc"),
      s"Command should contain -nostdinc: $cmdStr"
    )
  }

  test("buildDesugarCommand: noStdLibs=false does not add -nostdinc") {
    val fileToDesugar = os.Path("/tmp/test/file.c")
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = false,
      keepMem = false,
      makeMain = false,
      includedFiles = Seq.empty,
      includedDirectories = Seq.empty,
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show
    assert(
      !cmdStr.contains("-nostdinc"),
      s"Command should not contain -nostdinc: $cmdStr"
    )
  }

  test("buildDesugarCommand: keepMem=true adds -keep-mem") {
    val fileToDesugar = os.Path("/tmp/test/file.c")
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = false,
      keepMem = true,
      makeMain = false,
      includedFiles = Seq.empty,
      includedDirectories = Seq.empty,
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show
    assert(
      cmdStr.contains("-keep-mem"),
      s"Command should contain -keep-mem: $cmdStr"
    )
  }

  test("buildDesugarCommand: keepMem=false does not add -keep-mem") {
    val fileToDesugar = os.Path("/tmp/test/file.c")
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = false,
      keepMem = false,
      makeMain = false,
      includedFiles = Seq.empty,
      includedDirectories = Seq.empty,
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show
    assert(
      !cmdStr.contains("-keep-mem"),
      s"Command should not contain -keep-mem: $cmdStr"
    )
  }

  test("buildDesugarCommand: makeMain=true adds -make-main") {
    val fileToDesugar = os.Path("/tmp/test/file.c")
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = false,
      keepMem = false,
      makeMain = true,
      includedFiles = Seq.empty,
      includedDirectories = Seq.empty,
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show
    assert(
      cmdStr.contains("-make-main"),
      s"Command should contain -make-main: $cmdStr"
    )
  }

  test("buildDesugarCommand: makeMain=false does not add -make-main") {
    val fileToDesugar = os.Path("/tmp/test/file.c")
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = false,
      keepMem = false,
      makeMain = false,
      includedFiles = Seq.empty,
      includedDirectories = Seq.empty,
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show
    assert(
      !cmdStr.contains("-make-main"),
      s"Command should not contain -make-main: $cmdStr"
    )
  }

  test("buildDesugarCommand: all boolean flags enabled") {
    val fileToDesugar = os.Path("/tmp/test/file.c")
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = true,
      keepMem = true,
      makeMain = true,
      includedFiles = Seq.empty,
      includedDirectories = Seq.empty,
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show
    assert(
      cmdStr.contains("-nostdinc"),
      s"Command should contain -nostdinc: $cmdStr"
    )
    assert(
      cmdStr.contains("-keep-mem"),
      s"Command should contain -keep-mem: $cmdStr"
    )
    assert(
      cmdStr.contains("-make-main"),
      s"Command should contain -make-main: $cmdStr"
    )
  }

  // ============================================================
  // Output Path Tests
  // ============================================================

  test("getOutputPath: creates .desugared.c suffix") {
    val inputFile  = os.Path("/tmp/test/crypto/aes.c")
    val outputPath = SugarCRunner.getOutputPath(inputFile)

    assertEquals(outputPath, os.Path("/tmp/test/crypto/aes.desugared.c"))
  }

  test("getOutputPath: preserves directory structure") {
    val inputFile  = os.Path("/project/src/module/file.c")
    val outputPath = SugarCRunner.getOutputPath(inputFile)

    assertEquals(outputPath, os.Path("/project/src/module/file.desugared.c"))
  }

  test("getOutputPath: handles deeply nested paths") {
    val inputFile  = os.Path("/a/b/c/d/e/source.c")
    val outputPath = SugarCRunner.getOutputPath(inputFile)

    assertEquals(outputPath, os.Path("/a/b/c/d/e/source.desugared.c"))
  }

  test("getOutputPath: handles file with multiple dots in name") {
    val inputFile  = os.Path("/tmp/file.test.c")
    val outputPath = SugarCRunner.getOutputPath(inputFile)

    // baseName should be "file.test" (without .c extension)
    assertEquals(outputPath, os.Path("/tmp/file.test.desugared.c"))
  }

  // ============================================================
  // Full Command Integration Tests
  // ============================================================

  test("buildDesugarCommand: full command with all options") {
    val fileToDesugar = os.Path("/project/src/crypto/aes.c")
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = Some(os.Path("/tmp/rs.txt")),
      noStdLibs = true,
      keepMem = true,
      makeMain = false,
      includedFiles = Seq(os.Path("/config/header.h")),
      includedDirectories =
        Seq(os.Path("/usr/include"), os.Path("/project/include")),
      commandLineDeclarations = Seq("-D DEBUG", "-D _GNU_SOURCE")
    )

    val cmdStr = cmd.show

    // Base command
    assert(
      cmdStr.contains("java -Xmx32g superc.SugarC -showActions -useBDD"),
      s"Should have base command: $cmdStr"
    )

    // Included files (recommended space first, then regular includes)
    assert(
      cmdStr.contains("-include /tmp/rs.txt"),
      s"Should include rs file: $cmdStr"
    )
    assert(
      cmdStr.contains("-include /config/header.h"),
      s"Should include header: $cmdStr"
    )

    // Included directories
    assert(
      cmdStr.contains("-I /usr/include"),
      s"Should include /usr/include: $cmdStr"
    )
    assert(
      cmdStr.contains("-I /project/include"),
      s"Should include /project/include: $cmdStr"
    )

    // Declarations
    assert(cmdStr.contains("-D DEBUG"), s"Should have DEBUG macro: $cmdStr")
    assert(
      cmdStr.contains("-D _GNU_SOURCE"),
      s"Should have _GNU_SOURCE macro: $cmdStr"
    )

    // Boolean flags
    assert(cmdStr.contains("-nostdinc"), s"Should have -nostdinc: $cmdStr")
    assert(cmdStr.contains("-keep-mem"), s"Should have -keep-mem: $cmdStr")
    assert(
      !cmdStr.contains("-make-main"),
      s"Should not have -make-main: $cmdStr"
    )

    // Working directory
    assert(
      cmdStr.contains("(in /project/src/crypto)"),
      s"Should have working dir: $cmdStr"
    )
  }

  test("buildDesugarCommand: axtls-style aes.c command") {
    val fileToDesugar = os.Path("/targets/axtls/crypto/aes.c")
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = true,
      keepMem = false,
      makeMain = false,
      includedFiles = Seq(os.Path("/SugarlyzerConfig/axtlsInc.h")),
      includedDirectories = Seq(
        os.Path("/SugarlyzerConfig/"),
        os.Path("/targets/axtls/config"),
        os.Path("/targets/axtls/ssl"),
        os.Path("/targets/axtls/crypto")
      ),
      commandLineDeclarations = Seq.empty
    )

    val cmdStr = cmd.show

    // Should include axtls header
    assert(
      cmdStr.contains("-include /SugarlyzerConfig/axtlsInc.h"),
      s"Should include axtlsInc.h: $cmdStr"
    )

    // Should have all directories
    assert(
      cmdStr.contains("-I /SugarlyzerConfig"),
      s"Should include SugarlyzerConfig: $cmdStr"
    )
    assert(
      cmdStr.contains("-I /targets/axtls/config"),
      s"Should include config dir: $cmdStr"
    )
    assert(
      cmdStr.contains("-I /targets/axtls/ssl"),
      s"Should include ssl dir: $cmdStr"
    )
    assert(
      cmdStr.contains("-I /targets/axtls/crypto"),
      s"Should include crypto dir: $cmdStr"
    )

    // Should have nostdinc
    assert(cmdStr.contains("-nostdinc"), s"Should have -nostdinc: $cmdStr")

    // Working directory should be crypto folder
    assert(
      cmdStr.contains("(in /targets/axtls/crypto)"),
      s"Should have working dir: $cmdStr"
    )
  }

  test("buildDesugarCommand: busybox-style less.c command with macros") {
    val fileToDesugar = os.Path("/targets/busybox/miscutils/less.c")
    val cmd = SugarCRunner.buildDesugarCommand(
      fileToDesugar = fileToDesugar,
      rsFileOpt = None,
      noStdLibs = true,
      keepMem = false,
      makeMain = false,
      includedFiles = Seq(os.Path("/targets/busybox/include/autoconf.h")),
      includedDirectories = Seq(
        os.Path("/targets/busybox/include"),
        os.Path("/targets/busybox/libbb")
      ),
      commandLineDeclarations = Seq(
        "-D _GNU_SOURCE",
        "-D NDEBUG",
        "-D _LARGEFILE_SOURCE"
      )
    )

    val cmdStr = cmd.show

    // Should include autoconf.h
    assert(
      cmdStr.contains("-include /targets/busybox/include/autoconf.h"),
      s"Should include autoconf.h: $cmdStr"
    )

    // Should have directories
    assert(
      cmdStr.contains("-I /targets/busybox/include"),
      s"Should include include dir: $cmdStr"
    )
    assert(
      cmdStr.contains("-I /targets/busybox/libbb"),
      s"Should include libbb dir: $cmdStr"
    )

    // Should have macro definitions
    assert(
      cmdStr.contains("-D _GNU_SOURCE"),
      s"Should have _GNU_SOURCE: $cmdStr"
    )
    assert(cmdStr.contains("-D NDEBUG"), s"Should have NDEBUG: $cmdStr")
    assert(
      cmdStr.contains("-D _LARGEFILE_SOURCE"),
      s"Should have _LARGEFILE_SOURCE: $cmdStr"
    )

    // Working directory
    assert(
      cmdStr.contains("(in /targets/busybox/miscutils)"),
      s"Should have working dir: $cmdStr"
    )
  }
}
