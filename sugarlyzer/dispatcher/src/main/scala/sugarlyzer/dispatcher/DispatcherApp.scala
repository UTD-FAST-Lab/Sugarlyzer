package sugarlyzer.dispatcher

import cats.effect.{IOApp, IO, ExitCode}
import scopt.OParser
import sugarlyzer.common.Config
import com.github.dockerjava.api.DockerClient
import com.github.dockerjava.core.DockerClientBuilder

import com.github.dockerjava.api.model.Bind
import com.github.dockerjava.api.model.Volume
import com.github.dockerjava.api.model.AccessMode
import com.github.dockerjava.api.model.HostConfig
import com.github.dockerjava.api.model.Frame
import com.github.dockerjava.api.async.ResultCallback

object DispatcherApp extends IOApp {
  override def run(args: List[String]): IO[ExitCode] = {
    OParser.parse(Config.parser, args, Config.AppConfig()) match {
      case Some(config) => {
        for {
          _ <- IO.println(
            s"[HOST] Preparing to run ${config.tool} on ${config.program}"
          )

          _ <- buildImages(config)

          dockerClient <-
            IO.blocking { DockerClientBuilder.getInstance().build() }

          _ <- runPipeline(dockerClient, config)

        } yield ExitCode.Success
      }
      case None => IO(ExitCode.Error)
    }
  }

  def buildImages(
      config: Config.AppConfig
  ): IO[Unit] = {
    val buildProgramCmd = List(
      "docker",
      "build",
      "-t",
      "sugarlyzer-program",
      "-f",
      "Dockerfile.program",
      "."
    )

    val buildToolCmd = List(
      "docker",
      "build",
      "-t",
      s"sugarlyzer/${config.tool.toString().toLowerCase()}",
      "-f",
      s"Dockerfile.${config.tool}",
      "."
    )

    for {
      _ <- IO.println("[HOST] Building program image")
      _ <- IO.blocking {
        os.proc(buildProgramCmd).call(cwd = os.pwd)
      }
      _ <- IO.println("[HOST] Building tool image")
      _ <- IO.blocking {
        os.proc(buildToolCmd).call(cwd = os.pwd)
      }
    } yield ()
  }

  val SharedPath = "/workspace"
  def runPipeline(
      dockerClient: DockerClient,
      config: Config.AppConfig
  ): IO[Unit] = {
    val volumeName = s"sugarlyzer-${config.program}-${config.tool}"

    val createVolume = IO.blocking {
      dockerClient.createVolumeCmd().withName(volumeName).exec()
    }

    val volumeBind =
      new Bind(SharedPath, new Volume("/workspace"), AccessMode.rw)

    for {
      _ <- IO.println("[HOST] Creating shared volume")
      _ <- createVolume
      _ <- IO.println(s"[HOST] Volume ${volumeName} created")
      _ <- IO.println(s"[HOST] Starting Phase 1: Build")

      builderId <- IO.blocking {
        val container = dockerClient.createContainerCmd("sugarlyzer-program")
          .withHostConfig(
            new HostConfig().withBinds(volumeBind).withAutoRemove(true)
          )
          .withCmd(
            "java",
            "-jar",
            "/app/tester.jar",
            "--phase",
            "build",
            "--program",
            config.program,
            "--tool",
            config.tool
          )
          .exec()

        dockerClient.startContainerCmd(container.getId()).exec()
        container.getId()
      }

      buildResult <- IO.blocking {
        dockerClient.waitContainerCmd(builderId).start().awaitStatusCode()
      }
      _ <- if (buildResult != 0)
        IO.raiseError(new RuntimeException("Build failed"))
      else IO.unit

      _ <- IO.println(s"[HOST] Phase 1 completed")
      _ <- IO.println(s"[HOST] Starting Phase 2: Run")

      analyzerId <- IO.blocking {
        val container = dockerClient.createContainerCmd(
          s"sugarlyzer/${config.tool.toString().toLowerCase()}"
        ).withHostConfig(new HostConfig().withBinds(
          volumeBind
        ).withAutoRemove(true))
          .withCmd(
            "java",
            "-jar",
            "/app/tester.jar",
            "--phase",
            "analyze",
            "--program",
            config.program,
            "--tool",
            config.tool
          )
          .exec()

        dockerClient.startContainerCmd(container.getId()).exec()
        container.getId()
      }

      _ <- IO.blocking {
        dockerClient.logContainerCmd(analyzerId)
          .withStdOut(true).withStdErr(true).withFollowStream(true)
          .exec(new ResultCallback.Adapter[Frame] {
            override def onNext(item: Frame): Unit =
              print(new String(item.getPayload, "UTF-8"))
          }).awaitCompletion()
      }

      _ <- IO.println(s"[HOST] Phase 2 completed")

    } yield ()
  }
}
