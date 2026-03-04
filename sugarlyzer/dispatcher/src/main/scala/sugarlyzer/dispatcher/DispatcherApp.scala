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
          _            <- buildImages(config)
          dockerClient <- IO.blocking(DockerClientBuilder.getInstance().build())
          _            <- runPipeline(dockerClient, config)
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
      s"Dockerfile.${config.tool.toString().toLowerCase()}",
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
    val workspaceVolumeBind =
      new Bind(volumeName, new Volume("/workspace"), AccessMode.rw)
    val resultsVolumeBind =
      new Bind(config.resultsDir, new Volume("/results"), AccessMode.rw)

    for {
      _ <- IO.println("[HOST] Ensuring shared volume exists...")
      _ <-
        IO.blocking(dockerClient.createVolumeCmd().withName(volumeName).exec())

      // PHASE 1: BUILD
      _ <- IO.println(s"[HOST] Starting Phase 1: Build")
      builderId <- IO.blocking {
        val container = dockerClient.createContainerCmd("sugarlyzer-program")
          .withHostConfig(new HostConfig().withBinds(
            workspaceVolumeBind,
            resultsVolumeBind
          ))
          .withCmd("sleep", "infinity")
          .exec()
        dockerClient.startContainerCmd(container.getId()).exec()
        container.getId()
      }
      _ <- IO.blocking {
        val execCmd = dockerClient.execCreateCmd(builderId)
          .withAttachStdout(true)
          .withAttachStderr(true)
          .withCmd(
            "java",
            "-jar",
            "tester.jar",
            "--phase",
            "build",
            "--program",
            config.program,
            "--tool",
            config.tool.toString(),
            "--sample_size",
            config.sampleSize.toString
          )
          .exec()

        dockerClient.execStartCmd(
          execCmd.getId()
        ).exec(new ResultCallback.Adapter[Frame] {
          override def onNext(item: Frame): Unit =
            print(new String(item.getPayload, "UTF-8"))
        }).awaitCompletion()

        val execResponse = dockerClient.inspectExecCmd(execCmd.getId()).exec()
        if (execResponse.getExitCodeLong() != 0) {
          throw new RuntimeException(
            s"Build failed. Exit code: ${execResponse.getExitCodeLong()}"
          )
        }
      }
      _ <- IO.println(s"[HOST] Phase 1 completed")

      // PHASE 2: RUN
      _ <- IO.println(s"[HOST] Starting Phase 2: Run")
      analyzerId <- IO.blocking {
        val container = dockerClient.createContainerCmd(
          s"sugarlyzer/${config.tool.toString().toLowerCase()}"
        )
          .withHostConfig(new HostConfig().withBinds(
            workspaceVolumeBind,
            resultsVolumeBind
          ))
          .withCmd("sleep", "infinity")
          .exec()
        dockerClient.startContainerCmd(container.getId()).exec()
        container.getId()
      }

      _ <- IO.blocking {
        val execCmd = dockerClient.execCreateCmd(analyzerId)
          .withAttachStdout(true)
          .withAttachStderr(true)
          .withCmd(
            "java",
            "-jar",
            "tester.jar",
            "--phase",
            "analyze",
            "--program",
            config.program,
            "--tool",
            config.tool.toString().toLowerCase(),
            "--sample_size",
            config.sampleSize.toString
          )
          .exec()
        dockerClient.execStartCmd(
          execCmd.getId()
        ).exec(new ResultCallback.Adapter[Frame] {
          override def onNext(item: Frame): Unit =
            print(new String(item.getPayload, "UTF-8"))
        }).awaitCompletion()
      }
      _ <- IO.println(s"[HOST] Phase 2 completed")
    } yield ()
  }
}
