set terminal png size 800, 600
set output 'plot_NE_0304_2300.png'
set xlabel "N_e (m^{-3})"
set ylabel "Altitude (km)"
set title "Altitude vs. N, Mar 4 2023, 2300 UTC"
set xrange[0:1.5E11]

#set label "NMD, HMD" at 400000000.000000, 87.898422
set label "NME, HME" at 1837059840.000000, 110.000000
set label "NMF2, HMF2" at 110060593152.000000, 299.341187
plot "hvse.txt" using 1:2 with lines title "N_e (m^{-3})"
show label

replot
