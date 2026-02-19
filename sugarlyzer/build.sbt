val scala3Version = "3.8.1"
val scoptVersion  = "4.1.0"
val circeVersion  = "0.14.15"

// Common settings for all modules
lazy val commonSettings = Seq(
  version           := "2.0.0",
  scalaVersion      := scala3Version,
  semanticdbEnabled := true,
  semanticdbVersion := scalafixSemanticdb.revision,
  scalacOptions ++= Seq(
    "-Wunused:all",
    "-Wnonunit-statement",
    "-Wvalue-discard",
    "-deprecation",
    "-rewrite",
    "-no-indent"
  ),

  // Library dependencies
  libraryDependencies += "org.typelevel" %% "cats-core"       % "2.13.0",
  libraryDependencies += "org.typelevel" %% "cats-effect"     % "3.6.3",
  libraryDependencies += "com.lihaoyi"   %% "os-lib"          % "0.11.6",
  libraryDependencies += "ch.qos.logback" % "logback-classic" % "1.3.5",
  libraryDependencies += "com.typesafe.scala-logging" %% "scala-logging" % "3.9.5",
  libraryDependencies += "com.github.scopt" %% "scopt" % scoptVersion,
  libraryDependencies ++= Seq(
    "io.circe" %% "circe-core",
    "io.circe" %% "circe-generic",
    "io.circe" %% "circe-parser"
  ).map(_ % circeVersion),
  libraryDependencies += "com.github.docker-java" % "docker-java-transport-httpclient5" % "3.3.6",
  libraryDependencies += "com.github.docker-java" % "docker-java" % "3.3.6",
  libraryDependencies += "com.googlecode.plist"   % "dd-plist"    % "1.27",
  // Test Dependencies
  libraryDependencies += "org.scalameta" %% "munit"            % "1.2.1" % Test,
  libraryDependencies += "org.scalameta" %% "munit-scalacheck" % "1.2.0" % Test,
  libraryDependencies += "org.typelevel" %% "munit-cats-effect" % "2.1.0" % Test,
  libraryDependencies += "org.scalamock" %% "scalamock" % "7.5.0" % Test
)

lazy val root = project
  .in(file("."))
  .aggregate(common, dispatcher, tester)
  .settings(
    name := "Sugarlyzer",
    // Skip compilation and assembly for the root project
    Compile / compile          := (Compile / compile).value,
    Compile / sources          := Seq.empty,
    Compile / unmanagedSources := Seq.empty,
    Test / sources             := Seq.empty,
    Test / unmanagedSources    := Seq.empty,
    publish / skip             := true
  )

lazy val assemblySettings = Seq(
  assembly / assemblyMergeStrategy := {
    case PathList("META-INF", "maven", "com.kohlschutter.junixsocket", _*) =>
      MergeStrategy.first
    case PathList("META-INF", xs @ _*) =>
      xs map { _.toLowerCase } match {
        case "services" :: xs => MergeStrategy.filterDistinctLines
        case "manifest.mf" :: Nil | "index.list" :: Nil | "dependencies" :: Nil =>
          MergeStrategy.discard
        case _ => MergeStrategy.discard
      }
    case "module-info.class" => MergeStrategy.discard
    case _                   => MergeStrategy.first
  }
)

lazy val common = project
  .in(file("common"))
  .settings(
    commonSettings,
    name := "common"
  )

lazy val dispatcher = project
  .in(file("dispatcher"))
  .dependsOn(common)
  .settings(
    commonSettings,
    assemblySettings,
    name                   := "dispatcher",
    Compile / mainClass    := Some("sugarlyzer.dispatcher.DispatcherApp"),
    Compile / doc / target := file("dispatcher/docs"),
    assembly / assemblyOutputPath := file("dispatcher.jar")
  )

lazy val tester = project
  .in(file("tester"))
  .dependsOn(common)
  .settings(
    commonSettings,
    assemblySettings,
    name                   := "tester",
    Compile / mainClass    := Some("sugarlyzer.tester.TesterApp"),
    Compile / doc / target := file("tester/docs"),
    // Make main resources available to tests
    Test / unmanagedResourceDirectories += (Compile / resourceDirectory).value,
    assembly / assemblyOutputPath := file("tester.jar")
  )

lazy val testerTest = project
  .in(file("tester_test"))
  .dependsOn(common, tester)
  .settings(
    commonSettings,
    assemblySettings,
    name                   := "tester_test",
    Compile / mainClass    := Some("sugarlyzer.tester.test.MainApp"),
    Compile / doc / target := file("tester_test/docs"),
    // Make main resources available to tests
    Test / unmanagedResourceDirectories += (Compile / resourceDirectory).value,
    assembly / assemblyOutputPath := file("tester_test.jar")
  )
