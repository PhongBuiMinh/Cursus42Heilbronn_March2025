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

void	exit_error(char *error)
{
	printf("%s", error);
	exit(1);
}

void	initialize_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		exit_error("Error: Failed to allocate memory for forks\n");
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			exit_error("Error: Failed to initialize fork mutex %d\n");
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		exit_error("Error: Failed to initialize print mutex\n");
	if (pthread_mutex_init(&data->simulation_mutex, NULL) != 0)
		exit_error("Error: Failed to initialize simulation mutex\n");
}

void	initialize_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		exit_error("Error: Failed to allocate memory for philos\n");
	data->simulation_end = 0;
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].eat_count = 0;
		data->philos[i].last_meal_time = get_current_time();
		data->philos[i].left_fork_idx = i;
		data->philos[i].right_fork_idx = (i + 1) % data->num_philos;
		if (pthread_mutex_init(&data->philos[i].philo_mutex, NULL) != 0)
			exit_error("Error: Failed to initialize philo mutex for philosopher %d\n");
		i++;
	}
	data->start_time = get_current_time();
}
