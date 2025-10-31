/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpt-5-codex <gpt-5-c@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:00:00 by gpt-5-cod         #+#    #+#             */
/*   Updated: 2024/07/24 00:00:00 by gpt-5-cod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

static int	parse_number(const char *str, long *out)
{
	long	result;
	int	digit;

	if (*str == '\0')
		return (1);
	result = 0;
	while (*str)
	{
		if (!isdigit((unsigned char)*str))
			return (1);
		digit = *str - '0';
		if (result > INT_MAX / 10
			|| (result == INT_MAX / 10 && digit > INT_MAX % 10))
			return (1);
		result = result * 10 + digit;
		str++;
	}
	*out = result;
	return (0);
}

static int	read_positive(const char *arg, long *value)
{
	if (parse_number(arg, value) != 0)
		return (1);
	if (*value <= 0)
		return (1);
	return (0);
}

static int	set_duration(long *destination, const char *arg)
{
	long	value;

	if (read_positive(arg, &value) != 0)
		return (1);
	*destination = value;
	return (0);
}

int	parse_arguments(t_table *table, int argc, char **argv)
{
	long	value;

	if (argc != 5 && argc != 6)
		return (1);
	if (read_positive(argv[1], &value) != 0)
		return (1);
	table->philo_count = (int)value;
	if (set_duration(&table->time_to_die, argv[2]) != 0)
		return (1);
	if (set_duration(&table->time_to_eat, argv[3]) != 0)
		return (1);
	if (set_duration(&table->time_to_sleep, argv[4]) != 0)
		return (1);
	table->meals_required = -1;
	if (argc == 6)
	{
		if (read_positive(argv[5], &value) != 0)
			return (1);
		table->meals_required = (int)value;
	}
	table->philos = NULL;
	table->stop = false;
	return (0);
}
