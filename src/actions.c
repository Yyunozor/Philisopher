/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:03:51 by anpayot           #+#    #+#             */
/*   Updated: 2025/10/31 15:07:06 by anpayot          ###   ########.fr       */
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
	if (philo->left_fork == philo->right_fork)
	{
		precise_sleep(philo->table->time_to_die, philo->table);
		return ;
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(philo, "is eating");
	precise_sleep(philo->table->time_to_eat, philo->table);
	drop_forks(philo);
}

void	philo_sleep_and_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	precise_sleep(philo->table->time_to_sleep, philo->table);
	print_action(philo, "is thinking");
}
