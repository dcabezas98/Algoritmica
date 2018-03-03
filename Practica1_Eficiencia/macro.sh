#!/bin/bash

PROGRAMA=$1

echo "" > $PROGRAMA.dat
i=10

while [ $i -le 35 ]
do
    ./$PROGRAMA $i >> $PROGRAMA.dat
    i=$[$i+1]
done
