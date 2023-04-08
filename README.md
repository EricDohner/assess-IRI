# assess-IRI
ERT assessment: IRI model

The code contained in this repository runs the IRI model and generates vertical electron density profile data. Gnuplot scripts are included for generating the plots (also included).

The code requires the IRI model files and accessory data files to be contained within the same directory as call_IRI.c. 

"inputs.txt" contains the input parameters necessary to run the code -- geographic coordinates, date and time, etc.
"indat_jf.txt" contains the true/false inputs to the IRI model. They're set to the defaults, and stored as integers for ease of interface with Fortran.

"outputparams.txt" contains some outputs from the IRI model that are useful, but not part of the actual "(N, h)" density profile output file.

"Make" compiles all code. 

"Make run" runs call_IRI.exe.

"gnuplot plot_plasmaw.p" generates a plot of altitude vs. plasma frequency (in MHz) for the given coordinates.

"gnuplot plot_HvE_mar3.p" generates a plot of altitude vs. N (in m^-3) with labels for NMF2, etc. for March 3rd, 2021, 1100 UTC.

"gnuplot plot_HvE_mar4.p" generates a plot of altitude vs. N (in m^-3) with labels for NMF2, etc. for March 4th, 2021, 2300 UTC.
