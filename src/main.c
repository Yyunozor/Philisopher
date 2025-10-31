/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:20:36 by anpayot           #+#    #+#             */
/*   Updated: 2025/10/31 14:52:58 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	report_error(void)
{
	write(2, "Error\n", 6);
	write(2, "Invalid input\n", 14);
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
		write(2, "Error\n", 6);
		return (1);
	}
	if (launch_threads(&table) != 0)
	{
		destroy_table(&table);
		write(2, "Error\n", 6);
		return (1);
	}
	destroy_table(&table);
	return (0);
}
