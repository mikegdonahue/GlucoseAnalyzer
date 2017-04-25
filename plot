set terminal jpeg
set output "/GlucoseAnalyzer/site/output.jpg"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5
set title "Glucose Levels"
set xlabel "Days"
set ylabel "Glucose Blood Level (mg/dL)"
set grid
plot 'plotdata.dat' with linespoints ls 1
