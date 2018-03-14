#!/bin/bash

files=(burbuja insercion seleccion mergesort quicksort heapsort hanoi floyd)

for file in files
do
gnuplot <<-EOF
	set xlabel "Tamaño"
	set ylabel "Tiempo (seg)"
	set title "${file}"   
	set term png
	set output "${file}.png"
	plot "${file}/${file}.dat" title 'David', "${file}/${file}_emilio.dat" title 'Emilio', "${file}/${file}_inma.dat" title 'Inma', "${file}/${file}_patri.dat" title 'Patricia' with points
EOF
done
        
        # set xlabel "Tamaño"
	# set ylabel "Tiempo (seg)"
	# set title "burbuja"   
	# set term png
	# set output "burbuja.png"
	# plot "burbuja/burbuja.dat" title 'David', "burbuja/burbuja_emilio.dat" title 'Emilio', "burbuja/burbuja_inma.dat" title 'Inma', "burbuja/burbuja_patri.dat" title 'Patricia' with points

	# set xlabel "Tamaño"
	# ylabel "Tiempo (seg)"
	# title "seleccion"   
	# set term png
	# set output "seleccion.png"
	# plot "seleccion/seleccion.dat" title 'David', "seleccion/seleccion_emilio.dat" title 'Emilio', "seleccion/seleccion_inma.dat" title 'Inma', "seleccion/seleccion_patri.dat" title 'Patricia' with points

	# set xlabel "Tamaño"
	# ylabel "Tiempo (seg)"
	# title "insercion"   
	# set term png
	# set output "insercion.png"
	# plot "insercion/insercion.dat" title 'David', "insercion/insercion_emilio.dat" title 'Emilio', "insercion/insercion_inma.dat" title 'Inma', "insercion/insercion_patri.dat" title 'Patricia' with points

	# set xlabel "Tamaño"
	# ylabel "Tiempo (seg)"
	# title "mergesort"   
	# set term png
	# set output "mergesort.png"
	# plot "mergesort/mergesort.dat" title 'David', "mergesort/mergesort_emilio.dat" title 'Emilio', "mergesort/mergesort_inma.dat" title 'Inma', "mergesort/mergesort_patri.dat" title 'Patricia' with points
	
	# set xlabel "Tamaño"
	# ylabel "Tiempo (seg)"
	# title "quicksort"   
	# set term png
	# set output "quicksort.png"
	# plot "quicksort/quicksort.dat" title 'David', "quicksort/quicksort_emilio.dat" title 'Emilio', "quicksort/quicksort_inma.dat" title 'Inma', "quicksort/quicksort_patri.dat" title 'Patricia' with points

	# set xlabel "Tamaño"
	# ylabel "Tiempo (seg)"
	# title "heapsort"   
	# set term png
	# set output "heapsort.png"
	# plot "heapsort/heapsort.dat" title 'David', "heapsort/heapsort_emilio.dat" title 'Emilio', "heapsort/heapsort_inma.dat" title 'Inma', "heapsort/heapsort_patri.dat" title 'Patricia' with points

	# set xlabel "Tamaño"
	# ylabel "Tiempo (seg)"
	# title "floyd"   
	# set term png
	# set output "floyd.png"
	# plot "floyd/floyd.dat" title 'David', "floyd/floyd_emilio.dat" title 'Emilio', "floyd/floyd_inma.dat" title 'Inma', "floyd/floyd_patri.dat" title 'Patricia' with points

	# set xlabel "Tamaño"
	# ylabel "Tiempo (seg)"
	# title "hanoi"   
	# set term png
	# set output "hanoi.png"
	# plot "hanoi/hanoi.dat" title 'David', "hanoi/hanoi_emilio.dat" title 'Emilio', "hanoi/hanoi_inma.dat" title 'Inma', "hanoi/hanoi_patri.dat" title 'Patricia' with points

