package sugarlyzer.models

import cats.effect.{IO}
import os._


object Configurator {
  def stageAndConfigure(spec: ProgramSpecification): IO[Path] = IO.blocking {
    val targetRootDir = os.Path("/targets")
    if (!os.exists(targetRootDir)) os.makeDir.all(targetRootDir)

    val tarName      = s"${spec.name}.tar.gz"
    val resourcePath = s"programs/${spec.name}/$tarName"
    val tarDest      = targetRootDir / tarName

    val stream = getClass.getClassLoader.getResourceAsStream(resourcePath)
    if (stream == null)
      throw new RuntimeException(s"Missing resource: $resourcePath")

    os.write.over(tarDest, stream)

    val proc =
      os.proc("tar", "-xf", tarDest, "-C", targetRootDir).call(check = false)
    if (proc.exitCode != 0) throw new RuntimeException("Tar extraction failed")

    os.proc("bash", "-c", spec.buildCommand).call(
      cwd = os.Path(
        spec.targetDir
      ),
      stdout = os.Inherit,
      stderr = os.Inherit
    )

    os.Path(spec.targetDir)
  }

}
