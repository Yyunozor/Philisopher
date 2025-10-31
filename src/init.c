/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:18:59 by anpayot           #+#    #+#             */
/*   Updated: 2025/10/31 14:59:35 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

static int	init_global_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&table->stop_mutex);
		return (1);
	}
	if (pthread_mutex_init(&table->seat_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&table->print_mutex);
		pthread_mutex_destroy(&table->stop_mutex);
		return (1);
	}
	return (0);
}

int	init_table(t_table *table)
{
	table->philos = malloc(table->philo_count * sizeof(t_philo));
	if (table->philos == NULL)
		return (1);
	memset(table->philos, 0, table->philo_count * sizeof(t_philo));
	if (init_global_mutexes(table) != 0)
	{
		free(table->philos);
		table->philos = NULL;
		return (1);
	}
	if (setup_philosophers(table) != 0)
	{
		pthread_mutex_destroy(&table->seat_mutex);
		pthread_mutex_destroy(&table->print_mutex);
		pthread_mutex_destroy(&table->stop_mutex);
		free(table->philos);
		table->philos = NULL;
		return (1);
	}
	if (table->philo_count % 2 == 0)
		table->seat_capacity = table->philo_count;
	else
		table->seat_capacity = table->philo_count / 2;
	if (table->seat_capacity <= 0)
		table->seat_capacity = 1;
	table->available_seats = table->seat_capacity;
	return (0);
}

void	destroy_table(t_table *table)
{
	int	index;

	if (table->philos == NULL)
		return ;
	index = 0;
	while (index < table->philo_count)
	{
		pthread_mutex_destroy(&table->philos[index].fork);
		pthread_mutex_destroy(&table->philos[index].meal_mutex);
		index++;
	}
	pthread_mutex_destroy(&table->seat_mutex);
	pthread_mutex_destroy(&table->stop_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->philos);
	table->philos = NULL;
}
