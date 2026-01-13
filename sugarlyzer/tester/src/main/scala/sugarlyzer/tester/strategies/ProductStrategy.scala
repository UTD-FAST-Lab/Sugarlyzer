package sugarlyzer.tester.strategies

import cats.effect.{IO}
import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.models.*
import sugarlyzer.common.Config.AppConfig
import java.nio.file.Paths

object ProductStrategy extends AnalysisStrategy {
  def execute(config: AppConfig, tool: AnalysisTool): IO[Unit] = {
    val configSamplesPath = s"resources/programs/${config.program}/configs"
    val targetDir         = Paths.get("/targets")

    for {
      _           <- IO.println("Loading program from factory")
      programSpec <- ProgramFactory.load(config.program)

      _ <- IO.println(programSpec)
    } yield ()

  }
}
