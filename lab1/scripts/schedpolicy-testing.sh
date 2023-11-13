#!/bin/sh
for i in {1..16..1}; do
    a=`stress-ng --hdd 1 --schedpolicy 2 --metrics --timeout 5 | awk '/ hdd /{print}' | tail -n 2 | head -n 1 | awk '{print $5}'`
    echo "${i}, ${a}" >> data/schedulepolicy-data2.csv
done

