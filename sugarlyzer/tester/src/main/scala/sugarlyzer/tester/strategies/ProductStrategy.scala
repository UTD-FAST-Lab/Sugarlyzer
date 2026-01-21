package sugarlyzer.tester.strategies

import cats.effect.IO
import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.models.*
import sugarlyzer.common.Config.AppConfig
import cats.effect.syntax.all._
import os._
import sugarlyzer.tester.tools.Alarm
import scala.util.Using

object ProductStrategy extends AnalysisStrategy {
  def execute(config: AppConfig, tool: AnalysisTool): IO[Unit] = {
    for {
      _    <- IO.println("Loading program specification...")
      spec <- ProgramFactory.load(config.program)
      _    <- Configurator.stageAndBuild(spec)
      resulting_alarms <- (0 until config.sampleSize).toList.parTraverseN(
        Runtime.getRuntime().availableProcessors()
      ) {
        i =>
          prepareAndRunSample(i, spec, tool)
      }
      _ <- IO.println(s"Got ${resulting_alarms.flatten.size} alarms")
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
      _       <- IO.println(s"Finished sample #$i")
    } yield (alarms)
  }

  private def prepareTarget(
      i: Int,
      spec: ProgramSpecification
  ): IO[ProgramSpecification] = IO.blocking {
    val masterSource = os.Path(spec.targetDir)     // i.e., /targets/axtls-code/
    val iterDir      = os.Path("/targets") / s"$i" // i.e., /targets/0/

    if (os.exists(iterDir)) os.remove.all(iterDir)
    os.makeDir.all(iterDir)

    val finalDest = iterDir / masterSource.last // i.e., /targets/0/axtls-code/

    // Copy the source code to the new iteration location to parallelize
    os.copy(masterSource, finalDest)

    // Here we need to replace the existing config file with one of our samples
    val destConfigFile = iterDir / os.RelPath(
      spec.configFileLocation
    ) // i.e., /targets/0/axtls-code/config/.config

    if (!os.exists(destConfigFile))
      throw new RuntimeException(
        s"Config files not found: $destConfigFile. Content of iterDir: ${os.list(iterDir)}"
      )

    val configResource = s"programs/${spec.name}/configs/$i.config"

    Using(getClass.getClassLoader.getResourceAsStream((configResource))) {
      stream =>
        if (stream == null)
          throw new RuntimeException(s"Missing config: $configResource")
        os.write.over(destConfigFile, stream)
    }.get

    spec.copy(
      targetDir = (iterDir / spec.rootDir).toString,
      buildCommand = "yes | make oldconfig"
    )
  }
}
