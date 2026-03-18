package sugarlyzer.models

import cats.effect.{IO}
import os._
import scala.util.Using
import sugarlyzer.common.Config.AppConfig

object Configurator {
  /** Extracts the program tarball to sharedPath without building or injecting config headers. */
  def stage(appConfig: AppConfig, spec: ProgramSpecification): IO[Unit] = IO.blocking {
    val sharedPath   = os.Path(appConfig.sharedPath)
    val masterSource = sharedPath / os.RelPath(spec.rootDir)

    if (!os.exists(masterSource)) {
      val tarName      = s"${spec.name}.tar.gz"
      val resourcePath = s"programs/${spec.name}/$tarName"
      val tarDest      = sharedPath / tarName

      Using(getClass.getClassLoader.getResourceAsStream(resourcePath)) { stream =>
        if (stream == null)
          throw new RuntimeException(s"Missing resource: $resourcePath")
        os.write.over(tarDest, stream)
      }.get

      val proc = os.proc("tar", "-xf", tarDest, "-C", sharedPath.toString)
        .call(check = false)
      if (proc.exitCode != 0)
        throw new RuntimeException("Tar extraction failed")

      if (!os.exists(masterSource))
        throw new RuntimeException(
          s"Source directory does not exist after extraction: $masterSource"
        )
    }
  }

  def stageAndBuild(
      appConfig: AppConfig,
      spec: ProgramSpecification
  ): IO[Unit] = IO.blocking {
    val sharedPath   = os.Path(appConfig.sharedPath)
    val masterSource = sharedPath / os.RelPath(spec.rootDir)

    val tarName      = s"${spec.name}.tar.gz"
    val resourcePath = s"programs/${spec.name}/$tarName"
    val tarDest      = sharedPath / tarName

    Using(getClass.getClassLoader.getResourceAsStream(resourcePath)) {
      stream =>
        if (stream == null)
          throw new RuntimeException(s"Missing resource: $resourcePath")

        os.write.over(tarDest, stream)
    }.get

    val proc =
      os.proc("tar", "-xf", tarDest, "-C", sharedPath.toString)
        .call(check = false)
    if (proc.exitCode != 0)
      throw new RuntimeException("Tar extraction failed")

    if (!os.exists(masterSource)) {
      throw new RuntimeException(
        s"Source directory does not exist: $masterSource. Check spec.rootDir vs tar structure."
      )
    }

    // Remove any pre-compiled .o files shipped in the tarball so they get
    // recompiled for the current host (e.g. axtls ships zconf.tab.o built
    // against an older ABI which causes a TLS/errno mismatch at link time).
    os.walk(masterSource)
      .filter(p => p.ext == "o")
      .foreach(os.remove)

    // Remove generated Kconfig parser files that may be left over from a
    // previous build with a stale timestamp.  If present, `make` skips
    // regenerating them from the *_shipped originals, and an old flex-generated
    // lex.zconf.c (without #include <errno.h>) causes the same TLS link error.
    val kconfigDir = masterSource / "config" / "scripts" / "config"
    if (os.exists(kconfigDir)) {
      Seq("lex.zconf.c", "zconf.tab.c", "zconf.tab.h", "lkc_defs.h")
        .map(kconfigDir / _)
        .filter(os.exists)
        .foreach(os.remove)
    }

    // Prepend #include <errno.h> to zconf.tab.c_shipped so that errno is
    // declared via the TLS-aware glibc macro before any code in the file uses it.
    val zconfTabShipped = kconfigDir / "zconf.tab.c_shipped"
    if (os.exists(zconfTabShipped)) {
      val content = os.read(zconfTabShipped)
      if (!content.startsWith("#include <errno.h>"))
        os.write.over(zconfTabShipped, "#include <errno.h>\n" + content)
    }

    val buildProc = os.proc("bash", "-c", spec.buildCommand)
      .call(cwd = masterSource)
    if (buildProc.exitCode != 0)
      throw new RuntimeException(
        s"Failed to run build command: ${spec.buildCommand}"
      )

    os.copy(
      from = os.Path("/SugarlyzerConfig") / s"${spec.name}Config.h",
      to = sharedPath / os.RelPath(spec.configHeaderLocation),
      replaceExisting = true
    )
  }
}
