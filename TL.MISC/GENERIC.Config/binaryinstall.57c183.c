/*
Skype: b1narythag0d
XMPP: b1nary@nigge.rs
Usage: gcc install.c -o install
Description: Installs Your Basic, and Scanning Dependencies, and changes the ulimit.
Made Date: 6-24-16
*/
/*

# ___     __________  ____ _______      _____ _______________.___.  ___
# / _ \_/\ \______   \/_   |\      \    /  _  \\______   \__  |   | / _ \_/\
# \/ \___/  |    |  _/ |   |/   |   \  /  /_\  \|       _//   |   | \/ \___/
#           |    |   \ |   /    |    \/    |    \    |   \\____   |
#           |______  / |___\____|__  /\____|__  /____|_  // ______|
#                  \/              \/         \/       \/ \/

						*** INSTALL.C ***
*/
#include <stdio.h>
#include <stdlib.h>
int main() {
	goto Credz;
		Credz:
			printf("\x1b[31mCreated By ~B1NARY~\n");
			printf("\x1b[31mSkype: b1narythag0d\n");
			printf("\x1b[31mXMPP: b1nary@nigge.rs\n");
	goto Update;
		Update:
			printf("\x1b[34mUpdating Yum\n");
			system("yum update -y");
			system("apt-get update -y");
	goto Dependencies;
		Dependencies:
			printf("\x1b[34mInstalling Basic Dependencies\n");
			system("yum install perl -y");
			system("yum install gcc -y");
			system("yum install gcc-c++ -y");
			system("yum install cpan -y");
			system("yum install httpd -y");
			system("yum install tftp -y");
			system("yum install screen -y");
			system("yum install nano -y");
			system("yum install unzip -y");
			system("yum install tar -y");
			system("yum install wget -y");
			system("yum install curl -y");
			system("yum install busybox -y");
			system("yum install python-paramiko -y");
	goto LRAB;
		LRAB:
			printf("\x1b[34mInstalling LRAB Dependencies\n");
			system("yum install cpan wget curl glibc.i686 -y");
			system("cpan force install Parallel::ForkManager");
			system("cpan force install IO::Socket");
			system("cpan force install IO::Select");
			system("yum install gcc php-devel php-pear libssh2 libssh2-devel libpcap -y");
			system("pecl install -f ssh2");
			system("touch /etc/php.d/ssh2.ini");
			system("echo extension=ssh2.so > /etc/php.d/ssh2.ini");
			system("cpan force install Net::SSH2");
	goto Python_Scanner;
		Python_Scanner:
			printf("\x1b[34mInstalling Python Scanners Dependencies\n");
			system("yum install python-paramiko -y");
			system("apt-get install python2.6-dev");
			system("apt-get install python-paramkio");
	goto Ulimit;
		Ulimit:
			printf("\x1b[34mChanging The Ulimit\n");
			system("ulimit -Hn 999999; ulimit -Sn 99999");
			system("ulimit -s 999999; ulimit -n 999999; ulimit -u 999999");
			system("echo -e 'ulimit -s 999999; ulimit -n 999999; ulimit -u 999999\n' > ~/.bashrc");
			system("sysctl -w fs.file-max=999999 >/dev/null");
	return 0;
}