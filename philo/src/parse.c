#include "philo.h"
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

static int  parse_number(const char *str, long *out)
{
    long    result;

    if (*str == '\0')
        return (1);
    result = 0;
    while (*str)
    {
        if (!isdigit((unsigned char)*str))
            return (1);
        result = result * 10 + (*str - '0');
        if (result > INT_MAX)
            return (1);
        str++;
    }
    *out = result;
    return (0);
}

int parse_arguments(t_table *table, int argc, char **argv)
{
    long    value;

    if (argc != 5 && argc != 6)
        return (1);
    if (parse_number(argv[1], &value) || value <= 0)
        return (1);
    table->philo_count = (int)value;
    if (parse_number(argv[2], &value))
        return (1);
    table->time_to_die = value;
    if (parse_number(argv[3], &value))
        return (1);
    table->time_to_eat = value;
    if (parse_number(argv[4], &value))
        return (1);
    table->time_to_sleep = value;
    table->meals_required = -1;
    if (argc == 6)
    {
        if (parse_number(argv[5], &value))
            return (1);
        table->meals_required = (int)value;
        if (table->meals_required <= 0)
            return (1);
    }
    table->philos = NULL;
    table->stop = false;
    return (0);
}
