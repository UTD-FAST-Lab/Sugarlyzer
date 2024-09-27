#!/bin/bash
set -x

# Run remove-errors off, recommended space on
find ./resources/programs -type f -name "*.json" | parallel "sed -i 's/\"remove_errors\": true/\"remove_errors\": false/g' {}"

parallel --ungroup -j 1 dispatcher -t {1} -p {2} -r ~/git/Sugarlyzer_results/recommended_space_ON/remove_errors_OFF/{1}/{2}/desugared.json --force -v ::: clang infer phasar ::: axtls varbugs

CURDIR=$(pwd)
cd ../Sugarlyzer_results
find . -type f -name '*.log' | parallel -j 1 git add {}
find . -type f -name '*.json' | parallel -j 1 git add {}
git commit -m 'AUTO: Completed remove_errors OFF, recommended_space ON'
cd ${CURDIR}

# Run remove-errors on, recommended space off.
find ./resources/programs -type f -name "*.json" | parallel "sed -i 's/\"remove_errors\": false/\"remove_errors\": true/g' {}"

parallel --ungroup -j 1 dispatcher -t {1} -p {2} -r ~/git/Sugarlyzer_results/recommended_space_OFF/remove_errors_ON/{1}/{2}/desugared.json --force --no-recommended-space -v ::: clang infer phasar ::: axtls varbugs

CURDIR=$(pwd)
cd ../Sugarlyzer_results
find . -type f -name '*.log' | parallel -j 1 git add {}
find . -type f -name '*.json' | parallel -j 1 git add {}
git commit -m 'AUTO: Completed remove_errors ON, recommended_space OFF'
cd ${CURDIR}

# Run baselines
parallel --ungroup -j 1 dispatcher -t {1} -p {2} -r ~/git/Sugarlyzer_results/baselines/{1}/{2}/baselines.json --force -v --baselines::: clang infer phasar ::: axtls varbugs

CURDIR=$(pwd)
cd ../Sugarlyzer_results
find . -type f -name '*.log' | parallel -j 1 git add {}
find . -type f -name '*.json' | parallel -j 1 git add {}
git commit -m 'AUTO: Completed remove_errors OFF, recommended_space ON'
cd ${CURDIR}

CURDIR=$(pwd)
cd ../Sugarlyzer_results
find . -type f -name '*.log' | parallel -j 1 git add {}
find . -type f -name '*.json' | parallel -j 1 git add {}
git commit -m 'AUTO: Completed baselines'
cd ${CURDIR}
