/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:00:29 by fbui-min          #+#    #+#             */
/*   Updated: 2025/06/11 21:14:37 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_bit(int PID, int bit)
{
	if (bit == 0)
		kill(PID, SIGUSR1);
	else
		kill(PID, SIGUSR2);
	usleep(100);
}

void	send_string(int PID, char *str)
{
	int	i;

	while (*str)
	{
		i = 8;
		while (i-- > 0)
			send_bit(PID, (*str >> i) & 1);
		str++;
	}
	i = 8;
	while (i-- > 0)
		send_bit(PID, ('\0' >> i) & 1);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("User: ./a.out PID message\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (1);
	send_string(pid, argv[2]);
	return (0);
}
