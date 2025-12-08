package sugarlyzer.models

import java.io.File
import java.nio.file.{Files, Path, Paths}
import scala.collection.mutable
import scala.io.Source
import scala.jdk.CollectionConverters.*
import scala.sys.process.*
import scala.util.matching.Regex

/** Case class representing a baseline configuration for analysis */
case class BaselineConfig(
    sourceFile: Path,
    configuration: Option[Path],
    macros: Option[List[(String, String)]]
)

/** Specification for how to build and analyze a program */
class ProgramSpecification(
    val name: String,
    buildScript: String,
    projectRootPath: String,
    val configPrefix: Option[String] = None,
    val whitelist: Option[String] = None,
    val kgenMap: Option[String] = None,
    val removeErrors: Boolean = false,
    sourceDir: Option[String] = None,
    makeRootPath: Option[String] = None,
    includedFilesAndDirectories: List[Map[String, Any]] = List.empty,
    sampleDir: Option[String] = None,
    oldconfigLocation: Option[String] = None
) {

  val noStdLibs: Boolean                      = true
  val incDirsAndFiles: List[Map[String, Any]] = includedFilesAndDirectories

  private val _oldconfigLocation: String =
    oldconfigLocation.getOrElse("config/.config")
  private var _searchContext: String = "/targets"
  private val extractedFiles: String = "usr/local/bin/extracted_files.txt"

  // Memoization cache for tryResolvePath
  private val pathCache: mutable.Map[(String, Path), Path] = mutable.Map.empty

  def oldconfigLocationPath: Path =
    tryResolvePath(_oldconfigLocation, makeRoot)

  def searchContext: Path = {
    val p = Paths.get(_searchContext)
    if !Files.exists(p) then throw RuntimeException(
      s"Search context $p does not exist."
    )
    else
      p
  }

  def searchContext_=(value: String): Unit =
    _searchContext = value

  def projectRoot: Path =
    tryResolvePath(projectRootPath, searchContext)

  def sourceDirectory: Path =
    sourceDir.map(sd => tryResolvePath(sd, searchContext)).getOrElse(
      projectRoot
    )

  def sampleDirectory: Option[Path] =
    sampleDir.map(sd => tryResolvePath(sd, getResourcesPath))

  def makeRoot: Path =
    makeRootPath.map(mr => tryResolvePath(mr, searchContext)).getOrElse(
      projectRoot
    )

  def buildScriptPath: Path =
    tryResolvePath(buildScript, getResourcesPath)

  /** Helper to get the resources path (equivalent to importlib.resources.path) */
  private def getResourcesPath: Path =
    // In Scala/JVM, resources are typically accessed differently
    /* This provides a reasonable default; adjust based on your project
     * structure */
    Paths.get(sys.props.getOrElse("user.dir", "."), "resources", "programs")

  /** Returns all .c or .i files that are in the program's source locations */
  def getSourceFiles: Iterator[Path] = {
    val file = new File(extractedFiles)
    if file.exists() then Source.fromFile(file).getLines().map(f =>
      Paths.get(f, f)
    )
    else
      Iterator.empty
  }

  /** Iterates through the program.json's get_recommended_space field,
    * returning the first match.
    *
    * @param file The source file to search for.
    * @return (included_files, included_directories, macro_definitions) for the first object
    *         in get_recommended_space with a regular expression that matches the absolute file name.
    */
  def incFilesAndDirsForFile(file: Path)
      : (List[Path], List[Path], List[String]) = {
    val incDirs  = mutable.ListBuffer.empty[Path]
    val incFiles = mutable.ListBuffer.empty[Path]
    val cmdDecs  = mutable.ListBuffer.empty[String]

    for spec <- incDirsAndFiles do {
      val filePattern = spec.get("file_pattern").map(_.toString)
      val matches = filePattern.forall(pattern =>
        new Regex(pattern).findFirstIn(file.toAbsolutePath.toString).isDefined
      )

      if matches then {
        val relativeTo = spec.get("relative_to")
          .map(rt => Paths.get(rt.toString))
          .getOrElse(projectRoot)

        spec.get("included_files") match {
          case Some(files: List[?]) =>
            incFiles ++= files.map(p => tryResolvePath(p.toString, relativeTo))
          case _ => ()
        }

        spec.get("included_directories") match {
          case Some(dirs: List[?]) =>
            incDirs ++= dirs.map(p => tryResolvePath(p.toString, relativeTo))
          case _ => ()
        }

        spec.get("macro_definitions") match {
          case Some(defs: List[?]) =>
            cmdDecs ++= defs.map(_.toString)
          case _ => ()
        }
      }
    }

    (incFiles.toList, incDirs.toList, cmdDecs.toList)
  }

  /** Runs the script to obtain the program's source code.
    * @return The return code
    */
  def download(): Int =
    Process(buildScriptPath.toString).!

  /** Tries to resolve a path from a given root directory.
    * Results are cached for performance.
    *
    * @param path The path to resolve.
    * @param root The root from which to try to resolve the path.
    * @return The fully resolved path.
    */
  def tryResolvePath(path: String, root: Path): Path =
    pathCache.getOrElseUpdate(
      (path, root),
      resolvePathUncached(Paths.get(path), root)
    )

  def tryResolvePath(path: Path, root: Path): Path =
    pathCache.getOrElseUpdate(
      (path.toString, root),
      resolvePathUncached(path, root)
    )

  private def resolvePathUncached(path: Path, root: Path): Path = {
    if path == null then throw IllegalArgumentException("Supplied path is None")

    if path.getFileName == root.getFileName then return root

    if path.isAbsolute then return path

    val joinedPath = root.resolve(path)
    if Files.exists(joinedPath) then return joinedPath.toAbsolutePath

    val results = mutable.Set.empty[Path]
    Files.walk(root).iterator().asScala.foreach { rootDir =>
      if Files.isDirectory(rootDir) then {
        val cur = rootDir.resolve(path)
        if Files.exists(cur) then results += cur
      }
    }

    results.size match {
      case 0 =>
        throw java.io.FileNotFoundException(
          s"Could not resolve path $path from root $root"
        )
      case 1 =>
        results.head
      case _ =>
        throw RuntimeException(
          s"Path $path in root $root is ambiguous. Found the following potential results: " +
            s"$results. Try adding more context information to the index.json file, " +
            s"so that the path is unique."
        )
    }
  }

  /** Returns baseline configurations for analysis.
    * If no sample directory exists, generates all possible macro configurations.
    */
  def getBaselineConfigurations: Iterator[BaselineConfig | Path] =
    sampleDirectory match {
      case None =>
        /* If we don't have a sample directory, use get_all_macros to get every
         * possible configuration */
        getSourceFiles.flatMap { sourceFile =>
          val macros = getAllMacros(sourceFile)
          allConfigurations(macros).map { config =>
            BaselineConfig(sourceFile, None, Some(config))
          }
        }
      case Some(sampleDir) =>
        Files.list(tryResolvePath(sampleDir.toString, Paths.get(".")))
          .iterator()
          .asScala
    }

  /** Generates all possible DEF/UNDEF combinations for the given macros */
  private def allConfigurations(options: List[String])
      : List[List[(String, String)]] =
    options match {
      case Nil => List(List.empty)
      case head :: tail =>
        for {
          config   <- allConfigurations(tail)
          defState <- List("DEF", "UNDEF")
        } yield (defState, head) :: config
    }

  /** Discovers all macros in a source file using a preprocessor.
    * Note: This requires implementing MacroDiscoveryPreprocessor in Scala.
    *
    * @param filePath The path to the source file.
    * @return List of discovered macro names.
    */
  def getAllMacros(filePath: Path): List[String] = {
    val content        = Source.fromFile(filePath.toFile).mkString
    val ifdefPattern   = """#(?:ifdef|ifndef)\s+(\w+)""".r
    val definedPattern = """defined\s*\(\s*(\w+)\s*\)""".r

    val macros = mutable.Set.empty[String]
    ifdefPattern.findAllMatchIn(content).foreach(m => macros += m.group(1))
    definedPattern.findAllMatchIn(content).foreach(m => macros += m.group(1))

    macros.toList
  }
}

object ProgramSpecification {

  /** Factory method to create ProgramSpecification from a configuration map */
  def fromConfig(config: Map[String, Any]): ProgramSpecification =
    ProgramSpecification(
      name = config("name").toString,
      buildScript = config("build_script").toString,
      projectRootPath = config("project_root").toString,
      configPrefix = config.get("config_prefix").map(_.toString),
      whitelist = config.get("whitelist").map(_.toString),
      kgenMap = config.get("kgen_map").map(_.toString),
      removeErrors =
        config.get("remove_errors").exists(_.asInstanceOf[Boolean]),
      sourceDir = config.get("source_dir").map(_.toString),
      makeRootPath = config.get("make_root").map(_.toString),
      includedFilesAndDirectories = config.get("included_files_and_directories")
        .map(_.asInstanceOf[List[Map[String, Any]]])
        .getOrElse(List.empty),
      sampleDir = config.get("sample_dir").map(_.toString),
      oldconfigLocation = config.get("oldconfig_location").map(_.toString)
    )
}
