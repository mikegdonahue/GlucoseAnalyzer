set terminal jpeg
set output "output.jpg"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5
set title "Last 30 Days of Glucose Levels"
set xlabel "Days"
set ylabel "mg/dL"
set grid
plot 'plotdata.dat' using 1:2 with linespoints ls 1
