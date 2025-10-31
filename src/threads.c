/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpt-5-codex <gpt-5-c@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:00:00 by gpt-5-cod         #+#    #+#             */
/*   Updated: 2024/07/24 00:00:00 by gpt-5-cod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_created(t_table *table, int count)
{
	int	index;

	index = 0;
	while (index < count)
	{
		pthread_join(table->philos[index].thread, NULL);
		index++;
	}
}

int	launch_threads(t_table *table)
{
	int	index;

	table->start_time = current_time_ms();
	index = 0;
	while (index < table->philo_count)
	{
		pthread_mutex_lock(&table->philos[index].meal_mutex);
		table->philos[index].last_meal = table->start_time;
		pthread_mutex_unlock(&table->philos[index].meal_mutex);
		if (pthread_create(&table->philos[index].thread, NULL,
			philo_routine, &table->philos[index]) != 0)
		{
			stop_simulation(table);
			join_created(table, index);
			return (1);
		}
		index++;
	}
	if (pthread_create(&table->monitor, NULL, monitor_routine, table) != 0)
	{
		stop_simulation(table);
		join_created(table, table->philo_count);
		return (1);
	}
	join_created(table, table->philo_count);
	pthread_join(table->monitor, NULL);
	return (0);
}
