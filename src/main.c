/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpt-5-codex <gpt-5-c@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:00:00 by gpt-5-cod         #+#    #+#             */
/*   Updated: 2024/07/24 00:00:00 by gpt-5-cod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_table	table;

	if (parse_arguments(&table, argc, argv) != 0)
	{
		fprintf(stderr, "Error\n");
		fprintf(stderr, "Invalid input\n");
		return (1);
	}
	if (init_table(&table) != 0)
	{
		destroy_table(&table);
		fprintf(stderr, "Error\n");
		return (1);
	}
	if (launch_threads(&table) != 0)
	{
		destroy_table(&table);
		fprintf(stderr, "Error\n");
		return (1);
	}
	destroy_table(&table);
	return (0);
}
