/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/07/24 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

long	elapsed_since(long start)
{
	return (current_time_ms() - start);
}

void	precise_sleep(long duration_ms, t_table *table)
{
	long	start;
	long	elapsed;

	start = current_time_ms();
	while (!simulation_stopped(table))
	{
		elapsed = current_time_ms() - start;
		if (elapsed >= duration_ms)
			break ;
		if (duration_ms - elapsed > 5)
			usleep(1000);
		else
			usleep(100);
	}
}
