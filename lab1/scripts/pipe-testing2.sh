#!/bin/sh
for i in {1..16..1}; do
    a=`stress-ng --pipe 1 --sigpipe ${i} --metrics --timeout 1 | awk '/pipe /{print}' | head -n 1 | awk '{print $9}'`
    echo "${i}, ${a}" >> data/sigpipe-data.csv
done

