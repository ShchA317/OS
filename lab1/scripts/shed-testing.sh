#!/bin/sh
for i in {1000..10000..1000}; do
    stress-ng --hdd 1 --sched-runtime ${i} --timeout 30
    sleep 30
done

