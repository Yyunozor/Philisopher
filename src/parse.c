/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:20:23 by anpayot           #+#    #+#             */
/*   Updated: 2025/10/31 14:59:35 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static int	parse_number(const char *str, long *out)
{
	long	result;
	int		digit;

	if (*str == '\0')
		return (1);
	result = 0;
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
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

static int	parse_positive(const char *str, long *out)
{
	if (parse_number(str, out) != 0)
		return (1);
	if (*out <= 0)
		return (1);
	return (0);
}

static int	fill_core_params(t_table *table, char **argv)
{
	long	value;

	if (parse_positive(argv[1], &value) != 0)
		return (1);
	table->philo_count = (int)value;
	if (parse_positive(argv[2], &value) != 0)
		return (1);
	table->time_to_die = value;
	if (parse_positive(argv[3], &value) != 0)
		return (1);
	table->time_to_eat = value;
	if (parse_positive(argv[4], &value) != 0)
		return (1);
	table->time_to_sleep = value;
	return (0);
}

static int	fill_optional_meals(t_table *table, int argc, char **argv)
{
	long	value;

	table->meals_required = -1;
	if (argc == 6)
	{
		if (parse_positive(argv[5], &value) != 0)
			return (1);
		table->meals_required = (int)value;
	}
	return (0);
}

int	parse_arguments(t_table *table, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (fill_core_params(table, argv) != 0)
		return (1);
	if (fill_optional_meals(table, argc, argv) != 0)
		return (1);
	table->philos = NULL;
	table->stop = false;
	return (0);
}
