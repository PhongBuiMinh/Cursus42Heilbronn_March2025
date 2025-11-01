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

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				left_fork_idx;
	int				right_fork_idx;
	int				eat_count;
	unsigned long	last_meal_time;
	pthread_mutex_t	philo_mutex;
	struct s_data	*data;
	pthread_t		thread_id;
} 				t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	unsigned long	start_time;
	int				simulation_end;
	pthread_mutex_t simulation_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t *forks;
	t_philo 		*philos;
}	t_data;

void	parse_arguments(int argc, char **argv, t_data *data);
void	validate_parsed_arguments(t_data *data, int argc);

void	initialize_mutexes(t_data *data);
void	initialize_philos(t_data *data);

void	*philo_routine(void *arg);

int		philo_atoi(const char *str);
long	get_current_time(void);

void	print_status(t_philo *philo, const char *status);
void	*monitor_death(void *arg);
int	is_simulation_ended(t_data *data);

#endif