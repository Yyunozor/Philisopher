/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/07/24 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <ctype.h>
#include <limits.h>

static int	parse_number(const char *str, long *out)
{
	long	value;
	int	digit;

	if (*str == '\0')
		return (1);
	value = 0;
	while (*str)
	{
		if (!isdigit((unsigned char)*str))
			return (1);
		digit = *str - '0';
		if (value > INT_MAX / 10
			|| (value == INT_MAX / 10 && digit > INT_MAX % 10))
			return (1);
		value = value * 10 + digit;
		str++;
	}
	*out = value;
	return (0);
}

static int	read_positive(long *dst, char *arg)
{
	long	value;

	if (parse_number(arg, &value) || value <= 0)
		return (1);
	*dst = value;
	return (0);
}

int		parse_arguments(t_table *table, int argc, char **argv)
{
	long	value;

	if (argc != 5 && argc != 6)
		return (1);
	if (read_positive(&value, argv[1]))
		return (1);
	table->philo_count = (int)value;
	if (read_positive(&value, argv[2]))
		return (1);
	table->time_to_die = value;
	if (read_positive(&value, argv[3]))
		return (1);
	table->time_to_eat = value;
	if (read_positive(&value, argv[4]))
		return (1);
	table->time_to_sleep = value;
	table->meals_required = -1;
	if (argc == 6)
	{
		if (read_positive(&value, argv[5]))
			return (1);
		table->meals_required = (int)value;
	}
	table->philos = NULL;
	table->stop = false;
	return (0);
}
