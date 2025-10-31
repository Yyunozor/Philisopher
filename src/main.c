/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:20:36 by anpayot           #+#    #+#             */
/*   Updated: 2025/10/31 14:20:38 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static int	report_error(void)
{
	fprintf(stderr, "Error\n");
	fprintf(stderr, "Invalid input\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (parse_arguments(&table, argc, argv) != 0)
		return (report_error());
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
