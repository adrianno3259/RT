#!/bin/bash

# execução sem a grid:

while read x
do
	COUNTER=1
	while [ $COUNTER -lt 101 ];
	do
		echo Executando para  $COUNTER esferas
		echo $x $COUNTER > params.in
		time ./My_Raytracer < params.in
		COUNTER=$(($COUNTER * 10))
	done
done < input.txt

