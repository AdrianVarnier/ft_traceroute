#include "ft_traceroute.h"

void    parse(int argc, char** argv)
{
    if (argc < 2)
    {
        display_help();
        exit(1);
    }
    if (!strcmp(argv[1], "--help"))
    {
        display_help();
        exit(0);
    }
}