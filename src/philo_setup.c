/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:05:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/10/31 14:59:35 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_partial(t_table *table, int count)
{
	int	index;

	index = 0;
	while (index < count)
	{
		pthread_mutex_destroy(&table->philos[index].fork);
		pthread_mutex_destroy(&table->philos[index].meal_mutex);
		index++;
	}
}

static void	assign_forks(t_table *table, int index)
{
	table->philos[index].right_fork = &table->philos[index].fork;
	if (table->philo_count == 1)
		table->philos[index].left_fork = &table->philos[index].fork;
	else
		table->philos[index].left_fork
			= &table->philos[(index + 1) % table->philo_count].fork;
}

static int	init_philo_mutexes(t_table *table, int index)
{
	if (pthread_mutex_init(&table->philos[index].fork, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->philos[index].meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&table->philos[index].fork);
		return (1);
	}
	return (0);
}

int	setup_philosophers(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->philo_count)
	{
		if (init_philo_mutexes(table, index) != 0)
		{
			destroy_partial(table, index);
			return (1);
		}
		table->philos[index].id = index + 1;
		table->philos[index].table = table;
		table->philos[index].last_meal = 0;
		table->philos[index].meals_eaten = 0;
		assign_forks(table, index);
		index++;
	}
	return (0);
}
