/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:19:28 by avarnier          #+#    #+#             */
/*   Updated: 2025/03/19 09:19:29 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

extern t_data data;

static void    free_data(t_data *data)
{
    freeaddrinfo(data->addr);
    close(data->sock_icmp);
    close(data->sock_udp);
}

void    exit_clean(int n)
{
    free_data(&data);
    exit(n);
}

void handle_sigint(int sig)
{
    (void)sig;
    exit_clean(0);
}