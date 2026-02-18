#!/bin/bash

for i in `seq 1 1 10`; do
    export OMP_NUM_THREADS=$i
    ./pso
done

for i in `seq 1 1 10`; do
    ./pso $i
done
