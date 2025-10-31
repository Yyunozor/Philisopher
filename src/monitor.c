/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpt-5-codex <gpt-5-c@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:00:00 by gpt-5-cod         #+#    #+#             */
/*   Updated: 2024/07/24 00:00:00 by gpt-5-cod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static bool	all_philos_ate(t_table *table)
{
	int	index;
	int	satisfied;

	if (table->meals_required <= 0)
		return (false);
	satisfied = 0;
	index = 0;
	while (index < table->philo_count)
	{
		pthread_mutex_lock(&table->philos[index].meal_mutex);
		if (table->philos[index].meals_eaten >= table->meals_required)
			satisfied++;
		pthread_mutex_unlock(&table->philos[index].meal_mutex);
		index++;
	}
	return (satisfied == table->philo_count);
}

static bool	announce_death(t_table *table, int index)
{
	pthread_mutex_unlock(&table->philos[index].meal_mutex);
	pthread_mutex_lock(&table->print_mutex);
	if (!simulation_stopped(table))
		printf("%ld %d died\n", elapsed_since(table->start_time),
			table->philos[index].id);
	pthread_mutex_unlock(&table->print_mutex);
	stop_simulation(table);
	return (true);
}

static bool	check_death(t_table *table)
{
	int	index;
	long	now;

	now = current_time_ms();
	index = 0;
	while (index < table->philo_count)
	{
		pthread_mutex_lock(&table->philos[index].meal_mutex);
		if (now - table->philos[index].last_meal >= table->time_to_die)
			return (announce_death(table, index));
		pthread_mutex_unlock(&table->philos[index].meal_mutex);
		index++;
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

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
