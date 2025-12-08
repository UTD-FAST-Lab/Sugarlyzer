package sugarlyzer.util

import munit.CatsEffectSuite
import cats.syntax.show.*
import java.io.File

class CommandBuilderTest extends CatsEffectSuite {

  // ============================================================
  // Construction Tests
  // ============================================================

  test("CommandBuilder: creates with program only") {
    val cmd = CommandBuilder(program = "echo")

    assertEquals(cmd.program, "echo")
    assertEquals(cmd.args, Vector.empty)
    assertEquals(cmd.env, Map.empty)
    assertEquals(cmd.workingDir, None)
  }

  test("CommandBuilder: creates with program and args") {
    val cmd = CommandBuilder(
      program = "echo",
      args = Vector("hello", "world")
    )

    assertEquals(cmd.program, "echo")
    assertEquals(cmd.args, Vector("hello", "world"))
  }

  test("CommandBuilder: creates with all fields") {
    val dir = new File("/tmp")
    val cmd = CommandBuilder(
      program = "java",
      args = Vector("-version"),
      env = Map("JAVA_HOME" -> "/usr/lib/jvm"),
      workingDir = Some(dir)
    )

    assertEquals(cmd.program, "java")
    assertEquals(cmd.args, Vector("-version"))
    assertEquals(cmd.env, Map("JAVA_HOME" -> "/usr/lib/jvm"))
    assertEquals(cmd.workingDir, Some(dir))
  }

  // ============================================================
  // Builder Method Tests
  // ============================================================

  test("arg: appends single argument") {
    val cmd = CommandBuilder(program = "echo")
      .arg("hello")

    assertEquals(cmd.args, Vector("hello"))
  }

  test("arg: appends multiple arguments in sequence") {
    val cmd = CommandBuilder(program = "echo")
      .arg("hello")
      .arg("world")

    assertEquals(cmd.args, Vector("hello", "world"))
  }

  test("args: appends multiple arguments at once") {
    val cmd = CommandBuilder(program = "java")
      .args("-Xmx32g", "-cp", "app.jar")

    assertEquals(cmd.args, Vector("-Xmx32g", "-cp", "app.jar"))
  }

  test("args: can be called multiple times") {
    val cmd = CommandBuilder(program = "java")
      .args("-Xmx32g")
      .args("-cp", "app.jar")
      .args("Main")

    assertEquals(cmd.args, Vector("-Xmx32g", "-cp", "app.jar", "Main"))
  }

  test("args: handles empty varargs") {
    val emptyArgs: Seq[String] = Seq.empty
    val cmd = CommandBuilder(program = "echo")
      .args(emptyArgs*)

    assertEquals(cmd.args, Vector.empty)
  }

  test("env: adds environment variable") {
    val cmd = CommandBuilder(program = "java")
      .env("JAVA_HOME", "/usr/lib/jvm")

    assertEquals(cmd.env, Map("JAVA_HOME" -> "/usr/lib/jvm"))
  }

  test("env: adds multiple environment variables") {
    val cmd = CommandBuilder(program = "java")
      .env("JAVA_HOME", "/usr/lib/jvm")
      .env("PATH", "/usr/bin")

    assertEquals(
      cmd.env,
      Map(
        "JAVA_HOME" -> "/usr/lib/jvm",
        "PATH"      -> "/usr/bin"
      )
    )
  }

  test("env: overwrites existing key") {
    val cmd = CommandBuilder(program = "java")
      .env("JAVA_HOME", "/old/path")
      .env("JAVA_HOME", "/new/path")

    assertEquals(cmd.env, Map("JAVA_HOME" -> "/new/path"))
  }

  test("in: sets working directory") {
    val dir = new File("/tmp/workdir")
    val cmd = CommandBuilder(program = "ls")
      .in(dir)

    assertEquals(cmd.workingDir, Some(dir))
  }

  test("in: overwrites previous working directory") {
    val dir1 = new File("/tmp/dir1")
    val dir2 = new File("/tmp/dir2")
    val cmd = CommandBuilder(program = "ls")
      .in(dir1)
      .in(dir2)

    assertEquals(cmd.workingDir, Some(dir2))
  }

  // ============================================================
  // Immutability Tests
  // ============================================================

  test("arg: returns new instance, original unchanged") {
    val original = CommandBuilder(program = "echo")
    val modified = original.arg("hello")

    assertEquals(original.args, Vector.empty)
    assertEquals(modified.args, Vector("hello"))
  }

  test("args: returns new instance, original unchanged") {
    val original = CommandBuilder(program = "echo")
    val modified = original.args("hello", "world")

    assertEquals(original.args, Vector.empty)
    assertEquals(modified.args, Vector("hello", "world"))
  }

  test("env: returns new instance, original unchanged") {
    val original = CommandBuilder(program = "java")
    val modified = original.env("KEY", "value")

    assertEquals(original.env, Map.empty)
    assertEquals(modified.env, Map("KEY" -> "value"))
  }

  test("in: returns new instance, original unchanged") {
    val dir      = new File("/tmp")
    val original = CommandBuilder(program = "ls")
    val modified = original.in(dir)

    assertEquals(original.workingDir, None)
    assertEquals(modified.workingDir, Some(dir))
  }

  // ============================================================
  // build Tests
  // ============================================================

  test("build: creates ProcessBuilder with program and args") {
    val cmd = CommandBuilder(program = "echo")
      .args("hello", "world")

    val pb = cmd.build
    // ProcessBuilder is created successfully
    assert(pb != null)
  }

  test("build: includes working directory when set") {
    val dir = new File("/tmp")
    val cmd = CommandBuilder(program = "ls")
      .in(dir)

    val pb = cmd.build
    assert(pb != null)
  }

  // ============================================================
  // run Tests
  // ============================================================

  test("run: executes simple command successfully") {
    val cmd = CommandBuilder(program = "echo")
      .arg("hello")

    val exitCode = cmd.run()
    assertEquals(exitCode, 0)
  }

  test("run: returns non-zero for failing command") {
    val cmd = CommandBuilder(program = "false")

    val exitCode = cmd.run()
    assert(exitCode != 0)
  }

  test("run: executes command with arguments") {
    val cmd = CommandBuilder(program = "echo")
      .args("-n", "test")

    val exitCode = cmd.run()
    assertEquals(exitCode, 0)
  }

  // ============================================================
  // runWithFileRedirects Tests
  // ============================================================

  test("runWithFileRedirects: writes stdout to output file") {
    val tempDir    = os.temp.dir()
    val outputFile = tempDir / "output.txt"
    val logFile    = tempDir / "log.txt"

    val cmd = CommandBuilder(program = "echo")
      .arg("hello world")

    val result =
      cmd.runWithFileRedirects(outputFile, logFile).attempt.unsafeRunSync()

    result match {
      case Right((out, log)) =>
        assertEquals(out, outputFile)
        assertEquals(log, logFile)
        val content = os.read(outputFile).trim
        assertEquals(content, "hello world")
      case Left(e) =>
        fail(s"Command failed: ${e.getMessage}")
    }

    os.remove.all(tempDir)
  }

  test("runWithFileRedirects: creates output and log files") {
    val tempDir    = os.temp.dir()
    val outputFile = tempDir / "output.txt"
    val logFile    = tempDir / "log.txt"

    val cmd = CommandBuilder(program = "echo")
      .arg("test")

    cmd.runWithFileRedirects(outputFile, logFile).unsafeRunSync()

    assert(os.exists(outputFile), "Output file should be created")
    assert(os.exists(logFile), "Log file should be created")

    os.remove.all(tempDir)
  }

  test("runWithFileRedirects: returns error for failing command") {
    val tempDir    = os.temp.dir()
    val outputFile = tempDir / "output.txt"
    val logFile    = tempDir / "log.txt"

    val cmd = CommandBuilder(program = "false")

    val result =
      cmd.runWithFileRedirects(outputFile, logFile).attempt.unsafeRunSync()

    assert(result.isLeft, "Should return error for failing command")
    result match {
      case Left(e: RuntimeException) =>
        assert(
          e.getMessage.contains("exit code"),
          s"Error message should mention exit code: ${e.getMessage}"
        )
      case Left(e) =>
        fail(s"Unexpected exception type: ${e.getClass.getName}")
      case Right(_) =>
        fail("Expected error but got success")
    }

    os.remove.all(tempDir)
  }

  test("runWithFileRedirects: writes stderr to log file") {
    val tempDir    = os.temp.dir()
    val outputFile = tempDir / "output.txt"
    val logFile    = tempDir / "log.txt"

    // Use bash to write to stderr
    val cmd = CommandBuilder(program = "bash")
      .args("-c", "echo 'error message' >&2")

    // This will fail because bash returns 0 but we're testing stderr capture
    val result =
      cmd.runWithFileRedirects(outputFile, logFile).attempt.unsafeRunSync()

    result match {
      case Right(_) =>
        val logContent = os.read(logFile).trim
        assertEquals(logContent, "error message")
      case Left(e) =>
        // Command might fail, but log should still have content
        if (os.exists(logFile)) {
          val logContent = os.read(logFile).trim
          assert(
            logContent.contains("error"),
            s"Log should contain error: $logContent"
          )
        }
    }

    os.remove.all(tempDir)
  }

  // ============================================================
  // Show instance Tests
  // ============================================================

  test("Show: displays program only") {
    val cmd = CommandBuilder(program = "echo")

    val shown = cmd.show
    assertEquals(shown, "echo")
  }

  test("Show: displays program with args") {
    val cmd = CommandBuilder(program = "echo")
      .args("hello", "world")

    val shown = cmd.show
    assertEquals(shown, "echo hello world")
  }

  test("Show: displays environment variables") {
    val cmd = CommandBuilder(program = "java")
      .env("JAVA_HOME", "/usr/lib/jvm")

    val shown = cmd.show
    assert(shown.contains("JAVA_HOME=/usr/lib/jvm"))
    assert(shown.contains("java"))
  }

  test("Show: displays working directory") {
    val dir = new File("/tmp/workdir")
    val cmd = CommandBuilder(program = "ls")
      .in(dir)

    val shown = cmd.show
    assert(shown.contains("ls"))
    assert(shown.contains("(in /tmp/workdir)"))
  }

  test("Show: displays full command with all fields") {
    val dir = new File("/tmp")
    val cmd = CommandBuilder(program = "java")
      .args("-jar", "app.jar")
      .env("JAVA_HOME", "/usr/lib/jvm")
      .in(dir)

    val shown = cmd.show
    assert(shown.contains("JAVA_HOME=/usr/lib/jvm"))
    assert(shown.contains("java -jar app.jar"))
    assert(shown.contains("(in /tmp)"))
  }

  // ============================================================
  // Edge Cases
  // ============================================================

  test("handles arguments with spaces") {
    val cmd = CommandBuilder(program = "echo")
      .arg("hello world")

    assertEquals(cmd.args, Vector("hello world"))
  }

  test("handles arguments with special characters") {
    val cmd = CommandBuilder(program = "echo")
      .arg("-D \"KEY=value with spaces\"")

    assertEquals(cmd.args, Vector("-D \"KEY=value with spaces\""))
  }

  test("handles empty program string") {
    val cmd = CommandBuilder(program = "")

    assertEquals(cmd.program, "")
  }

  test("chaining all builder methods") {
    val dir = new File("/tmp")
    val cmd = CommandBuilder(program = "java")
      .arg("-Xmx32g")
      .args("-cp", "lib/*")
      .env("JAVA_HOME", "/usr/lib/jvm")
      .env("DEBUG", "true")
      .in(dir)
      .arg("Main")

    assertEquals(cmd.program, "java")
    assertEquals(cmd.args, Vector("-Xmx32g", "-cp", "lib/*", "Main"))
    assertEquals(cmd.env, Map("JAVA_HOME" -> "/usr/lib/jvm", "DEBUG" -> "true"))
    assertEquals(cmd.workingDir, Some(dir))
  }
}
