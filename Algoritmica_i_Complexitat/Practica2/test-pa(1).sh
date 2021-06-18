#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo usage: $0 "<"aqueducte python script">"
    exit
fi

for len in `seq 5 20`; do
  for i in `seq 10`; do
    python3 $1 test$len-$i.in > output.ans
    if ! cmp output.ans test$len-$i.pa.ans
    then 
       echo KO
    fi
  done
done
