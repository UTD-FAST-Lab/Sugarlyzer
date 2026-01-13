package sugarlyzer.tester.tools

import sugarlyzer.models.ProgramSpecification

import cats.effect.{IO}

object InferTool extends AnalysisTool {
  def name(): String = { "Infer" }

  def run(spec: ProgramSpecification): IO[String] = {
    for {
      _ <- IO.println(s"Running tool ${name()}")
      _ <- IO.println(s"Program build command: ${spec.buildCommand}")
      _ <- IO.println(s"Program target dir: ${spec.targetDir}")

    } yield ("End")
  }
  def parseOutput(rawOutput: String): List[String] = {
    List("O")
  }
}
