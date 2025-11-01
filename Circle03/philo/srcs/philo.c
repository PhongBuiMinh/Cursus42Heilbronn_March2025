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

void	lock_forks(t_philo *philo)
{
	if (philo->left_fork_idx < philo->right_fork_idx)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork_idx]);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork_idx]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork_idx]);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork_idx]);
	}
	print_status(philo, "has taken a fork");
}

void	unlock_forks(t_philo *philo)
{
	if (philo->left_fork_idx < philo->right_fork_idx)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork_idx]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork_idx]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork_idx]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork_idx]);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		print_status(philo, "is thinking");
		lock_forks(philo);
		if (is_simulation_ended(philo->data))
		{
			unlock_forks(philo);
			break;
		}
		print_status(philo, "is eating");
		pthread_mutex_lock(&philo->philo_mutex);
		philo->last_meal_time = get_current_time();
		philo->eat_count++;
		pthread_mutex_unlock(&philo->philo_mutex);
		usleep(philo->data->time_to_eat * 1000);
		unlock_forks(philo);
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}
