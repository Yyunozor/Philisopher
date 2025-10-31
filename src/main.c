#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    t_table table;

    if (parse_arguments(&table, argc, argv) != 0)
    {
        fprintf(stderr, "Error\n");
        return (1);
    }
    if (init_table(&table) != 0)
    {
        destroy_table(&table);
        fprintf(stderr, "Error\n");
        return (1);
    }
    if (launch_threads(&table) != 0)
    {
        destroy_table(&table);
        fprintf(stderr, "Error\n");
        return (1);
    }
    destroy_table(&table);
    return (0);
}
