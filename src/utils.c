/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/07/24 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

bool	simulation_stopped(t_table *table)
{
	bool	stopped;

	pthread_mutex_lock(&table->stop_mutex);
	stopped = table->stop;
	pthread_mutex_unlock(&table->stop_mutex);
	return (stopped);
}

void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->stop_mutex);
	table->stop = true;
	pthread_mutex_unlock(&table->stop_mutex);
}

void	print_action(t_philo *philo, const char *message)
{
	long	timestamp;

	if (simulation_stopped(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->print_mutex);
	if (!simulation_stopped(philo->table))
	{
		timestamp = elapsed_since(philo->table->start_time);
		printf("%ld %d %s\n", timestamp, philo->id, message);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
}
