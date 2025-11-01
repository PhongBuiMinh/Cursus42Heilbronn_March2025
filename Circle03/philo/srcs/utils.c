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

int	is_simulation_ended(t_data *data)
{
	int	ended;

	pthread_mutex_lock(&data->simulation_mutex);
	ended = data->simulation_end;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (ended);
}

long	get_current_time(void)
{
	struct timeval	tv;
	long	miliseconds;
	
	gettimeofday(&tv, NULL);
	miliseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (miliseconds);
}

long	get_timestamp(t_philo *philo)
{
	return (get_current_time() - philo->data->start_time);
}

void	print_status(t_philo *philo, const char *status)
{
	long	timestamp;

	if (is_simulation_ended(philo->data))
		return;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return;
	}
	timestamp = get_timestamp(philo);
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
