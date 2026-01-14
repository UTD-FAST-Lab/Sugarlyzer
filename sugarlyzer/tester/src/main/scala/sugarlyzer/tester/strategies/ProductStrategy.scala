package sugarlyzer.tester.strategies

import cats.effect.IO
import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.models.*
import sugarlyzer.common.Config.AppConfig
import cats.syntax.all.*
import os._

object ProductStrategy extends AnalysisStrategy {
  def execute(config: AppConfig, tool: AnalysisTool): IO[Unit] = {
    for {
      _            <- IO.println("Loading program specification...")
      spec         <- ProgramFactory.load(config.program)
      masterSource <- Configurator.stageAndConfigure(spec)
      _ <- (0 until config.sampleSize).toList.parTraverse_ { i =>
        prepareAndRunSample(i, masterSource, spec, tool)
      }
    } yield ()
  }

  private def prepareAndRunSample(
      i: Int,
      masterSource: os.Path,
      spec: ProgramSpecification,
      tool: AnalysisTool
  ): IO[Unit] = {
    for {
      newSpec <- prepareTarget(i, masterSource, spec)
      _       <- tool.run(newSpec)
    } yield ()
  }

  private def prepareTarget(
      i: Int,
      masterSource: os.Path,
      spec: ProgramSpecification
  ): IO[ProgramSpecification] = IO.blocking {
    val iterDir = os.Path("/targets") / s"$i"

    if (os.exists(iterDir)) os.remove.all(iterDir)
    os.makeDir.all(iterDir)

    val finalDest = iterDir / masterSource.last
    os.copy(masterSource, finalDest)

    val destConfigDir = iterDir / os.RelPath(spec.configFileLocation)

    if (!os.exists(destConfigDir))
      throw new RuntimeException(
        s"Config dir still not found: $destConfigDir. Content of iterDir: ${os.list(iterDir)}"
      )

    val destConfigFile = destConfigDir / ".config"
    val configResource = s"programs/${spec.name}/configs/$i.config"

    val stream = getClass.getClassLoader.getResourceAsStream(configResource)
    if (stream == null)
      throw new RuntimeException(s"Missing config: $configResource")

    os.write.over(destConfigFile, stream)

    spec.copy(
      targetDir = (iterDir / spec.rootDir).toString,
      buildCommand = "yes | make oldconfig"
    )
  }
}
