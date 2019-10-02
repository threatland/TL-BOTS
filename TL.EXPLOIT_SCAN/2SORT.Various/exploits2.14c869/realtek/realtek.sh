#!/bin/bash
clear
echo -e "\e[1;97m[\e[1;36mOkami\e[1;97m] \e[1;36mNow Auto-Scanning Realtek"
zmap -p52869 -o jp -B100M -N 10000
ulimit -n 999999
python Realtek.py jp
rm -rf jp
clear
sh realtek.sh
