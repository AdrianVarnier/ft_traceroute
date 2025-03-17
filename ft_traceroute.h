#ifndef FT_TRACEROUTE_H
#define FT_TRACEROUTE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_HOPS 30
#define TIMEOUT 2
#define UDP_PORT 33434

typedef struct s_data
{
    int udp_sock;
    int icmp_sock;
}              t_data;

// display.c
void    display_help();

// parse.c
void    parse(int argc, char** argv);

// network.c
void    init_socket(t_data* data);

#endif