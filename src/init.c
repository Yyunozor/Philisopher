/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpt-5-codex <gpt-5-c@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:00:00 by gpt-5-cod         #+#    #+#             */
/*   Updated: 2024/07/24 00:00:00 by gpt-5-cod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	cleanup_partial(t_table *table, int count)
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

static int	init_table_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&table->stop_mutex);
		return (1);
	}
	return (0);
}

static int	init_philo(t_table *table, int index)
{
	t_philo	*philo;

	philo = &table->philos[index];
	if (pthread_mutex_init(&philo->fork, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philo->meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->fork);
		return (1);
	}
	philo->id = index + 1;
	philo->table = table;
	philo->last_meal = 0;
	philo->meals_eaten = 0;
	philo->right_fork = &table->philos[index].fork;
	if (table->philo_count == 1)
		philo->left_fork = &table->philos[index].fork;
	else
		philo->left_fork
			= &table->philos[(index + 1) % table->philo_count].fork;
	return (0);
}

int	init_table(t_table *table)
{
	int	index;

	table->philos = calloc(table->philo_count, sizeof(t_philo));
	if (!table->philos)
		return (1);
	if (init_table_mutexes(table) != 0)
	{
		free(table->philos);
		table->philos = NULL;
		return (1);
	}
	index = 0;
	while (index < table->philo_count)
	{
		if (init_philo(table, index) != 0)
		{
			cleanup_partial(table, index);
			pthread_mutex_destroy(&table->print_mutex);
			pthread_mutex_destroy(&table->stop_mutex);
			free(table->philos);
			table->philos = NULL;
			return (1);
		}
		index++;
	}
	return (0);
}

void	destroy_table(t_table *table)
{
	int	index;

	if (!table->philos)
		return ;
	index = 0;
	while (index < table->philo_count)
	{
		pthread_mutex_destroy(&table->philos[index].fork);
		pthread_mutex_destroy(&table->philos[index].meal_mutex);
		index++;
	}
	pthread_mutex_destroy(&table->stop_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->philos);
	table->philos = NULL;
}
