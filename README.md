# Framework for Performing Product- and Transformation-based Analysis of C systems

This artifact includes the code used to run product- and transformation-based analysis on C SPLs.

# Prerequisites

Everything runs in Docker. You do not need anything installed on your machine.

- Docker
- GNU Parallel if running `runProduct.sh` and `runTransformation.sh`

# Setup

From the repository root:

```sh
docker compose build
```

This builds four images from the one `Dockerfile`:

| Image | Base | Contents |
| --- | --- | --- |
| `sugarlyzer-program` | Ubuntu 18.04 | Build environment for the subjects, and SugarC. BusyBox 1.28 needs this older glibc. |
| `sugarlyzer-clang` | Ubuntu 22.04 | Clang 11 static analyzer |
| `sugarlyzer-infer` | Ubuntu 22.04 | Infer 1.2.0 |
| `sugarlyzer-cppcheck` | Ubuntu 22.04 | CppCheck |


The first build will take a while. Later builds will use Docker's cache and only redo what changed. 
After changing any code run `docker compose build` again before runnign experiments.
For a clean rebuild: `docker compose build --no-cache`.

The Tester (`tester.jar`) is compiled inside the build, so the images always contain the current code.

# Usage

> [!WARNING]
> **Runs can use a lot of RAM and Disk Space.**

Note that the VBDb benchmark is called 'varbugs' in the options.
The analysis will run in a combination of Docker containers. 
Family-based analysis is run separately; please see the top-level artifact documentation for more information.

## Running one experiment

```sh
./run.sh -t <TOOL> -p <PROGRAM> [-s STRATEGY] [-n SAMPLES] [-j JOBS] [-o OUT]
```

## Running all experiments

```sh
./runBaselines.sh JOBS SAMPLES
./runDesugared.sh JOBS
```

# Results

`results_vbdb` contains the results of running the analysis on the VBDb benchmark, as well as classification artifacts and helper scripts we used.

# Scripts

`scripts` contains the notebooks and scripts used to obtain the results reported in RQ2. `preliminary.ipynb` contains the code for running the preliminary study mentioned in Section 5.1. `varbugs.ipynb` computes all the data and creates the Venn diagram and Table 1 for RQ2.1, and `realworld.ipynb` computes the results and creates the Venn diagram for RQ2.2. `performance.py` produces Table 2 based on a performance log directory, assuming each log is named <tool>_<target>_<strategy>.log. Note that family-based results in Table 2 were computed and added manually, as family-based analysis is not a part of this framework.
