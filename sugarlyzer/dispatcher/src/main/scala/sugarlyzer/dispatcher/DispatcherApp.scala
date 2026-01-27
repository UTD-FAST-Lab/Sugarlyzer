package sugarlyzer.dispatcher

import cats.effect.{IOApp, IO, ExitCode}
import scopt.OParser
import sugarlyzer.common.Config
import com.github.dockerjava.api.DockerClient
import com.github.dockerjava.core.DockerClientBuilder
import com.github.dockerjava.api.model.{
  Bind,
  Volume,
  AccessMode,
  HostConfig,
  Frame
}
import com.github.dockerjava.api.async.ResultCallback

object DispatcherApp extends IOApp {

  override def run(args: List[String]): IO[ExitCode] = {
    OParser.parse(Config.parser, args, Config.AppConfig()) match {
      case Some(config) =>
        for {
          _ <-
            IO.println(s"[HOST] Preparing ${config.tool} on ${config.program}")
          _ <- buildImages(config)

          dockerClient <- IO.blocking(DockerClientBuilder.getInstance().build())
          _            <- runPipeline(dockerClient, config)
          _ <- IO.println("[HOST] Pipeline finished. Launching debug shell...")
          _ <- enterShell(config)

        } yield ExitCode.Success
      case None => IO(ExitCode.Error)
    }
  }

  def buildImages(config: Config.AppConfig): IO[Unit] = {
    val buildProgramCmd = List(
      "docker",
      "build",
      "-t",
      "sugarlyzer-program",
      "-f",
      "Dockerfile.program",
      "."
    )
    val toolTag = s"sugarlyzer/${config.tool.toString().toLowerCase()}"
    val buildToolCmd = List(
      "docker",
      "build",
      "-t",
      toolTag,
      "-f",
      s"Dockerfile.${config.tool}",
      "."
    )

    for {
      _ <- IO.println("[HOST] Building program image...")
      _ <- IO.blocking(os.proc(buildProgramCmd).call(
        cwd = os.pwd,
        stdout = os.Inherit,
        stderr = os.Inherit
      ))
      _ <- IO.println("[HOST] Building tool image...")
      _ <- IO.blocking(os.proc(buildToolCmd).call(
        cwd = os.pwd,
        stdout = os.Inherit,
        stderr = os.Inherit
      ))
    } yield ()
  }

  val SharedPath = "/workspace"

  def runPipeline(
      dockerClient: DockerClient,
      config: Config.AppConfig
  ): IO[Unit] = {
    val volumeName = s"sugarlyzer-${config.program}-${config.tool}"
    val volumeBind =
      new Bind(volumeName, new Volume("/workspace"), AccessMode.rw)

    for {
      _ <- IO.println("[HOST] Ensuring shared volume exists...")
      _ <-
        IO.blocking(dockerClient.createVolumeCmd().withName(volumeName).exec())

      // PHASE 1: BUILD
      _ <- IO.println(s"[HOST] Starting Phase 1: Build")
      builderId <- IO.blocking {
        val container = dockerClient.createContainerCmd("sugarlyzer-program")
          .withHostConfig(new HostConfig().withBinds(volumeBind))
          .withTty(false)
          .withCmd(
            "java",
            "-jar",
            "tester.jar",
            "--phase",
            "build",
            "--program",
            config.program,
            "--tool",
            config.tool,
            "--sample_size",
            config.sampleSize.toString
          )
          .exec()
        dockerClient.startContainerCmd(container.getId()).exec()
        container.getId()
      }

      // STREAM LOGS (BUILDER)
      _ <- streamLogs(dockerClient, builderId)

      buildResult <- IO.blocking {
        dockerClient.waitContainerCmd(builderId).start().awaitStatusCode()
      }
      _ <- if (buildResult != 0) IO.raiseError(
        new RuntimeException(s"Build failed with code $buildResult")
      )
      else IO.unit
      _ <- IO.println(s"[HOST] Phase 1 completed")

      // PHASE 2: RUN
      _ <- IO.println(s"[HOST] Starting Phase 2: Run")
      analyzerId <- IO.blocking {
        val container = dockerClient.createContainerCmd(
          s"sugarlyzer/${config.tool.toString().toLowerCase()}"
        )
          .withHostConfig(new HostConfig().withBinds(volumeBind))
          .withTty(false)
          .withCmd(
            "java",
            "-jar",
            "tester.jar",
            "--phase",
            "analyze",
            "--program",
            config.program,
            "--tool",
            config.tool,
            "--sample_size",
            config.sampleSize.toString
          )
          .exec()
        dockerClient.startContainerCmd(container.getId()).exec()
        container.getId()
      }

      _ <- streamLogs(dockerClient, analyzerId)
      _ <- IO.println(s"[HOST] Phase 2 completed")
    } yield ()
  }

  // Helper to stream logs to local console
  private def streamLogs(
      client: DockerClient,
      containerId: String
  ): IO[Unit] = IO.blocking {
    client.logContainerCmd(containerId)
      .withStdOut(true)
      .withStdErr(true)
      .withFollowStream(true)
      .exec(new ResultCallback.Adapter[Frame] {
        override def onNext(item: Frame): Unit = {
          print(new String(
            item.getPayload,
            "UTF-8"
          ))
        }
      }).awaitCompletion(): Unit
  }

  private def enterShell(config: Config.AppConfig): IO[Unit] = IO.blocking {
    val volumeName = s"sugarlyzer-${config.program}-${config.tool}"
    val image      = s"sugarlyzer/${config.tool.toString().toLowerCase()}"

    println(s"\n[HOST] >>> ENTERING DEBUG SHELL ($image) <<<")
    println(s"[HOST] Mounted Volume: $volumeName")
    println(s"[HOST] Type 'exit' to return to host.\n")

    val proc = os.proc(
      "docker",
      "run",
      "-it",
      "--rm",
      "-v",
      s"$volumeName:/workspace",
      image,
      "/bin/bash"
    ).call(
      stdin = os.Inherit,
      stdout = os.Inherit,
      stderr = os.Inherit
    )

    if (proc.exitCode != 0) {
      throw new RuntimeException(s"Shell failed with code ${proc.exitCode}")
    }

    ()
  }
}
