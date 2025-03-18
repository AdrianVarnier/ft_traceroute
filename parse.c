#include "ft_traceroute.h"

void    parse(t_data* data, int argc, char** argv)
{
    int host = 0;

    if (argc < 2)
    {
        display_help();
        exit(1);
    }
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "--help"))
        {
            display_help();
            exit_clean(0);
        }
        else if (!strcmp(argv[i], "-f") && i + 1 < argc)
            data->hop = atoi(argv[++i]);
        else if (!strcmp(argv[i], "-m") && i + 1 < argc)
            data->max_hop = atoi(argv[++i]);
        else if (!strcmp(argv[i], "-q") && i + 1 < argc)
            data->max_probe = atoi(argv[++i]);
        else if (!strcmp(argv[i], "-w") && i + 1 < argc)
            data->timeout.tv_sec = atoi(argv[++i]);
        else if (!strcmp(argv[i], "-I"))
            data->icmp = 1;
        else
        {
            resolve_address(data, argv[i]);
            host = 1;
        }
    }
    if (!host)
    {
        fprintf(stderr, "Specify \"host\" missing argument.\n");
        exit_clean(1);
    }
}