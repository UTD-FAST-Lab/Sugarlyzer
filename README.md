# Sugarlyzer

Sugarlyzer is a framework for performing static analysis using off-the-shelf bug finders on C software product lines.

# Prerequisites
This application is written for Python version 3.10.0. We suggest using PyEnv to manage multiple Python versions.
Furthermore, Sugarlyzer runs its analyses in Docker containers in order to maintain consistent
environments across runs, so you must have a working Docker installation. 

# Setup

We recommend creating a virtual environment for Sugarlyzer. To do so, run

`python -m venv <name_of_virtual_environment>`

where 'python' points to a python 3.10.0 installation (note that this may be `python3` on your system.
This will create a new folder.
If, for example, you named your virtual environment 'venv', then you can activate it as follows:

`source ./venv/bin/activate`

Your shell prompt should now have a prefix with the name of the virtual environment.
Now, when you install dependencies, they will be installed into this virtual environment instead of globally.

In order to install Sugarlyzer's dependencies, from the root directory of the repository, run

`python -m pip install -r requirements.txt`

Where `python` points to a Python executable of at least version 3.10.0. 
This will install all of the Python dependencies required. Then, in order to install
the application, run

`python -m pip install -e .`

This installation will put two executables on your system PATH: `dispatcher`, and `tester`.
`dispatcher` is the command you run from your host, while `tester` is the command you run from inside the Docker container (under normal usage, a user
will never invoke `tester` themselves, but it can be useful for debugging to skip
container creation, which can take quite a while. especially for Clang which needs to clone and build LLVM.)

Simply run `dispatcher --help` from anywhere in order to see the helpdoc on how to
invoke Sugarlyzer.

# Usage

`dispatcher` is the primary interface for interacting with Sugarlyzer. Using `dispatcher`, we can run two types of analysis.
First, we can run static analysis on desugared code (our primary contribution).
Second, we can run the sampling-based baseline, which uses configuration samples from Mordahl et al.'s 2019 work "An Empirical Study of Real-World Variability Bugs Detected by Variability-Oblivious Tools."

An example of running static analysis on desugared code can be seen by running

```
dispatcher -t infer -p toybox --jobs <<number of jobs you want to run concurrently>>
```

This will run the Infer static analyzer on the desugared code of Toybox.

# Extending with New Tools

To extend Sugarlyzer with new tools, the following steps must be performed.
1. Add a new dockerfile to `resources/tools/<tool_name>/Dockerfile`. This Dockerfile *must* 1) Inherit from the sugarlyzer/base:latest image, which contains Sugarlyzer and its dependencies, and 2) install the tool so it can be invoked from the command line. *Please note that the tool name that is exposed to the user via the command line and the name of the tool as passed to AbstractTool is the exact same as whatever this folder is named.*
2. Add a new class to `src/sugarlyzer/analyses` that inherits from AbstractTool. The only method that must be implemented is `analyze`, which takes as input a path to a code file and returns an iterable of result files, containing the analysis results. Also, update `src/sugarlyzer/analyses/AnalysisToolFactory` to correctly return an instance of your tool given its name.
3. Add a new reader to `src/sugarlyzer/readers` that inherits from AbstractReader. The only function that must be implemented is `read_output`, which takes as input a report file as produced by the runner implemented in step 2. and returns Alarm objects.*


\* Note that, depending on your needs, it may be necessary to derive your own subtype of `Alarm,` as we do for Clang.

# Extending with New Programs

To extend Sugarlyzer with new programs, the following steps must be performed:
1. Add a new folder to `resources/programs` with the name of the program/set of programs you wish to use. Note that, like tools, Sugarlyzer will use the name of this folder to refer to the program.
2. This folder must have two elements. First, a runnable script (make sure to update the permissions before you try to run Sugarlyzer) that places the program somewhere in the /targets folder. This will be run in the Docker container, so it won't modify your host system. Second, a `program.json` file which contains two fields. "build_script", which contains the name of the build script you just added, and "source_location", which is a list of folders to search for source files. If "source_location" is omitted, all .c files in the /results directory will be used.
