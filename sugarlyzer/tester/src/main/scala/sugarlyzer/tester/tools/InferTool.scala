package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

import cats.effect.{IO}
import os._

object InferTool extends AnalysisTool {
  def name(): String = { "Infer" }

  def run(spec: ProgramSpecification): IO[String] = {
    for {
      _ <- IO.println(s"Running tool ${name()}")
      _ <- IO.println(s"Program build command: ${spec.buildCommand}")
      _ <- IO.println(s"Program target dir: ${spec.targetDir}")

      _ <- applyConfiguration(spec)

    } yield ("End")
  }

  def applyConfiguration(spec: ProgramSpecification): IO[Unit] = IO.blocking {
    println("Applying configuration")

    val proc = os.proc("bash", "-c", spec.buildCommand).call(
      cwd = os.Path(spec.targetDir)
    )

    println("Program configuration done")

    if (proc.exitCode != 0) {
      throw new RuntimeException(
        s"Failed to run build command: ${spec.buildCommand}"
      )
    }

  }
  def parseOutput(rawOutput: String): List[String] = {
    List("O")
  }
}
