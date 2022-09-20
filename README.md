# Sugarlyzer

# Prerequisites
This application is written for Python version >= 3.10.0. Furthermore, 
Sugarlyzer runs its analyses in Docker containers in order to maintain consistent
environments across runs, so you must have a working Docker installation.

# Usage

We recommend creating a virtual environment for Sugarlyzer. To do so, run

`python -m venv <name_of_virtual_environment>`

where 'python' points to a python 3.10.0 or higher installation. This will create a new folder. If, for example, you named your virtual environment 'venv', then
you can activate it as follows:

`source ./venv/bin/activate`

In order to install Sugarlyzer's dependencies, from the root directory of the repository, run

`python -m pip install -r requirements.txt`

Where `python` points to a Python executable of at least version 3.10.0. 
This will install all of the Python dependencies required. Then, in order to install
the application, run

`python -m pip install .`

This installation will put three executables on your system PATH: `dispatcher`, and `tester`.
`dispatcher` is the command you run from your host, while `tester` is the command you run from inside the Docker container (under normal usage, a user
will never invoke `tester` themselves, but it can be useful for debugging to skip
container creation, which can take quite a while. especially for Clang which needs to clone and build LLVM.)

Simply run `dispatcher --help` from anywhere in order to see the helpdoc on how to
invoke Sugarlyzer.

# Extending with New Tools

To extend Sugarlyzer with new tools, the following steps must be performed.
1. Add a new dockerfile to `resources/tools/<tool_name>/Dockerfile`. This Dockerfile *must* 1) Inherit from the sugarlyzer/base:latest image, which contains Sugarlyzer and its dependencies, and 2) install the tool so it can be invoked from the command line. *Please note that the tool name that is exposed to the user via the command line and the name of the tool as passed to AbstractTool is the exact same as whatever this folder is named.*
2. Add a new class to `src/sugarlyzer/analyses` that inherits from AbstractTool. The only method that must be implemented is `analyze`, which takes as input a path to a code file and returns an iterable of result files, containing the analysis results. Also, update `src/sugarlyzer/analyses/AnalysisToolFactory` to correctly return an instance of your tool given its name.
3. Add a new reader to `src/sugarlyzer/readers` that inherits from AbstractReader. The only function that must be implemented is `read_output`, which takes as input a report file as produced by the runner implemented in step 2. and returns Alarm objects.*


\* Note that, depending on your needs, it may be necessary to derive your own subtype of `Alarm,` as we do for clang.
