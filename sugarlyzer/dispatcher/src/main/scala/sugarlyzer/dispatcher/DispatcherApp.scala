package sugarlyzer.dispatcher

import cats.effect.{IOApp, IO, ExitCode}
import scopt.OParser
import sugarlyzer.common.Config
import com.github.dockerjava.api.DockerClient
import com.github.dockerjava.core.DockerClientBuilder
import com.github.dockerjava.api.model.HostConfig
import com.github.dockerjava.api.async.ResultCallback
import com.github.dockerjava.api.model.Frame

import os._

object DispatcherApp extends IOApp {

  private def getImageName(tool: String): String = {
    tool match {
      case ""   => return "sugarlyzer/base"
      case tool => return f"sugarlyzer/${tool.toString().toLowerCase()}"
    }
  }

  private def buildImage(tool: String): IO[Unit] = {
    val baseCmd = List(
      "docker",
      "build",
      "-t",
      "sugarlyzer/base",
      "-f",
      "Dockerfile.base",
      "."
    )

    val toolCmd = List(
      "docker",
      "build",
      "-t",
      getImageName(tool),
      "-f",
      s"Dockerfile.$tool",
      "."
    )

    println(s"pwd: ${os.pwd}")

    IO.blocking {
      println("[HOST] Building Base Image...")
      val baseResult = os.proc(baseCmd).call(
        cwd = os.pwd
      )
      if (baseResult.exitCode != 0) {
        println(s"[HOST] Base Image Build Failed: ${baseResult.exitCode}")
        sys.exit(1)
      }

      println(s"[HOST] Building ${getImageName(tool)}...")
      val toolResult = os.proc(toolCmd).call(
        cwd = os.pwd
      )
      if (toolResult.exitCode != 0) {
        println(
          s"[HOST] ${getImageName(tool)} Build Failed: ${toolResult.exitCode}"
        )
        sys.exit(1)
      }
    }
  }

  private def startTester(
      dockerClient: DockerClient,
      config: Config.AppConfig
  ): IO[Unit] = {
    for {
      container <- IO.blocking {

        val hostConfig = new HostConfig()
          .withAutoRemove(true)

        val createdContainer =
          dockerClient.createContainerCmd(getImageName(config.tool))
            .withCmd("/bin/bash")
            .withTty(true)
            .withHostConfig(hostConfig)
            .exec()

        dockerClient.startContainerCmd(createdContainer.getId).exec()

        createdContainer
      }
      _ <- IO.blocking {
        val testerCmd = List(
          "java",
          "-jar",
          "/app/tester.jar",
          "-t",
          config.tool,
          "-p",
          config.program,
          "-s",
          config.strategy.toString,
          "--sample_size",
          config.sampleSize.toString
        )

        val execCreateCmdResponse = dockerClient.execCreateCmd(container.getId)
          .withAttachStderr(true)
          .withAttachStdout(true)
          .withCmd("bash", "-c", testerCmd.mkString(" "))
          .exec()

        dockerClient.execStartCmd(execCreateCmdResponse.getId)
          .exec(new ResultCallback.Adapter[Frame] {
            override def onNext(item: Frame): Unit = {
              print(new String(item.getPayload, "UTF-8"))
            }
          }).awaitCompletion()
      }

      _ <- IO.println(s"Container is ${container}")

    } yield ()
  }

  override def run(args: List[String]): IO[ExitCode] = {
    OParser.parse(Config.parser, args, Config.AppConfig()) match {
      case Some(config) => {
        for {
          _ <- IO.println(
            s"[HOST] Preparing to run ${config.tool} on ${config.program}"
          )

          _ <- buildImage(config.tool)

          dockerClient <-
            IO.blocking { DockerClientBuilder.getInstance().build() }

          _ <- startTester(dockerClient, config)
          _ <- IO.println("[HOST] Preparing/Launching docker environment")

        } yield ExitCode.Success
      }
      case None => IO(ExitCode.Error)
    }
  }
}
