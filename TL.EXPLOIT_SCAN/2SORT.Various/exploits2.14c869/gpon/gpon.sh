#!/bin/bash
#!Created By Swizz
#!Just start the scanner and go to the movies =)
clear
echo -e "\e[1;32mNow Auto-Scanning GPON"
zmap -p443 -wg.lst -og.txt
ulimit -n 999999
python gloader.py g.txt
rm -rf g.txt
clear
sh gpon.sh
