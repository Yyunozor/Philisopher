#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

static void    usage(void)
{
    fprintf(stderr, "Usage: philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals]\n");
}

int main(int argc, char **argv)
{
    t_table table;

    if (parse_arguments(&table, argc, argv) != 0)
    {
        usage();
        return (1);
    }
    if (init_table(&table) != 0)
    {
        destroy_table(&table);
        fprintf(stderr, "Error: initialization failed\n");
        return (1);
    }
    if (launch_threads(&table) != 0)
    {
        destroy_table(&table);
        fprintf(stderr, "Error: thread creation failed\n");
        return (1);
    }
    destroy_table(&table);
    return (0);
}
