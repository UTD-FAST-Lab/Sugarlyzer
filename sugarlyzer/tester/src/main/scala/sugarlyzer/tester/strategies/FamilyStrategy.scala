package sugarlyzer.tester.strategies

import cats.effect.IO
import sugarlyzer.tester.tools.AnalysisTool
import sugarlyzer.tester.tools.FamilyAlarm
import sugarlyzer.common.Config.AppConfig
import sugarlyzer.models.*
import sugarlyzer.models.Configurator

object FamilyStrategy extends AnalysisStrategy {
  type Alarm = FamilyAlarm

  def analyze(
      appConfig: AppConfig,
      spec: ProgramSpecification,
      tool: AnalysisTool
  ): IO[List[FamilyAlarm]] = {
    ???
  }

  def build(appConfig: AppConfig, spec: ProgramSpecification): IO[Unit] = for {
    _ <- IO.println("Preparing to build...")
    _ <- {
      if (!spec.configFileLocation.isEmpty) {
        Configurator.stageAndBuild(appConfig, spec)
      } else {
        Configurator.stage(appConfig, spec)
      }
    }
  } yield ()

  def deduplicate(alarms: List[FamilyAlarm]): List[FamilyAlarm] = {
    ???
  }

  def exportAlarms(alarms: List[FamilyAlarm]): IO[Unit] = IO.blocking {
    ???
  }

}
