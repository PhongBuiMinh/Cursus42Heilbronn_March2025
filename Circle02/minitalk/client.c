/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:00:29 by fbui-min          #+#    #+#             */
/*   Updated: 2025/07/02 17:56:57 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t g_ack_received = 0;

void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack_received = 1;
}

void	send_bit(int pid, char byte)
{
	int	i;

	i = 8;
	while (i-- > 0)
	{
		g_ack_received = 0;
		if (((byte >> i) & 1) == 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(-2);
		}
		else if (((byte >> i) & 1) == 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(-2);
		}
		usleep(50);
	}
	while (!g_ack_received)
		pause();
}

void	configure_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(-1);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*message;

	if (argc != 3)
		return (ft_printf("User: ./a.out PID message\n"), 1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (ft_printf("PID error.\n"), 1);
	configure_signal();
	message = argv[2];
	while (*message)
		send_bit(pid, *message++);
	send_bit(pid, '\0');
	return (0);
}

// Version 1
// void	send_bit(int PID, int bit)
// {
// 	if (bit == 0)
// 		kill(PID, SIGUSR1);
// 	else
// 		kill(PID, SIGUSR2);
// 	usleep(100);
// }

// void	send_string(int PID, char *str)
// {
// 	int	i;

// 	while (*str)
// 	{
// 		i = 8;
// 		while (i-- > 0)
// 			send_bit(PID, (*str >> i) & 1);
// 		str++;
// 	}
// 	i = 8;
// 	while (i-- > 0)
// 		send_bit(PID, ('\0' >> i) & 1);
// }

// int	main(int argc, char **argv)
// {
// 	int	pid;

// 	if (argc != 3)
// 	{
// 		ft_printf("User: ./a.out PID message\n");
// 		return (1);
// 	}
// 	pid = ft_atoi(argv[1]);
// 	if (pid <= 0)
// 		return (1);
// 	send_string(pid, argv[2]);
// 	return (0);
// }
