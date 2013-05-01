#!/bin/bash

output=$1
games=$2

./blackjack -g $games -dump $output

array=(no-usable usable)
ending=(dat)
for item in ${array[*]}
do
	for type in ${ending[*]}
	do
		name=$output-$item.$type
		echo "reset
		set term postscript
		set output \"./results/graphs/$name.ps\"
		set dgrid3d 10,10 
		set palette defined (0 0 0 0, 1 0 0 1, 3 0 1 0, 4 1 0 0, 6 1 1 1)
		set xtics ('A' 0, '2' 1, '3' 2, '4' 3, '5' 4, '6' 5, '7' 6, '8' 7, '9' 8, '10' 9)
		set xlabel 'Dealer Reveals'
		set ylabel 'Player Sum'
		set ytics ('12' 0, '13' 1, '14' 2, '15' 3, '16' 4 , '17' 5, '18' 6, '19' 7, '20' 8, '21' 9)
		set nokey
		set title '$output $item ace, Probability' 
		splot '$name' using 2:1:3 with lines pal" | gnuplot
		convert ./results/graphs/$name.ps -rotate 90 ./results/graphs/$name.png
		rm ./results/graphs/$name.ps
	done
done

ending=(datpol)
for item in ${array[*]}
do
	for type in ${ending[*]}
	do
		name=$output-$item.$type
		echo "reset
		set term postscript
		set output \"./results/graphs/$name.ps\"
		set dgrid3d 10,10 
		set palette model RGB
		set palette model RGB defined (0 \"blue\", 0 'dark-blue', 1 \"white\", 2 \"white\", 3 \"dark-red\", 3 'red' )
		set xtics ('A' 0, '2' 1, '3' 2, '4' 3, '5' 4, '6' 5, '7' 6, '8' 7, '9' 8, '10' 9)
		set xlabel 'Dealer Reveals'
		set ylabel 'Player Sum' rotate by 270
		set ytics ('12' 0, '13' 1, '14' 2, '15' 3, '16' 4 , '17' 5, '18' 6, '19' 7, '20' 8, '21' 9)
		set view 0,0
		set pm3d
		set nokey
		set title '$output $item ace, Policy' 
		splot '$name' using 2:1:3 with points pal" | gnuplot
		convert ./results/graphs/$name.ps -rotate 90 ./results/graphs/$name.png
		rm ./results/graphs/$name.ps
	done
done

mv *.dat ./results/
mv *.datpol ./results/