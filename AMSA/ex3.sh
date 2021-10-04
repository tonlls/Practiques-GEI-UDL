#!/bin/bash
# user="$(ps -u $user)"
if [ "$#" -eq 0 ]; then
	user=$USER
elif [ "$#" -eq 1 ]; then
	user=$1
fi
for pid in $(ps -u $username -f | awk 'NR>1 {print $2}' | head -n -4 ); do
    virt=$(cat /proc/$pid/statm | awk '{print $1}' )
    if [ $virt -gt 512 ]; then
        echo "$pid"
    fi
done

read input
kill $input
