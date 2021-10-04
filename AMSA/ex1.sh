#!/bin/sh

if [ "$#" -eq 0 ]; then
	printf '|%10s  |  %14s  |  %15s  |  %16s  |\n' "PID" "Fitxers Oberts" "Memoria Virtual" "Memoria Resident"
	for pid in $( ps -f | awk 'NR>1 {print $2}' | head -n -4); do 
		c=0
		for file in ls -la /proc/$pid/fd; do
			c=$((c+1))
		done
		v=$(cat /proc/$pid/statm | awk '{print $1}' )
		r=$(cat /proc/$pid/statm | awk '{print $2}' )
		printf '|%10s  |  %14s  |  %15s  |  %16s  |\n' "$pid" "$c" "$v" "$r"
	done
elif [ "$#" -eq 1 ]; then
	echo "$(ls -la /proc/$1/fd)"
else
	echo "Illegal number of parameters"
fi