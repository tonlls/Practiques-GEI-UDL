#!/bin/bash
# Ramdisk
ROOTUSER NAME=root
MOUNTPT=/tmp/ramdisk
SIZE=2024 # 2K blocs
BLOCKSIZE=1024 # mida bloc: 1K (1024 bytes)
DEVICE=/dev/ram0 # Primer Ram Disc
username=`id -nu` # equivalent a fer username=$USER
[ "$username" != "$ROOTUSER NAME" ] && echo "no autoritzat" && exit 1
[ ! -d "$MOUNTPT" ] && mkdir $MOUNTPT
dd if=/dev/zero of=$DEVICE count=$SIZE bs=$BLOCKSIZE
/sbin/mke4fs $DEVICE # Crea un s. de fitxers ext4
# també es podria fer mkfs -t ext4 $DEVICE , o bé mkfs.ext4 $DEVICE
mount $DEVICE $MOUNTPT # el munta
chmod 777 $MOUNTPT
echo $MOUNTPT " disponible"
exit 0