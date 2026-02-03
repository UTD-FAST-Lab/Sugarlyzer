package sugarlyzer.models

import cats.effect.{IO}
import os._
import scala.util.Using
import sugarlyzer.common.Config.AppConfig

object Configurator {
  def stageAndBuild(
      appConfig: AppConfig,
      spec: ProgramSpecification
  ): IO[Unit] = IO.blocking {
    val sharedPath   = os.Path(appConfig.sharedPath)
    val masterSource = sharedPath / os.RelPath(spec.rootDir)

    val tarName      = s"${spec.name}.tar.gz"
    val resourcePath = s"programs/${spec.name}/$tarName"
    val tarDest      = sharedPath / tarName

    Using(getClass.getClassLoader.getResourceAsStream(resourcePath)) { stream =>
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
