#!/bin/bash
# My first script
name="DLA-2D"
name1="cluster-datos"
name2="sizesnumber-datos"
VAR=0.05
VAR1=0.5

g++ -std=c++11 $name.cpp -o $name.o
./$name.o > $name.txt

cat <<EOF> $name.gp

#set term pdf
#set output "paths-2D.pdf"
#set xlabel "x"
#set ylabel "y"
#set grid
#set key left top box
#set size square
#plot [-20:20][-20:20] "$name.txt" u 1:2 title "$particle 1" w lp ps $VAR lt rgb# "red" pointtype 7, \
#"$name.txt" u 3:4 title "$particle 2" w lp ps $VAR lt rgb "blue" pointtype 7, \
#"$name.txt" u 5:6 title "$particle 3" w lp ps $VAR lt rgb "green" pointtype 7, #\
#"$name.txt" u 7:8 title "$particle 4" w lp ps $VAR lt rgb "orange" pointtype 7

#set term pdf
#set output "cluster-2D.pdf"
#set xlabel "x"
#set ylabel "y"
#set grid
#set size square
##set key left top box
#plot [-20:20][-20:20] "$name1.txt" u 1:2 title "$cluster 1" w p ps $VAR1 lt rgb# "red" pointtype 7 


set term pdf
set output "distribution-2D.pdf"
set xlabel "Tamaño"
set ylabel "Numero"
set grid
set size square
#set key left top box
plot [0:300][0:30] "$name2.txt" u 1:2 title "$cantidad" w p ps $VAR1 lt rgb "red" pointtype 7 


EOF

gnuplot $name.gp

#okular paths-2D.pdf &
#okular cluster-2D.pdf &
