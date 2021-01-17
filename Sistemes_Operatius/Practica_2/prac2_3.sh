#!/bin/bash
# ----------------------------------------------------------------------
# PRA2: Guions bash
# Codi font: prac2_3.sh
#
# Eduard Sales Jové
# Ton Llucià Senserrich.
# ----------------------------------------------------------------------

# fiquem a la variable dir la direccio de la carpeta on es troben els scripts d'arrancada del nivell introduit
dir="/etc/rc$1.d/"

# comprovem que el nombre de parametres es correcte
if [ $# -ne 1 ] ;then 
	echo "Us: {$0} <nivell_arrencada>"
	exit 1
fi

# comprovem si existeix el directori corresponent al nivell d'arrencada introduit per parametre
if [ ! -d $dir ] ;then
	echo "El nivell d'arrancada {$1} no existeix o no té el directori a {$dir}"
	exit 1
fi

# obtenim el nombre d'scripts que comencen amb S, es a dir que son scripts d'inici
start=$(ls "$dir"S* 2>/dev/null | wc -l)
# obtenim el nombre d'scripts que comencen amb K, es a dir que que son scripts d'aturada
end=$(ls "$dir"K* 2>/dev/null | wc -l )
echo "El nivell {$1} té {$start} serveis per iniciar i {$end} per aturar"