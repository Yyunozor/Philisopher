#include "philo.h"
#include <unistd.h>

static void take_forks(t_philo *philo)
{
    pthread_mutex_t *first;
    pthread_mutex_t *second;

    if (philo->id % 2 == 0)
    {
        first = philo->right_fork;
        second = philo->left_fork;
    }
    else
    {
        first = philo->left_fork;
        second = philo->right_fork;
    }
    pthread_mutex_lock(first);
    print_action(philo, "has taken a fork");
    if (first == second)
        return ;
    pthread_mutex_lock(second);
    print_action(philo, "has taken a fork");
}

static void release_forks(t_philo *philo)
{
    if (philo->left_fork == philo->right_fork)
    {
        pthread_mutex_unlock(philo->left_fork);
        return ;
    }
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

static void eat(t_philo *philo)
{
    long    start;

    if (philo->left_fork == philo->right_fork)
    {
        precise_sleep(philo->table->time_to_die, philo->table);
        return ;
    }
    start = current_time_ms();
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = start;
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_mutex);
    print_action(philo, "is eating");
    precise_sleep(philo->table->time_to_eat, philo->table);
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = start + philo->table->time_to_eat;
    pthread_mutex_unlock(&philo->meal_mutex);
    release_forks(philo);
}

static void philo_sleep_and_think(t_philo *philo)
{
    print_action(philo, "is sleeping");
    precise_sleep(philo->table->time_to_sleep, philo->table);
    print_action(philo, "is thinking");
    if (philo->table->philo_count % 2 == 1)
    {
        long    buffer;
        long    delay;

        buffer = philo->table->time_to_die
            - (philo->table->time_to_eat + philo->table->time_to_sleep);
        if (buffer > 0)
        {
            delay = buffer / 2;
            if (delay <= 0)
                delay = 1;
            precise_sleep(delay, philo->table);
        }
    }
}

static void stagger_start(t_philo *philo)
{
    long    delay;

    if (philo->table->philo_count == 1)
        return ;
    delay = 0;
    if (philo->table->philo_count % 2 == 0)
    {
        if (philo->id % 2 == 0)
            delay = philo->table->time_to_eat / 2;
    }
    else if (philo->id % 2 == 0)
        delay = philo->table->time_to_eat / 2;
    if (delay > 0)
        precise_sleep(delay, philo->table);
}

static void join_philos(t_table *table, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        pthread_join(table->philos[i].thread, NULL);
        i++;
    }
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->table->philo_count == 1)
    {
        take_forks(philo);
        precise_sleep(philo->table->time_to_die, philo->table);
        if (philo->left_fork == philo->right_fork)
            pthread_mutex_unlock(philo->left_fork);
        return (NULL);
    }
    stagger_start(philo);
    while (!simulation_stopped(philo->table))
    {
        take_forks(philo);
        eat(philo);
        if (simulation_stopped(philo->table))
            break ;
        philo_sleep_and_think(philo);
    }
    return (NULL);
}

int launch_threads(t_table *table)
{
    int i;

    table->start_time = current_time_ms();
    i = 0;
    while (i < table->philo_count)
    {
        pthread_mutex_lock(&table->philos[i].meal_mutex);
        table->philos[i].last_meal = table->start_time;
        pthread_mutex_unlock(&table->philos[i].meal_mutex);
        if (pthread_create(&table->philos[i].thread, NULL, philo_routine,
                &table->philos[i]) != 0)
        {
            stop_simulation(table);
            join_philos(table, i);
            return (1);
        }
        i++;
    }
    if (pthread_create(&table->monitor, NULL, monitor_routine, table) != 0)
    {
        stop_simulation(table);
        join_philos(table, table->philo_count);
        return (1);
    }
    join_philos(table, table->philo_count);
    pthread_join(table->monitor, NULL);
    return (0);
}
