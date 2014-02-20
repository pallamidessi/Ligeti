set term png
set output "weierstrass.png"
set xrange[0:20480]
set xlabel "Number of Evaluations"
set ylabel "Fitness"
plot 'weierstrass.dat' using 3:4 t 'Best Fitness' w lines, 'weierstrass.dat' using 3:5 t  'Average' w lines, 'weierstrass.dat' using 3:6 t 'StdDev' w lines
