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

Interact with `dispatcher.jar` to do the product-based and transformation-based analyses. Run `java -jar dispatcher.jar --help` to see the options that the application takes. The analysis will run in a combination of Docker containers. Family-based analysis is run separately; please see the top-level artifact documentation for more information.

We have provided `runProduct.sh` and `runTransformation.sh.` These run all of the product-based and transformation-based analyses, respectively. You can run individual analyses using `java -jar dispatcher.jar <options>`.
