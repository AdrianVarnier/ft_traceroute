#include "ft_traceroute.h"

extern t_data data;

static void    free_data(t_data *data)
{
    freeaddrinfo(data->addr);
    close(data->sock_icmp);
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