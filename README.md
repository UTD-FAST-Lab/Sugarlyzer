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

