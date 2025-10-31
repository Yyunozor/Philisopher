/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/07/24 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	print_error(void)
{
	write(1, "Error\n", 6);
}

int		main(int argc, char **argv)
{
	t_table	table;

	if (parse_arguments(&table, argc, argv) != 0)
	{
		print_error();
		return (1);
	}
	if (init_table(&table) != 0)
	{
		print_error();
		destroy_table(&table);
		return (1);
	}
	if (launch_threads(&table) != 0)
	{
		destroy_table(&table);
		print_error();
		return (1);
	}
	destroy_table(&table);
	return (0);
}
