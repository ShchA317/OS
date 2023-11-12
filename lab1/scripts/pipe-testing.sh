#!/bin/sh
for i in {16..10000..16}; do
    a=`stress-ng --pipe 1 --pipe-ops ${i} --metrics | awk '/pipe /{print}' | head -n 1 | awk '{print $9}'`
    echo "${i}, ${a}" >> data/pipe-data
    sleep 0.5
done





