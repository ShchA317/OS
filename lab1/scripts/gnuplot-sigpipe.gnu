#!/usr/bin/gnuplot --persist
set key autotitle columnhead
plot 'data/sigpipe-data.csv' using 1:2 with points pointsize 1 pointtype 7 lt 1
