#!/bin/sh
for i in {1..9..1}; do
    echo "run with zlib-mem-level=$i"
    a=`stress-ng --zlib 1 --zlib-mem-level $i --metrics --timeout 10`
    echo "$a"
done
