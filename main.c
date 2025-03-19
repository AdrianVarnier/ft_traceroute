/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:19:41 by avarnier          #+#    #+#             */
/*   Updated: 2025/03/19 09:19:41 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

t_data data;

static void    init_data(t_data* data)
{
    memset(data, 0, sizeof(t_data));
    data->hop = 1;
    data->max_hop = 30;
    data->max_probe = 3;
    data->timeout.tv_sec = 5;
    data->interval = 0;
    data->response.addr_len = sizeof(data->response.addr);
}

int main(int argc, char** argv)
{
    init_data(&data);
    parse(&data, argc, argv);
    init_socket(&data);
    ft_traceroute(&data);
    signal(SIGINT, handle_sigint);
    return 0;
}