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

int	main(int argc, char **argv)
{
	pthread_t	monitor_thread;
	t_data		data;
	int			i;

	parse_arguments(argc, argv, &data);
	validate_parsed_arguments(&data, argc);
	initialize_mutexes(&data);
	initialize_philos(&data);
	i = 0;
	while (i < data.num_philos)
	{
		pthread_create(&data.philos[i].thread_id, NULL, philo_routine,
			&data.philos[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor_death, &data);
	i = 0;
	while (i < data.num_philos)
	{
		pthread_join(data.philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	cleanup(&data);
}

// valgrind --tool=helgrind ./bin/philo
// valgrind --leak-check=full ./bin/philo