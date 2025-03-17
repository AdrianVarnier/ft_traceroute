#include "ft_traceroute.h"

t_data data;

void    init_data(t_data* data)
{
    memset(data, 0, sizeof(t_data));
}

int main(int argc, char** argv)
{
    parse(argc, argv);
    init_data(&data);
    init_socket(&data);
    return 0;
}