#!/bin/bash
dec2bin () {
	local n bits=0
	bit=
	for (( n=$1 ; n>0 ; n >>= 1 )); do
		bit="$(( n&1 ))$bit"
		((bits++))
	done
	return $bits
}

if [ $1 -lt 0 ] || [ $1 -gt 100 ] ;then 
	echo "Us: {$0} <nombre no negatiu>"
	exit 1
fi
if [ $# -gt 1 ] ;then
	echo "AVIS: nomes s'utilitzarà el primer parametre"
fi
for (( n=0 ; n<=$1 ; n++ )); do
	dec2bin "$n"
	echo "$n(d = $bit(b -> $? bits"
done

