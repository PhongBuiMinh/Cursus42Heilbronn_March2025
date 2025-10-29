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
	
int	philo_atoi(const char *str)
{
	int	num;
	int	i;
	
	num = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
			i++;
	if (str[i] == '-')
		return (-1);
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0' || num == 0)
		return (-1);
	return (num);
}

long	get_current_time(void)
{
	struct timeval	tv;
	long	miliseconds;

	gettimeofday(&tv, NULL);
	miliseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (miliseconds);
}

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
	if ((data->num_philos == -1 || data->time_to_die == -1 ||
		data->time_to_eat == -1 || data->time_to_sleep == -1) ||
		(argc == 6 && data->must_eat_count == -1))
	{
		printf("Error: All arguments must be positive integer\n")
		exit(1);
	}
	if (data->num_philos > 200)
		printf("Warnings: %d philosophers might cause performance issues\n", data->num_philos)
}

void	initialize_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
	{
		printf("Error: Failed to allocate memory for philos\n");
		exit(1);
	}
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].eat_count = 0;
		data->philos[i].last_meal_time = 0;
		i++;
		// Initialize other fields, like forks, mutexes, states
	}
	// Initialize mutexes for forks and any shared resources here or separately
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	t_data	data;

	parse_arguments(argc);
	validate_parsed_arguments(&data, argc);
	initialize_philos(&data);
	long	start_time = get_current_time();
	usleep(1000);
	long	current_time = get_current_time();
	long	elapsed_time = current_time - start_time;
	printf("timestamp: %ld\n", elapsed_time);
}
