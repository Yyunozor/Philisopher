/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:26:15 by anpayot           #+#    #+#             */
/*   Updated: 2025/10/31 15:07:07 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	acquire_seat(t_philo *philo)
{
	while (!simulation_stopped(philo->table))
	{
		pthread_mutex_lock(&philo->table->seat_mutex);
		if (philo->table->available_seats > 0)
		{
			philo->table->available_seats--;
			pthread_mutex_unlock(&philo->table->seat_mutex);
			return (true);
		}
		pthread_mutex_unlock(&philo->table->seat_mutex);
		precise_sleep(1, philo->table);
	}
	return (false);
}

static void	release_seat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->seat_mutex);
	philo->table->available_seats++;
	if (philo->table->available_seats > philo->table->seat_capacity)
		philo->table->available_seats = philo->table->seat_capacity;
	pthread_mutex_unlock(&philo->table->seat_mutex);
}

static void	handle_single_philo(t_philo *philo)
{
	take_forks(philo);
	precise_sleep(philo->table->time_to_die, philo->table);
	drop_forks(philo);
}

static void	stagger_start(t_philo *philo)
{
	long	delay;

	if (philo->table->philo_count == 1)
		return ;
	if (philo->id % 2 == 1)
	{
		if (philo->table->philo_count % 2 == 0
			|| philo->id != philo->table->philo_count)
			return ;
		delay = philo->table->time_to_eat;
	}
	else if (philo->table->philo_count % 2 == 0)
		delay = philo->table->time_to_eat / 2;
	else if (philo->table->time_to_eat > philo->table->time_to_sleep)
		delay = philo->table->time_to_eat - philo->table->time_to_sleep;
	else
		delay = philo->table->time_to_eat / 2;
	if (delay <= 0)
		delay = 1;
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
		if (!acquire_seat(philo))
			break ;
		take_forks(philo);
		philo_eat(philo);
		release_seat(philo);
		if (simulation_stopped(philo->table))
			break ;
		philo_sleep_and_think(philo);
	}
	return (NULL);
}
