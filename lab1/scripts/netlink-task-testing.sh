#!/bin/sh
for i in {1..16..1}; do
    echo "run with netlink-task=$i"
    a=`stress-ng --netlink-task $i --metrics --timeout 2`
    echo "${a}"
done

