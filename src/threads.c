/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:26:09 by anpayot           #+#    #+#             */
/*   Updated: 2025/10/31 14:59:35 by anpayot          ###   ########.fr       */
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

static int	create_philo_thread(t_table *table, int index)
{
	t_philo	*current;

	current = &table->philos[index];
	pthread_mutex_lock(&current->meal_mutex);
	current->last_meal = table->start_time;
	pthread_mutex_unlock(&current->meal_mutex);
	if (pthread_create(&current->thread, NULL, philo_routine, current) != 0)
		return (1);
	return (0);
}

static int	create_philosophers(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->philo_count)
	{
		if (create_philo_thread(table, index) != 0)
		{
			stop_simulation(table);
			join_created(table, index);
			return (1);
		}
		index++;
	}
	return (0);
}

static int	create_monitor(t_table *table)
{
	if (pthread_create(&table->monitor, NULL, monitor_routine, table) != 0)
	{
		stop_simulation(table);
		join_created(table, table->philo_count);
		return (1);
	}
	return (0);
}

int	launch_threads(t_table *table)
{
	table->start_time = current_time_ms();
	if (create_philosophers(table) != 0)
		return (1);
	if (create_monitor(table) != 0)
		return (1);
	join_created(table, table->philo_count);
	pthread_join(table->monitor, NULL);
	return (0);
}
