
set mxtics 2
set mytics 2
set grid
set grid mxtics
set grid mytics
set grid xtics ytics
set xrange [0:1] 

set style line 1 lc "#000000" lw 3
set style line 2 lc "#0000FF" lw 3
set style line 3 lc "#FF0000" lw 3
set style line 4 lc "#00FF00" lw 3
set style line 5 lc "#FF00FF" lw 3
set style line 6 lc "#FF8833" lw 3

set term png size 960,840 font 20 enhanced

set output 'run.log.trace.png'
plot 'run.log.trace' using ($1):($2) title 'x' with linespoints linestyle 2 pointtype 7 pointsize 2

