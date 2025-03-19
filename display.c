/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:19:25 by avarnier          #+#    #+#             */
/*   Updated: 2025/03/19 09:19:25 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void    display_help()
{
    printf("Usage:\n");
    printf("\tft_traceroute [options] host\n");
    printf("\n");
    printf("Options:\n");
    printf("\t--help\t\tRead this help and exit\n");
    printf("\t-I\t\tUse ICMP ECHO for probes\n");
    printf("\t-f first_ttl\tSpecifies with what TTL to start. Defaults to 1.\n");
    printf("\t-m max_ttl\tSpecifies the maximum number of hops (max time-to-live value) traceroute will probe. The default is 30.\n");
    printf("\t-w waittime\tSet the time (in seconds) to wait for a response to a probe (default 5.0 sec).\n");
    printf("\t-q nqueries\tSets the number of probe packets per hop. The default is 3.\n");
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
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &data->response.addr.sin_addr, ip_str, sizeof(ip_str));
    if (strcmp(data->response.last_addr, ip_str) != 0)
    {
        printf("%s  ", ip_str);
        strcpy(data->response.last_addr, ip_str);
    }
    printf("%.3f ms  ", (data->response.end.tv_sec - data->response.start.tv_sec) * 1000.0
        + (data->response.end.tv_usec - data->response.start.tv_usec) / 1000.0);
}