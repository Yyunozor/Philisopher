#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static bool all_philos_ate(t_table *table)
{
	int i;
	int satisfied;

	if (table->meals_required <= 0)
		return (false);
	satisfied = 0;
	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		if (table->philos[i].meals_eaten >= table->meals_required)
			satisfied++;
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		i++;
	}
	return (satisfied == table->philo_count);
}

static bool check_death(t_table *table)
{
	int     i;
	long    now;

	now = current_time_ms();
	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		if (now - table->philos[i].last_meal >= table->time_to_die)
		{
			pthread_mutex_unlock(&table->philos[i].meal_mutex);
			pthread_mutex_lock(&table->print_mutex);
			if (!simulation_stopped(table))
				printf("%ld %d died\n", elapsed_since(table->start_time),
					table->philos[i].id);
			pthread_mutex_unlock(&table->print_mutex);
			stop_simulation(table);
			return (true);
		}
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		i++;
	}
	return (false);
}

void *monitor_routine(void *arg)
{
	t_table *table;

	table = (t_table *)arg;
	while (!simulation_stopped(table))
	{
		if (check_death(table))
			break ;
		if (all_philos_ate(table))
		{
			stop_simulation(table);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}
