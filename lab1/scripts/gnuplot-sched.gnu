#!/usr/bin/gnuplot --persist
set key autotitle columnhead
plot 'data/schedulepolicy-data.csv' using 1:2 with linespoints pointsize 1 pointtype 7 lt 1, \
'data/schedulepolicy-data2.csv' using 1:2 with linespoints pointsize 1 pointtype 7 lt 2
