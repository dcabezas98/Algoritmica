#!/bin/bash

i=100000

echo "" > tiempos/pos_Repetidos.dat
#echo "" > tiempos/pos_Repetidos_OBVIO.dat
while [ $i -le 2500000 ]
do
    ./en-su-posicion_Repetidos $i >> tiempos/pos_Repetidos.dat
    #./en-su-posicion_Repetidos_OBVIO $i >> tiempos/pos_Repetidos_OBVIO.dat
    i=$[$i+100000]
done
