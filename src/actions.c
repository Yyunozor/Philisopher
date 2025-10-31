/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpt-5-codex <gpt-5-c@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:00:00 by gpt-5-cod         #+#    #+#             */
/*   Updated: 2024/07/24 00:00:00 by gpt-5-cod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	pthread_mutex_lock(first);
	print_action(philo, "has taken a fork");
	if (first == second)
		return ;
	pthread_mutex_lock(second);
	print_action(philo, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_eat(t_philo *philo)
{
	long	start;

	if (philo->left_fork == philo->right_fork)
	{
		precise_sleep(philo->table->time_to_die, philo->table);
		return ;
	}
	start = current_time_ms();
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = start;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(philo, "is eating");
	precise_sleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = start + philo->table->time_to_eat;
	pthread_mutex_unlock(&philo->meal_mutex);
	drop_forks(philo);
}

void	philo_sleep_and_think(t_philo *philo)
{
	long	buffer;
	long	delay;

	print_action(philo, "is sleeping");
	precise_sleep(philo->table->time_to_sleep, philo->table);
	print_action(philo, "is thinking");
	if (philo->table->philo_count % 2 == 1)
	{
		buffer = philo->table->time_to_die
			- (philo->table->time_to_eat + philo->table->time_to_sleep);
		if (buffer > 0)
		{
			delay = buffer / 2;
			if (delay <= 0)
				delay = 1;
			precise_sleep(delay, philo->table);
		}
	}
}
