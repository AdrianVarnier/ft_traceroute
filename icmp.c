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

void    set_echo_header(t_data* data, int seq)
{
    data->packet_icmp.header.type = ICMP_ECHO;
    data->packet_icmp.header.code = 0;
    data->packet_icmp.header.un.echo.id = getpid() & 0xFFFF;
    data->packet_icmp.header.un.echo.sequence = seq;
    data->packet_icmp.header.checksum = 0;
    data->packet_icmp.header.checksum = checksum(&data->packet_icmp, sizeof(data->packet_icmp));
}