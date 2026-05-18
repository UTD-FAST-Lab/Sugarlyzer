# Artifact for "An Empirical Study of Static Analysis-Based Variability Bug Detection in C"

This artifact includes the code and data for RQ2 of our submission entitled "An Empirical Study of Static Analysis-Based Variability Bug Detection in C"

# Prerequisites

- Docker
- Java 17+
- sbt 1.12.9+
- GNU Parallel if running `runProduct.sh` and `runTransformation.sh`

# Setup

Navigate to the `sugarlyzer` directory and run `make` to build `dispatcher.jar` and `tester.jar`.

# Usage

Interact with `dispatcher.jar` to do the product-based and transformation-based analyses. Run `java -jar dispatcher.jar --help` to see the options that the application takes. Note that the VBDb benchmark is called 'varbugs' in the JAR options. The analysis will run in a combination of Docker containers. Family-based analysis is run separately; please see the top-level artifact documentation for more information.

We have provided `runProduct.sh` and `runTransformation.sh.` These run all of the product-based and transformation-based analyses, respectively. You can run individual analyses using `java -jar dispatcher.jar <options>`.

# Results

`results_vbdb` contains the results of running the analysis on the VBDb benchmark, as well as classification artifacts and helper scripts we used.

# Scripts

`scripts` contains the notebooks and scripts used to obtain the results reported in RQ2. `preliminary.ipynb` contains the code for running the preliminary study mentioned in Section 5.1. `varbugs.ipynb` computes all the data and creates the Venn diagram and Table 1 for RQ2.1, and `realworld.ipynb` computes the results and creates the Venn diagram for RQ2.2. `performance.py` produces Table 2 based on a performance log directory, assuming each log is named <tool>_<target>_<strategy>.log. Note that family-based results in Table 2 were computed and added manually, as family-based analysis is not a part of this framework.
