#!/bin/bash
# ----------------------------------------------------------------------
# PRA2: Guions bash
# Codi font: prac2_4.sh
#
# Ton Llucià Senserrich.
# Nom complet autor2.
# ----------------------------------------------------------------------

binari () {
	local n bit
	for (( n=$1 ; n>0 ; n >>= 1 )); do
		bit="$(( n&1 ))$bit"
	done
	return "$bit"
}
if [ "$#" -ne 1 ] || [ "$1" -lt 0 ] ;then 
	echo "Us: {$0} <nombre no negatiu>"
	exit 1
fi
fval=0
while : ; do
	read -p "Valor final? :" fval
	if [ "$fval" -gt "$1" ]; then
		break
	fi
	echo "ERROR: valor final ha de ser > "$1
done
for (( n=$1 ; n<=$fval ; n++ )); do
	binari "$n"
	echo "$n(d = $?(b"
done