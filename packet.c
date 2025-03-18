#include "ft_traceroute.h"

static uint16_t checksum(void *ptr, int len)
{
    uint16_t* data = ptr;
    uint32_t sum = 0;
    for (; len > 1; len -= 2)
        sum += *data++;
    if (len == 1)
        sum += *(uint8_t*)data;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return ~sum;
}

void    set_icmp_header(t_data* data, int seq)
{
    data->packet_icmp.header.type = ICMP_ECHO;
    data->packet_icmp.header.code = 0;
    data->packet_icmp.header.un.echo.id = getpid() & 0xFFFF;
    data->packet_icmp.header.un.echo.sequence = seq;
    data->packet_icmp.header.checksum = 0;
    data->packet_icmp.header.checksum = checksum(&data->packet_icmp, sizeof(data->packet_icmp));
}

void    set_ip_header(t_data* data, int seq, int ttl)
{
    data->packet_udp.header_ip.version = 4;
    data->packet_udp.header_ip.ihl = 5;
    data->packet_udp.header_ip.tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + 32);
    data->packet_udp.header_ip.id = htonl(seq);
    data->packet_udp.header_ip.ttl = ttl;
    data->packet_udp.header_ip.protocol = IPPROTO_UDP;
    data->packet_udp.header_ip.saddr = inet_addr("127.0.0.1");
    data->packet_udp.header_ip.daddr = ((struct sockaddr_in *)data->addr->ai_addr)->sin_addr.s_addr;
    data->packet_udp.header_ip.check = 0;
    data->packet_udp.header_ip.check = checksum((unsigned short *)&data->packet_udp.header_ip, sizeof(struct iphdr));
}

void    set_udp_header(t_data* data)
{
    t_pseudo_udp_header pseudo_header;

    data->packet_udp.header_udp.source = htons(12345);
    data->packet_udp.header_udp.dest = ((struct sockaddr_in *)data->addr->ai_addr)->sin_port;
    data->packet_udp.header_udp.len = htons(sizeof(struct udphdr) + 32);
    data->packet_udp.header_udp.check = 0;
    memcpy(&pseudo_header.header_udp, &data->packet_udp, sizeof(struct udphdr));

    pseudo_header.source_address = inet_addr("127.0.0.1");
    pseudo_header.dest_address = ((struct sockaddr_in *)data->addr->ai_addr)->sin_addr.s_addr;
    pseudo_header.placeholder = 0;
    pseudo_header.protocol = IPPROTO_UDP;
    pseudo_header.udp_length = htons(sizeof(struct udphdr) + 32);

    data->packet_udp.header_udp.check = checksum(&pseudo_header, sizeof(t_pseudo_udp_header));
}