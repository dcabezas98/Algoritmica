#!/bin/bash

PROGRAMA=$1

echo "" > $PROGRAMA.dat
i=1000

while [ $i -le 25000 ]
do
    ./$PROGRAMA $i >> $PROGRAMA.dat
    i=$[$i+1000]
done
