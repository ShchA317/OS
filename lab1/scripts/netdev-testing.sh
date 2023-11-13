#!/bin/sh
for i in {1..16..1}; do
    echo "run with netlink-task=$i"
    a=`stress-ng --netdev $i --metrics --timeout 2`
    echo "${a}"
done

