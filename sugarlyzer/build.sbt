val scala3Version = "3.8.0-RC1"

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

  // Test Dependencies
  libraryDependencies += "org.scalameta" %% "munit"            % "1.2.1" % Test,
  libraryDependencies += "org.scalameta" %% "munit-scalacheck" % "1.2.0" % Test,
  libraryDependencies += "org.scalamock" %% "scalamock"        % "7.5.0" % Test
)

lazy val root = project
  .in(file("."))
  .aggregate(dispatcher, tester)
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

lazy val dispatcher = project
  .in(file("dispatcher"))
  .settings(
    commonSettings,
    name                   := "dispatcher",
    Compile / doc / target := file("dispatcher/docs")
  )

lazy val tester = project
  .in(file("tester"))
  .settings(
    commonSettings,
    name                   := "tester",
    Compile / doc / target := file("tester/docs")
  )
