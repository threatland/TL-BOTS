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
##################BASIC##################
#########################################
yum update;
yum install gcc -y;
yum install gcc-c++ -y;
yum install cpan -y;
yum install wget -y;
yum install curl -y;
yum install perl -y;
yum install unzip -y;
yum install nano -y

#########################################
################SCANNING#################
#########################################

echo -e "\e[1;35mSetting Up Your Scanning Shit For LRAB"
yum install cpan wget curl glibc.i686 -y
cpan force install Parallel::ForkManager
cpan force install IO::Socket
cpan force install IO::Select
sleep 2
yum install gcc php-devel php-pear libssh2 libssh2-devel libpcap -y
pecl install -f ssh2
touch /etc/php.d/ssh2.ini
echo extension=ssh2.so > /etc/php.d/ssh2.ini
cpan force install Net::SSH2
sleep 2
echo "Setting Up Your Scanning Shit For Python Scanners"
yum install python-paramiko -y