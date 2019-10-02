
zmap -p8088 -wyarn.lst -omfu.txt
ulimit -n 999999
python yarn.py mfu.txt
rm -rf mfu.txt
clear
sh yarn.sh
