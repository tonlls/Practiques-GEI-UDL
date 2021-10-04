#!/bin/bash

printf '|%10s  |  %10s  |  %10s  |  %11s%%  |\n' "CPU 1min" "CPU 5min" "CPU 15 min" "Busy Memory"
while true; do
	avg_load=($(cat /proc/loadavg))
	memory=($(cat /proc/meminfo))
	total_mem=${memory[1]} 
	active_mem=${memory[19]}
	avg_procs=$((( ${active_mem} *100 )/${total_mem}))
	printf '|%10s  |  %10s  |  %10s  |  %11s%%  |\n' "${avg_load[0]}" "${avg_load[1]}" "${avg_load[2]}" "$avg_procs"
	# echo "CPU (avg processes) 1m: ${AverageProcessorLoad[0]}"
	# echo "CPU (avg processes) 5m: ${AverageProcessorLoad[1]}"
	# echo "CPU (avg processes) 15m: ${AverageProcessorLoad[2]}"
	# echo "BUSY MEMORY %: ${AverageExecutionProcesses}"
	# echo ""
	sleep 1
done