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

int	check_death(t_data *data)
{
	int				i;
	unsigned long	now;

	i = 0;
	now = get_current_time();
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].philo_mutex);
		if (now - data->philos[i].last_meal_time >= (unsigned long)data->time_to_die)
		{
			print_status(&data->philos[i], "died");
			pthread_mutex_lock(&data->simulation_mutex);
			data->simulation_end = 1;
			pthread_mutex_unlock(&data->simulation_mutex);
			pthread_mutex_unlock(&data->philos[i].philo_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].philo_mutex);
		i++;
	}
	return (0);
}

void	*monitor_death(void *arg)
{
	t_data  *data;

	data = (t_data *)arg;
	while (!data->simulation_end)
	{
		if (check_death(data))
			break;
		usleep(50);
	}
	return (NULL);
}
