/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpt-5-codex <gpt-5-c@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:00:00 by gpt-5-cod         #+#    #+#             */
/*   Updated: 2024/07/24 00:00:00 by gpt-5-cod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

long	current_time_ms(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000L) + (timestamp.tv_usec / 1000L));
}

long	elapsed_since(long start)
{
	return (current_time_ms() - start);
}

void	precise_sleep(long duration_ms, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = current_time_ms();
	while (!simulation_stopped(table))
	{
		elapsed = current_time_ms() - start;
		if (elapsed >= duration_ms)
			break ;
		remaining = duration_ms - elapsed;
		if (remaining > 5)
			usleep(1000);
		else
			usleep(100);
	}
}
