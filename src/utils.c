/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:26:41 by anpayot           #+#    #+#             */
/*   Updated: 2025/10/31 16:46:49 by anpayot          ###   ########.fr       */
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
	pthread_mutex_lock(&philo->table->print_mutex);
	if (!simulation_stopped(philo->table))
		printf("%ld %d %s\n", elapsed_since(philo->table->start_time),
			philo->id, message);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
