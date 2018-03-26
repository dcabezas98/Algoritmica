#!/bin/bash

i=1000

while [ $i -le 25000 ]
do
    ./genera-ensuposicion $i > ejemplos/distintos_$i.txt
    i=$[$i+1000]
done
