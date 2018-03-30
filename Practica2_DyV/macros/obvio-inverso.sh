#!/bin/bash

echo "" > tiempos/obvio-inverso-distintos.dat
echo "" > tiempos/obvio-inverso-repetidos.dat

i=100000
while [ $i -le 2500000 ]
do
    ./obvio_inverso $i >> tiempos/obvio-inverso-distintos.dat
    ./obvio_inverso_rep $i >> tiempos/obvio-inverso-repetidos.dat
    i=$[$i+100000]
done

