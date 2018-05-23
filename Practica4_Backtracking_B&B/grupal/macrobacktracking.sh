#!/bin/bash

SALIDA=salidas/backtracking.dat

echo "" > $SALIDA
./tsp_backtracking a4 >> $SALIDA
./tsp_backtracking att5 >> $SALIDA
./tsp_backtracking bayg6 >> $SALIDA
./tsp_backtracking berlin7 >> $SALIDA
./tsp_backtracking eil8 >> $SALIDA
./tsp_backtracking eil9 >> $SALIDA
./tsp_backtracking gr10 >> $SALIDA
./tsp_backtracking gr11 >> $SALIDA
./tsp_backtracking kroD12 >> $SALIDA
./tsp_backtracking pcb13 >> $SALIDA
./tsp_backtracking pr14 >> $SALIDA
./tsp_backtracking pr15 >> $SALIDA
