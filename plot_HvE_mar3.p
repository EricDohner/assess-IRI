set terminal png size 800, 600
set output 'plot_NE_0303_1100.png'
set xlabel "N_e (m^{-3})"
set ylabel "Altitude (km)"
set title "Altitude vs. N"
set xrange[0:4.8E11]

set label "NME, HME" at 118537142272.000000, 110.000000
set label "NMF1, HMF1" at 216448450560.000000, 166.305466
set label "NMF2, HMF1" at 385372487680.000000, 228.481354
plot "hvse.txt" using 1:2 with lines title "N_e (m^{-3})"
show label

replot
