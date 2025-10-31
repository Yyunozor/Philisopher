#include "philo.h"
#include <stdlib.h>

static void cleanup_partial(t_table *table, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        pthread_mutex_destroy(&table->philos[i].fork);
        pthread_mutex_destroy(&table->philos[i].meal_mutex);
        i++;
    }
}

int init_table(t_table *table)
{
    int i;

    table->philos = calloc(table->philo_count, sizeof(t_philo));
    if (!table->philos)
        return (1);
    if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
    {
        free(table->philos);
        table->philos = NULL;
        return (1);
    }
    if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
    {
        pthread_mutex_destroy(&table->stop_mutex);
        free(table->philos);
        table->philos = NULL;
        return (1);
    }
    i = 0;
    while (i < table->philo_count)
    {
        if (pthread_mutex_init(&table->philos[i].fork, NULL) != 0
            || pthread_mutex_init(&table->philos[i].meal_mutex, NULL) != 0)
        {
            cleanup_partial(table, i);
            pthread_mutex_destroy(&table->print_mutex);
            pthread_mutex_destroy(&table->stop_mutex);
            free(table->philos);
            table->philos = NULL;
            return (1);
        }
        table->philos[i].id = i + 1;
        table->philos[i].table = table;
        table->philos[i].last_meal = 0;
        table->philos[i].meals_eaten = 0;
        table->philos[i].right_fork = &table->philos[i].fork;
        if (table->philo_count == 1)
            table->philos[i].left_fork = &table->philos[i].fork;
        else
            table->philos[i].left_fork = &table->philos[(i + 1) % table->philo_count].fork;
        i++;
    }
    return (0);
}

void destroy_table(t_table *table)
{
    int i;

    if (!table->philos)
        return ;
    i = 0;
    while (i < table->philo_count)
    {
        pthread_mutex_destroy(&table->philos[i].fork);
        pthread_mutex_destroy(&table->philos[i].meal_mutex);
        i++;
    }
    pthread_mutex_destroy(&table->stop_mutex);
    pthread_mutex_destroy(&table->print_mutex);
    free(table->philos);
    table->philos = NULL;
}
