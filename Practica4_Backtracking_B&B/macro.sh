#!/bin/bash

echo "" > tiempos.dat
echo "" > tiempos_fuerza_bruta.dat

for i in `seq 3 12`
do
    ./tiempo_cena $i >> tiempos.dat
    ./tiempo_cena_fuerza_bruta $i >> tiempos_fuerza_bruta.dat
done
