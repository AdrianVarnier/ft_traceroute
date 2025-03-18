#include "ft_traceroute.h"

static void ft_traceroute_icmp(t_data *data)
{
    display_traceroute_info(data);
    for (; data->hop <= data->max_hop; data->hop++)
    {
        setsockopt(data->sock_icmp, IPPROTO_IP, IP_TTL, &data->hop, sizeof(data->hop));
        printf(" %d  ", data->hop);
        for (int probe = 1; probe <= data->max_probe; probe++)
        {
            set_icmp_header(data, data->hop * data->max_probe - (data->max_probe - probe));
            gettimeofday(&data->response.start, NULL);
            if (sendto(data->sock_icmp, &data->packet_icmp, sizeof(data->packet_icmp), 0,  data->addr->ai_addr, data->addr->ai_addrlen) < 0)
                exit_clean(1);

            memset(&data->response.buffer, 0, sizeof(data->response.buffer));
            if (recvfrom(data->sock_icmp, data->response.buffer, sizeof(data->response.buffer), 0, (struct sockaddr*)&data->response.addr, &data->response.addr_len) <= 0)
            {
                printf("*  ");
                continue ;
            }
            gettimeofday(&data->response.end, NULL);
            display_hop_info(data);
        }
        printf("\n");
        if (data->response.addr.sin_addr.s_addr == ((struct sockaddr_in *)data->addr->ai_addr)->sin_addr.s_addr)
            exit_clean(0);
        data->response.is_addr_displayed = 0;
    }
}

static void ft_traceroute_udp(t_data* data)
{
    display_traceroute_info(data);
    for (; data->hop <= data->max_hop; data->hop++)
    {
        setsockopt(data->sock_icmp, IPPROTO_IP, IP_TTL, &data->hop, sizeof(data->hop));
        printf(" %d  ", data->hop);
        for (int probe = 1; probe <= data->max_probe; probe++)
        {
            set_ip_header(data, data->hop * data->max_probe - (data->max_probe - probe), data->hop);
            set_udp_header(data);
            gettimeofday(&data->response.start, NULL);
            if (sendto(data->sock_icmp, &data->packet_udp, sizeof(data->packet_udp), 0,  data->addr->ai_addr, data->addr->ai_addrlen) < 0)
                exit_clean(1);

            memset(&data->response.buffer, 0, sizeof(data->response.buffer));
            if (recvfrom(data->sock_icmp, data->response.buffer, sizeof(data->response.buffer), 0, (struct sockaddr*)&data->response.addr, &data->response.addr_len) <= 0)
            {
                printf("*  ");
                continue ;
            }
            gettimeofday(&data->response.end, NULL);
            display_hop_info(data);
        }
        printf("\n");
        if (data->response.addr.sin_addr.s_addr == ((struct sockaddr_in *)data->addr->ai_addr)->sin_addr.s_addr)
            exit_clean(0);
        data->response.is_addr_displayed = 0;
    }
}

void    ft_traceroute(t_data *data)
{
    if (data->icmp)
        ft_traceroute_icmp(data);
    ft_traceroute_udp(data);
}