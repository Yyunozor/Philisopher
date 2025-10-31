/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:26:03 by anpayot           #+#    #+#             */
/*   Updated: 2025/10/31 14:26:06 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

long	current_time_ms(void)
{
	struct timeval		v;

	gettimeofday(&v, NULL);
	return ((v.tv_sec * 1000L) + (v.tv_usec / 1000L));
}

long	elapsed_since(long start)
{
	return (current_time_ms() - start);
}

static void	sleep_chunk(long remaining)
{
	if (remaining > 5)
		usleep(1000);
	else
		usleep(100);
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
		sleep_chunk(remaining);
	}
}
