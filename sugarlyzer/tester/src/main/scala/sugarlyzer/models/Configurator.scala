package sugarlyzer.models

import cats.effect.{IO}
import os._
import scala.util.Using

object Configurator {
  def stageAndBuild(spec: ProgramSpecification): IO[Unit] = IO.blocking {
    val targetRootDir = os.Path("/targets")
    if (!os.exists(targetRootDir)) os.makeDir.all(targetRootDir)

    val tarName      = s"${spec.name}.tar.gz"
    val resourcePath = s"programs/${spec.name}/$tarName"
    val tarDest      = targetRootDir / tarName

    Using(getClass.getClassLoader.getResourceAsStream(resourcePath)) { stream =>
      if (stream == null)
        throw new RuntimeException(s"Missing resource: $resourcePath")

      os.write.over(tarDest, stream)
    }.get

    val proc =
      os.proc("tar", "-xf", tarDest, "-C", targetRootDir)
        .call(check = false)
    if (proc.exitCode != 0)
      throw new RuntimeException("Tar extraction failed")

    val buildProc = os.proc("bash", "-c", spec.buildCommand)
      .call(cwd = os.Path(spec.targetDir))
    if (buildProc.exitCode != 0)
      throw new RuntimeException(
        s"Failed to run build command: ${spec.buildCommand}"
      )

    /* val configHeaderResource = s"programs/${spec.name}/${spec.name}Config.h"
     * Using(getClass.getClassLoader.getResourceAsStream(configHeaderResource))
     * { stream => if (stream == null) throw new RuntimeException(s"Missing
     * resource: $configHeaderResource")
     *
     * val configHeaderDest =
     * targetRootDir / os.RelPath(spec.configHeaderLocation)
     *
     * os.write.over(configHeaderDest, stream) }.get */
  }
}
