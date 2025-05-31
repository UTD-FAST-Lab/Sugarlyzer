# Artifact for "An Empirical Study of Static Analysis-Based Variability Bug Detection"

This artifact includes the code and data for RQ2 of our submission entitled "An Empirical Study of Static Analysis-Based Variability Bug Detection."

# Prerequisites

This application is written for Python version >= 3.13.We suggest using PyEnv to manage multiple Python versions.
Furthermore, we utilize Docker containers in order to maintain consistent environments across runs, so you must have a working Docker installation. 

# Setup

## Product- and Transformation-Based Approaches

First, create a virtual environment.

`python -m venv <name_of_virtual_environment>`

where 'python' points to a python 3.13.0 or higher installation (note that this may be `python3` on your system).
This will create a new folder.

If, for example, you named your virtual environment 'venv', then you can activate it as follows:

`source ./venv/bin/activate`

Your shell prompt should now have a prefix with the name of the virtual environment.
Now, when you install dependencies, they will be installed into this virtual environment instead of globally.

In order to install dependencies, from the root directory of the repository, run

`pip install -r requirements.txt`

This will install all of the Python dependencies required. Then, in order to install
the application, run

`pip install -e .`

This installation will put two executables on your system PATH: `dispatcher`, and `tester`.
`dispatcher` is the command you run from your host, while `tester` is the command you run from inside the Docker container (under normal usage, a user
will never invoke `tester` themselves, but it can be useful for debugging to skip
container creation, which can take quite a while. especially for Clang which needs to clone and build LLVM.)

Simply run `dispatcher --help` from anywhere in order to see the helpdoc on how to
invoke the tool. Running with the "--baselines" flag causes the tool to run the product-based mode. Otherwise, it will run the transformation-based analysis.

## Family-Based Analysis

The scripts to run the family-based analysis are available under `./scripts/family.` However, these require the TypeChef VAA to be installed, which is non-trivial. We are in the process of providing a virtual machine with the necessary setup so that these experiments can be replicated.

# Usage

An example of running static analysis on desugared code can be seen by running

```
dispatcher -t infer -p toybox --jobs <<number of jobs you want to run concurrently>>
```

This will run the Infer static analyzer on the desugared code of Toybox. Run with 8 cores, this experiment took about 30 minutes, and produces 21 reports.

To run baseline experiments, simply pass the `--baseline` parameter. For example, to run Infer's analysis on 10 random configurations of Toybox, use the following command:

```
dispatcher -t infer -p toybox --baselines --sample-size 10 --jobs <<number of jobs you want to run concurrently>
```

## Provided Scripts

We have provided `runDesugared.sh` and `runBaselines.sh.` These run the desugared analysis, the product-based analysis, and a small subset of experiments respectively.

[2] Rhein, Alexander Von, Jörg Liebig, Andreas Janker, Christian Kästner, and Sven Apel. "Variability-aware static analysis at scale: An empirical study." ACM Transactions on Software Engineering and Methodology (TOSEM) 27, no. 4 (2018): 1-33.

[3] Abal, Iago, Jean Melo, Ştefan Stănciulescu, Claus Brabrand, Márcio Ribeiro, and Andrzej Wąsowski. "Variability bugs in highly configurable systems: A qualitative analysis." ACM Transactions on Software Engineering and Methodology (TOSEM) 26, no. 3 (2018): 1-34.
