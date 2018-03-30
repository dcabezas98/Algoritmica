#!/bin/bash

i=100000

echo "" > tiempos/pos.dat
echo "" > tiempos/pos_OBVIO.dat
while [ $i -le 2500000 ]
do
    ./en-su-posicion $i >> tiempos/pos.dat
    ./en-su-posicion_OBVIO $i >> tiempos/pos_OBVIO.dat
    i=$[$i+100000]
done
