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

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

typedef struct s_data
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_count;
}	t_data;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	t_data		data;
} 				t_philo;
	
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
	{
		if (str[i++] == '-')
			return (-1);
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0' || num == 0)
		return (-1);
	return (num);
}

void	release_fork(void)
{
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
}

void	take_fork(void)
{
	if (id % 2 == 0)
	{
		pthread_mutex_lock(left_fork);
		print_status(taken a fork);
		pthread_mutex_lock(right_fork);
		print_status(taken a fork);
	}
	else
	{
		pthread_mutex_lock(right_fork);
		print_status(taken a fork);
		pthread_mutex_lock(left_fork);
		print_status(taken a fork);
	}
}

void	*act(void *arg)
{
	int	id;
		
	id = *(int*)arg;
	printf("Philo %d is thinking\n", id);
	sleep(1);
	printf("Philo %d is eating\n", id);
	sleep(1);
	printf("Philo %d is sleeping\n", id);
	sleep(1);
	return (NULL);
}
		
int	main(int argc, char **argv)
{
	// (void)argv;
	// (void)argc;
	if (argc < 6)
	{
		printf("Usage: ./philo n_philo time_to_die time_to_eat time_to_sleep [n_times_each_philo_must_eat]\n");
		exit(0);
	}
	int	i;
	i = 1;
	while (argv[i])
	{
		if (philo_atoi(argv[i]) == -1)
			return (1);
		i++;
	}
	t_philo	philo;
	memset(&philo, 0, sizeof(philo));
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	int	ids[3] = {0, 1, 2};
	
	pthread_create(&thread1, NULL, act, &ids[0]);
	pthread_create(&thread2, NULL, act, &ids[1]);
	pthread_create(&thread3, NULL, act, &ids[2]);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	return (0);
}
