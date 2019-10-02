#!/bin/bash

echo "###############################################################################"
echo "# ___     __________  ____ _______      _____ _______________.___.  ___       #"
echo "# / _ \_/\ \______   \/_   |\      \    /  _  \\______   \__  |   | / _ \_/\  #"
echo "# \/ \___/  |    |  _/ |   |/   |   \  /  /_\  \|       _//   |   | \/ \___/  #"
echo "#           |    |   \ |   /    |    \/    |    \    |   \\____   |           #"
echo "#           |______  / |___\____|__  /\____|__  /____|_  // ______|           #"
echo "#                  \/              \/         \/       \/ \/                  #"
echo "###############################################################################"

#########################################
###############UPDATING##################
#########################################

echo "Updating Your Shit"
yum update -y;
mkdir p2p

#########################################
#############DEPENDENCIES################
#########################################

echo "Setting Up The Dependencies For Your Standard P2P"
yum install perl -y; yum install gcc -y; yum install gcc-c++ -y; yum install cpan -y; yum install httpd -y; yum install tftp -y; yum install screen -y; yum install nano -y; yum install unzip -y; yum install tar -y; yum install wget; yum install curl;yum install busybox

#########################################
################ULIMIT###################
#########################################

echo "Fixxing The Ulimit"
ulimit -n 999999; ulimit -u 999999
sysctl -w fs.file-max=100000
echo "Done, Now Just Upload The Other Files"