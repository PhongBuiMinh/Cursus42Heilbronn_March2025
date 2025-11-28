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
//
void	lock_forks(t_philo *philo)
{
	if (philo->left_fork_idx < philo->right_fork_idx)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork_idx]);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork_idx]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork_idx]);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork_idx]);
		print_status(philo, "has taken a fork");
	}
}

void	unlock_forks(t_philo *philo)
{
	if (philo->left_fork_idx < philo->right_fork_idx)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork_idx]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork_idx]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork_idx]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork_idx]);
	}
}

void	eat_and_sleep(t_philo *philo)
{
	if (is_simulation_ended(philo->data))
		return ;
	print_status(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	unlock_forks(philo);
	if (is_simulation_ended(philo->data))
		return ;
	print_status(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

int	try_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	if (is_simulation_ended(philo->data))
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		return (0);
	}
	philo->last_meal_time = get_current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->philo_mutex);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		print_status(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		return (NULL);
	}
	usleep((philo->id % 2) * 1000);
	while (!is_simulation_ended(philo->data))
	{
		print_status(philo, "is thinking");
		usleep(500);
		lock_forks(philo);
		if (!try_eat(philo))
		{
			unlock_forks(philo);
			break ;
		}
		eat_and_sleep(philo);
	}
	return (NULL);
}
