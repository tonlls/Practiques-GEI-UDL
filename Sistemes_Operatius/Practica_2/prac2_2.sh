#!/bin/bash

# ----------------------------------------------------------------------
# PRA2: Guions bash
# Codi font: prac2_2.sh
#
# Eduard Sales Jové
# Ton Llucià Senserrich.
# ----------------------------------------------------------------------

if [ $# -ne 2 ]
then
    echo "$0 suma els dos nombres passats com a parametres"
    echo "Ús: $0 <nombre1> <nombre2>"
    exit 1
fi
echo "$1 + $2 = `expr $1 + $2`"
echo "$1 + $2 = $(($1 + $2))"
let sum=$1+$2
echo "$1 + $2 = $sum"