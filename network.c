#include "ft_traceroute.h"

void    init_socket(t_data* data)
{
    data->udp_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    data->icmp_sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (data->icmp_sock < 0 || data->udp_sock < 0)
    {
        close(data->udp_sock);
        close(data->icmp_sock);
        exit(1);
    }
}