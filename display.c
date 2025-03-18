#include "ft_traceroute.h"

void    display_help()
{
    printf("Usage:\n");
    printf("\tft_traceroute host\n");
    printf("\n");
    printf("Options:\n");
    printf("\t--help:\t\tRead this help and exit\n");
    printf("\n");
    printf("Arguments:\n");
    printf("\thost:\t\tThe host to traceroute to\n");
}

void    display_traceroute_info(t_data* data)
{
    char ip_str[INET_ADDRSTRLEN];
    
    inet_ntop(AF_INET, &((struct sockaddr_in *)data->addr->ai_addr)->sin_addr, ip_str, sizeof(ip_str));
    printf("traceroute to %s, %d hops max, 60 byte packets\n", ip_str, data->max_hop);
}

void    display_hop_info(t_data* data)
{
    if (!data->response.is_addr_displayed)
    {
        char ip_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &data->response.addr.sin_addr, ip_str, sizeof(ip_str));
        printf("%s  ", ip_str);
        data->response.is_addr_displayed = 1;
    }
    printf("%.3f ms  ", (data->response.end.tv_sec - data->response.start.tv_sec) * 1000.0
        + (data->response.end.tv_usec - data->response.start.tv_usec) / 1000.0);
}