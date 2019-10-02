#!/bin/bash

echo -e "\x1b[31m###############################################################################"
echo -e "\x1b[31m# ___     __________  ____ _______      _____ _______________.___.  ___       #"
echo -e "\x1b[31m# / _ \_/\ \______   \/_   |\      \    /  _  \\______   \__  |   | / _ \_/\  #"
echo -e "\x1b[31m# \/ \___/  |    |  _/ |   |/   |   \  /  /_\  \|       _//   |   | \/ \___/  #"
echo -e "\x1b[31m#           |    |   \ |   /    |    \/    |    \    |   \\____   |           #"
echo -e "\x1b[31m#           |______  / |___\____|__  /\____|__  /____|_  // ______|           #"
echo -e "\x1b[31m#                  \/              \/         \/       \/ \/                  #"
echo -e "\x1b[31m###############################################################################"

#########################################
###############UPDATING##################
#########################################

echo -e "\x1b[31mUPDATING YOUR SHIT YOU FUCKING NIGGER!!!!!"
yum update -y;
cd;mkdir p2p

#########################################
#############DEPENDENCIES################
#########################################

echo -e "\x1b[31mSETTING UP YOUR DEPENDENCIES, DONT BE LIKE CODE, AND WAIT A DAMN MINUTE!!!!!!!!"
yum install perl -y;yum install gcc -y;yum install gcc-c++ -y;yum install cpan -y;yum install httpd -y;yum install tftp -y;yum install screen -y;yum install nano -y;yum install unzip -y;yum install tar -y;yum install wget -y;yum install curl -y;yum install busybox -y;yum install python-paramiko -y

#########################################
################ULIMIT###################
#########################################

echo -e "\x1b[31mDONT BE LIKE CODE, AND WAIT A DAMN MINUTE!!!!"
cd
ulimit -Hn 999999; ulimit -Sn 99999
echo -e 'ulimit -s 999999; ulimit -n 999999; ulimit -u 999999\n' > ~/.bashrc
ulimit -s 999999; ulimit -n 999999; ulimit -u 999999
sysctl -w fs.file-max=999999 >/dev/null
echo -e '\x1b[31m~B1NARY~ IS A LAZY FUCKING NIGGER!!!!!!'