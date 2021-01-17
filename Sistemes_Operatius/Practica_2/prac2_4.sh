#!/bin/bash
# ----------------------------------------------------------------------
# PRA2: Guions bash
# Codi font: prac2_4.sh
#
# Eduard Sales Jové
# Ton Llucià Senserrich.
# ----------------------------------------------------------------------

#funció que tradueix un enter a binari
binari () {
	local n
	#vuidem la variable bit perque no contingui basura anterior
	bit=
	for (( n=$1 ; n>0 ; n >>= 1 )); do
		bit="$(( n&1 ))$bit"
	done
}


# comprovem que el nomre de parametres i els parametres son correctes
if [ $# -ne 1 ] || [ $1 -lt 0 ] ;then 
	echo "Us: {$0} <nombre no negatiu>"
	exit 1
fi

fval=0
#fem un bucle mentre no introduim un valor final valid
while : ; do
	read -p "Valor final? :" fval
	if [ $fval -gt $1 ]; then
		break
	fi
	echo "ERROR: valor final ha de ser > "$1
done

# fem un bucle per cada valor entre l'inicial i el final i fem un echo per a cada un
for (( n=$1 ; n<=$fval ; n++ )); do
	binari "$n"
	echo "$n(d = $bit(b"
done