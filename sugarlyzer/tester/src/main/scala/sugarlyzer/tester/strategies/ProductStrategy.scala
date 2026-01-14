package sugarlyzer.tester.strategies

import cats.effect.IO
import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.models.*
import sugarlyzer.common.Config.AppConfig
import cats.syntax.all.*
import os._
import sugarlyzer.tester.tools.Alarm

object ProductStrategy extends AnalysisStrategy {
  def execute(config: AppConfig, tool: AnalysisTool): IO[Unit] = {
    for {
      _    <- IO.println("Loading program specification...")
      spec <- ProgramFactory.load(config.program)
      _    <- Configurator.stageAndBuild(spec)
      resulting_alarms <- (0 until config.sampleSize).toList.parTraverse { i =>
        prepareAndRunSample(i, spec, tool)
      }
      _ <- IO.println(s"Got ${resulting_alarms.flatten.size} alarms")
      _ <- IO.println(s"Alarms: ${resulting_alarms.flatten}")
    } yield ()
  }

  private def prepareAndRunSample(
      i: Int,
      spec: ProgramSpecification,
      tool: AnalysisTool
  ): IO[List[Alarm]] = {
    for {
      newSpec <- prepareTarget(i, spec)
      alarms  <- tool.run(newSpec)
    } yield (alarms)
  }

  private def prepareTarget(
      i: Int,
      spec: ProgramSpecification
  ): IO[ProgramSpecification] = IO.blocking {
    val masterSource = os.Path(spec.targetDir)
    val iterDir      = os.Path("/targets") / s"$i"

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
