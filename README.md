# Sugarlyzer

Sugarlyzer is a framework for performing static analysis using off-the-shelf bug finders on C software product lines.

This artifact is capable of running a subset of experiments from our paper. Specifically, this artifact is capable of 
producing the results from Table 3 in RQ1, which show the comparison between our approach and the sampling-based approach. 
Additionally, we can run analysis on the the TOSEM benchmarks (column 3 of Table 6, as well as analysis time).
We are still working on integrating and testing the analysis for the family-based baseline (Column 2 of Table 6) as well as the 
analyses for the Varbugs benchmark (Table 2), and these will be included in a future release of Sugarlyzer.

# Prerequisites
This application is written for Python version >= 3.10.0. We suggest using PyEnv to manage multiple Python versions.
Furthermore, Sugarlyzer runs its analyses in Docker containers in order to maintain consistent
environments across runs, so you must have a working Docker installation. 

# Setup

First, create a virtual environment for Sugarlyzer. To do so, run

`python -m venv <name_of_virtual_environment>`

where 'python' points to a python 3.10.0 or higher installation (note that this may be `python3` on your system).
This will create a new folder.
If, for example, you named your virtual environment 'venv', then you can activate it as follows:

`source ./venv/bin/activate`

Your shell prompt should now have a prefix with the name of the virtual environment.
Now, when you install dependencies, they will be installed into this virtual environment instead of globally.

In order to install Sugarlyzer's dependencies, from the root directory of the repository, run

`pip install -r requirements.txt`

This will install all of the Python dependencies required. Then, in order to install
the application, run

`pip install -e .`

This installation will put two executables on your system PATH: `dispatcher`, and `tester`.
`dispatcher` is the command you run from your host, while `tester` is the command you run from inside the Docker container (under normal usage, a user
will never invoke `tester` themselves, but it can be useful for debugging to skip
container creation, which can take quite a while. especially for Clang which needs to clone and build LLVM.)

Simply run `dispatcher --help` from anywhere in order to see the helpdoc on how to
invoke Sugarlyzer.

# Usage

`dispatcher` is the primary interface for interacting with Sugarlyzer. Using `dispatcher`, we can run two types of analysis.
First, we can run static analysis on desugared code (our primary contribution) (Sections 5.2.2 and 5.3).
Second, we can run the sampling-based baseline, which uses configuration samples from Mordahl et al.'s 2019 work [1] (Section 5.2.2).

An example of running static analysis on desugared code can be seen by running

```
dispatcher -t infer -p toybox --jobs <<number of jobs you want to run concurrently>>
```

This will run the Infer static analyzer on the desugared code of Toybox. Run with 8 cores, this experiment took about 30 minutes, and produces 21 reports.

To run baseline experiments, simply pass the `--baseline` parameter. **However, note that this will, by default, run all 1000 configurations from Mordahl et al.'s FSE 2019 work.** To limit the number of configurations that are run, use the `--sample-size` parameter.
For example, to run Infer's analysis on 10 random configurations of Toybox, use the following command:

```
dispatcher -t infer -p toybox --baselines --sample-size 10 --jobs <<number of jobs you want to run concurrently>
```

Alternative analyzers and target programs can be specified with `-t` and `-p`, respectively.
Currently, the Infer (infer), Clang (clang), and Phasar (phasar) static analyzers are implemented.
We have also integrated six target systems (per Section 5.1).
From Mordahl et al.'s work [1], we integrated axTLS 2.1.4 (axtls), Toybox 0.7.5 (toybox), and Busybox 1.28.0 (busybox).
From von Rhein et al's work [2], we integrated Busybox 1.18.5 (tosembusybox), OpenSSL 1.0.1c (tosemopenssl), uClibc 0.9.33.2 (tosemuclibc).

**Note that baseline experiments only work on the target programs from Mordahl et al's work. The other experiments were run using different tooling that is not a part of this artifact. These experiments will be integrated in a future version of Sugarlyzer.**

# Results

By default, results are written to a `results.json` file in the root directory, but this file can be modified with the `-r` option.
The file is a JSON file, with a list of alarms that were detected during the analysis.
Alarms on desugared inputs have the following relevant fields:

- input_file: The file on which the report was detected.
- input_line: The line in the desugared file on which the alarm was detected.
- original_line: The line(s) in the original file that the input_line corresponds to.
- message: The alarm message
- bug_type: The type of check that was being performed (e.g., a memory leak).
- presence_condition: The condition under which the alarm exists. A blank condition, like "Or(And())" indicates that the alarm is present in all variants of the SPL.

Baseline alarms are formatted somewhat differently. Specifically, instead of presence_condition, they have a "configuration" field that lists configurations under which the alarm was detected.

# Processing Results

We provide a Jupyter notebook, located at `scripts/comparison.ipynb`. This script can tell you the time that desugaring and analysis took (Tables 2 and 6), as well as compare baseline/desugared results to see their overlap (Column 5 of Table 2). 
Instructions for using the notebook are embedded in the notebook.

# Extending with New Tools

Extending Sugarlyzer with new analysis tools is straightforward. To extend Sugarlyzer with new tools, the following steps must be performed.
1. Add a new dockerfile to `resources/tools/<tool_name>/Dockerfile`. This Dockerfile *must* 1) Inherit from the sugarlyzer/base:latest image, which contains Sugarlyzer and its dependencies, and 2) install the tool so it can be invoked from the command line. *Please note that the tool name that is exposed to the user via the command line and the name of the tool as passed to AbstractTool is the exact same as whatever this folder is named.*
2. Add a new class to `src/sugarlyzer/analyses` that inherits from AbstractTool. The only method that must be implemented is `analyze`, which takes as input a path to a code file and returns an iterable of result files, containing the analysis results. Also, update `src/sugarlyzer/analyses/AnalysisToolFactory` to correctly return an instance of your tool given its name.
3. Add a new reader to `src/sugarlyzer/readers` that inherits from AbstractReader. The only function that must be implemented is `read_output`, which takes as input a report file as produced by the runner implemented in step 2. and returns Alarm objects.*

\* Note that, depending on your needs, it may be necessary to derive your own subtype of `Alarm,` as we do for Clang.

# Extending with New Programs

The process for extending Sugarlyzer with new programs is more involved, and we are happy to help with such an integration. Generally, the process looks like this:
1. Add a new folder to `resources/programs` with the name of the program/set of programs you wish to use. Note that, like tools, Sugarlyzer will use the name of this folder to refer to the program.
2. This folder must have two elements. First, a runnable script (make sure to update the permissions before you try to run Sugarlyzer) that places the program somewhere in the /targets folder. This will be run in the Docker container, so it won't modify your host system. Second, a `program.json` file. The program.json file must contain various fields which tell Sugarlyzer how the code is structures. We suggest looking at existing files for examples. The required fields are a "build_script," which contains the location of the aforementioned script. Next, a "project_root," which contains the name of the root folder of the source code. Next, an "included_files_and_directories," which will tell Sugarlyzer which files and directories need to be included to compile each file. This field is a list of records, where each record contains an "included_files" and "included_directories" field. For example, an excerpt of axTLS's file is shown below:
  
```
"included_files_and_directories": [
   {
       "included_files": [
             "/SugarlyzerConfig/axtlsInc.h"
       ],
       "included_directories": [
             "/SugarlyzerConfig/",
             "/SugarlyzerConfig/stdinc/usr/include/",
             "/SugarlyzerConfig/stdinc/usr/include/x86_64-linux-gnu/",
             "/SugarlyzerConfig/stdinc/usr/lib/gcc/x86_64-linux-gnu/9/include/"
       ]
   },
   {
         "file_pattern": "aes\\.c$",
         "included_files": [],
         "included_directories": [
               "config",
               "ssl",
               "crypto"
         ]
   }
]
```

The first entry applies to all files in axTLS -- i.e., every file should be compiled with the axtlsInc.h file, as well as the directories listed under included_directories. The second entry has a filter (`file_pattern`), which tells us that for any file that matches the regular expression `aes\.c`, we should additionally include the `config`, `ssl`, and `crypto` directories when we compile the file.

[1] Mordahl, Austin, Jeho Oh, Ugur Koc, Shiyi Wei, and Paul Gazzillo. "An empirical study of real-world variability bugs detected by variability-oblivious tools." In Proceedings of the 2019 27th ACM Joint Meeting on European Software Engineering Conference and Symposium on the Foundations of Software Engineering, pp. 50-61. 2019.

[2] Rhein, Alexander Von, Jörg Liebig, Andreas Janker, Christian Kästner, and Sven Apel. "Variability-aware static analysis at scale: An empirical study." ACM Transactions on Software Engineering and Methodology (TOSEM) 27, no. 4 (2018): 1-33.

[3] Abal, Iago, Jean Melo, Ştefan Stănciulescu, Claus Brabrand, Márcio Ribeiro, and Andrzej Wąsowski. "Variability bugs in highly configurable systems: A qualitative analysis." ACM Transactions on Software Engineering and Methodology (TOSEM) 26, no. 3 (2018): 1-34.
