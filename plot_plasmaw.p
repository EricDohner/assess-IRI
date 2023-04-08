set terminal png size 500, 400
set output 'plot_plasmaw.png'
set xrange [0:8]
set xlabel "Plasma Frequency (MHz)"
set ylabel "Altitude (km)"
set title "Altitude vs. Plasma frequency"
plot "hvsplasmafreq.txt" using 1:2 with lines title "Plasma freq (MHz)"

replot
