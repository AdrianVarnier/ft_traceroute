/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:19:43 by avarnier          #+#    #+#             */
/*   Updated: 2025/03/19 09:19:44 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void    init_socket(t_data* data)
{
    data->sock_icmp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    data->sock_udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 
    if (data->sock_icmp < 0 || data->sock_udp < 0)
        exit_clean(1);
    setsockopt(data->sock_icmp, SOL_SOCKET, SO_RCVTIMEO, &data->timeout, sizeof(data->timeout));
}

static void    set_hints_icmp(struct addrinfo* hints)
{
    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_protocol = IPPROTO_ICMP;
}

int     resolve_address(t_data* data, char* addr)
{
    struct addrinfo hints;
    set_hints_icmp(&hints);
    if (getaddrinfo(addr, NULL, &hints, &data->addr) != 0)
    {
        fprintf(stderr, "%s: Temporary failure in name resolution\n", addr);
        fprintf(stderr, "Cannot handle \"host\" cmdline arg `%s'\n", addr);
        exit(1);
    }
    return 0;
}