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
