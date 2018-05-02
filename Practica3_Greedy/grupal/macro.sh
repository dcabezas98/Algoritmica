#!/bin/bash

alg=doubleNearest

echo "" > tiempos/$alg.dat

./tsp-$alg ulysses16 >> tiempos/$alg.dat
./tsp-$alg ulysses22 >> tiempos/$alg.dat
./tsp-$alg att48 >> tiempos/$alg.dat
./tsp-$alg st70 >> tiempos/$alg.dat
./tsp-$alg eil101 >> tiempos/$alg.dat
./tsp-$alg ch150 >> tiempos/$alg.dat
./tsp-$alg gr202 >> tiempos/$alg.dat
./tsp-$alg a280 >> tiempos/$alg.dat
./tsp-$alg pcb442 >> tiempos/$alg.dat
./tsp-$alg pa561 >> tiempos/$alg.dat
./tsp-$alg gr666 >> tiempos/$alg.dat
./tsp-$alg pr1002 >> tiempos/$alg.dat
./tsp-$alg pr2392 >> tiempos/$alg.dat
