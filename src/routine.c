/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/07/24 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_single_philo(t_philo *philo)
{
	take_forks(philo);
	precise_sleep(philo->table->time_to_die, philo->table);
	drop_forks(philo);
}

void	stagger_start(t_philo *philo)
{
	long	delay;

	delay = 0;
	if (philo->table->philo_count > 1 && philo->id % 2 == 0)
		delay = philo->table->time_to_eat / 2;
	if (delay > 0)
		precise_sleep(delay, philo->table);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->philo_count == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	stagger_start(philo);
	while (!simulation_stopped(philo->table))
	{
		take_forks(philo);
		philo_eat(philo);
		if (simulation_stopped(philo->table))
			break ;
		philo_sleep_and_think(philo);
	}
	return (NULL);
}
