#Python script to automatically install needed dependencies. 

import subprocess, sys, time

def run(cmd):
    subprocess.call(cmd, shell=True)

print("\x1b[0;32mYou are using Seb's auto dependency setup.\x1b[0m")

time.sleep(5)
	
run("yum install python-paramiko -y")

run("yum install nano -y")

run("yum update -y")

run("yum install gcc -y")

run("yum install httpd -y")

run("yum install cpan -y")

run("yum install vsftpd -y")

run("yum install xinetd tftp tftp-server -y")

run("yum install screen -y")

run("yum install nc -y")



print("\x1b[0;33mSucessfully setup\x1b[0m")
print("\x1b[0;32mThe dependencies\x1b[0m")
print("\x1b[0;31mNeeded to use qBot and my compiler\x1b[0m")
print("\x1b[0;30mThanks for using my auto dependency installer!\x1b[0m")
exit(1)