#!/bin/bash

if [ -z "$1" ]; then
    echo "Error: first parameter should be the number of jobs to use."
    exit 1
fi

mkdir logs/
mkdir results/

parallel --dryrun --ungroup --progress -j 1 "mkdir -p logs/{1}; java -jar dispatcher.jar -t {2} -p {3} --results_dir ./results/{1}/{2}_{3}_{4} -s {4} -j $1 |& tee -i logs/{1}/{2}_{3}_{4}.log" ::: 1 2 3 4 5 ::: clang infer ::: axtls toybox busybox ::: product transformation
