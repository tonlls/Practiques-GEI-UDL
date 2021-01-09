#!/bin/bash
# ----------------------------------------------------------------------
# PRA2: Guions bash
# Codi font: prac2_3.sh
#
# Ton Llucià Senserrich.
# Nom complet autor2.
# ----------------------------------------------------------------------

dir="/etc/rc$1.d/"
if [ "$#" -ne 1 ] ;then 
	echo "Us: {$0} <nivell_arrencada>"
	exit 1
fi
if [ ! -d "$dir" ] ;then
	echo "El nivell d'arrancada {$1} no existeix o no té el directori a {$dir}"
	exit 1
fi
start=$(ls -1q "$dir"S* 2>/dev/null | wc -l)
end=$(ls -1q "$dir"K* 2>/dev/null | wc -l )
echo "El nivell {$1} té {$start} serveis per iniciar i {$end} per aturar"
#ls -1q /directory/data* | wc -l