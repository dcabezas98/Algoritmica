#!/bin/bash

SALIDA=salidas/BandB.dat

echo "" > $SALIDA
./tsp_BandB a4 >> $SALIDA
./tsp_BandB att5 >> $SALIDA
./tsp_BandB bayg6 >> $SALIDA
./tsp_BandB berlin7 >> $SALIDA
./tsp_BandB eil8 >> $SALIDA
./tsp_BandB eil9 >> $SALIDA
./tsp_BandB gr10 >> $SALIDA
./tsp_BandB gr11 >> $SALIDA
./tsp_BandB kroD12 >> $SALIDA
./tsp_BandB pcb13 >> $SALIDA
./tsp_BandB pr14 >> $SALIDA
./tsp_BandB pr15 >> $SALIDA
