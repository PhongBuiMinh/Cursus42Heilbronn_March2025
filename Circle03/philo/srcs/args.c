/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:33:21 by fbui-min          #+#    #+#             */
/*   Updated: 2025/10/03 16:34:30 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_arguments(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [must_eat_count]\n");
		exit(0);
	}
	data->num_philos = philo_atoi(argv[1]);
	data->time_to_die = philo_atoi(argv[2]);
	data->time_to_eat = philo_atoi(argv[3]);
	data->time_to_sleep = philo_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = philo_atoi(argv[5]);
	else
		data->must_eat_count = -1;
}

void	validate_parsed_arguments(t_data *data, int argc)
{
	if ((data->num_philos == -1 || data->time_to_die == -1
			|| data->time_to_eat == -1 || data->time_to_sleep == -1)
		|| (argc == 6 && data->must_eat_count == -1))
	{
		printf("Error: All arguments must be positive integer\n");
		exit(1);
	}
	if (data->num_philos > 200)
		printf("Warning: %d philosophers might cause performance issues\n",
			data->num_philos);
}
