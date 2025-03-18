#ifndef FT_TRACEROUTE_H
#define FT_TRACEROUTE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <sys/time.h>
#include <signal.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

typedef struct s_pseudo_udp_header
{
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t placeholder;
    u_int8_t protocol;
    u_int16_t udp_length;
    struct udphdr   header_udp;
    char            payload[32];
} t_pseudo_udp_header;

typedef struct s_icmp_packet
{
    struct icmphdr  header;
    char            payload[52];
} t_icmp_packet;

typedef struct s_udp_packet
{
    struct iphdr    header_ip;
    struct udphdr   header_udp;
    char            payload[32];
} t_udp_packet;

typedef struct  s_response
{
    int                 is_addr_displayed;
    char                buffer[1024];
    struct sockaddr_in  addr;
    socklen_t           addr_len;
    struct timeval      start;
    struct timeval      end;
} t_response;

typedef struct s_data
{
    int                 sock_icmp;
    int                 hop;
    int                 max_hop;
    int                 max_probe;
    int                 icmp;
    int                 interval;
    struct timeval      timeout;
    struct addrinfo*    addr;
    t_icmp_packet       packet_icmp;
    t_udp_packet        packet_udp;
    t_response          response;
}              t_data;

// display.c
void    display_help();
void    display_traceroute_info(t_data* data);
void    display_hop_info(t_data* data);

// parse.c
void    parse(t_data* data, int argc, char** argv);

// network.c
void    init_socket(t_data* data);
int     resolve_address(t_data* data, char* addr);

// exit.c
void    exit_clean(int n);
void    handle_sigint(int sig);

// packet.c
void    set_icmp_header(t_data* data, int seq);
void    set_ip_header(t_data* data, int seq, int ttl);
void    set_udp_header(t_data* data);

// ft_traceroute.c
void    ft_traceroute(t_data *data);

#endif