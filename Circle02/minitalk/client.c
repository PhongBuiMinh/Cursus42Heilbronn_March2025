/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:00:29 by fbui-min          #+#    #+#             */
/*   Updated: 2025/06/15 20:52:54 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t g_ack_received = 0;

void	ft_signal_handler(int sig)
{
	static size_t	bit = 0;

	if (sig == SIGUSR1)
	{
		bit++;
		g_ack_received = 1;
	}
	else if (sig == SIGUSR2)
	{
		printf("received bits :%ld", bit++);
		g_ack_received = 1;
		bit = 0;
		exit(0);
	}
}

void	send_bit(int PID, char byte)
{
	int	i;
	int	timeout;

	i = 8;
	timeout = 500;
	while (i-- > 0)
	{
		g_ack_received = 0;
		if (((byte >> i) & 1) == 0)
			kill(PID, SIGUSR1);
		else if (((byte >> i) & 1) == 1)
			kill(PID, SIGUSR2);
		while (!g_ack_received && (timeout > 0))
		{
			usleep(100);
			timeout -= 100;
		}
		if (timeout <= 0)
			printf("timeout\n");
	}
}

void	encode_string(int PID, char *str)
{
	while (*str)
	{
		send_bit(PID, *str);
		str++;
	}
	send_bit(PID, '\0');
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sa;

	if (argc != 3)
		return (ft_printf("User: ./a.out PID message\n"), 1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (ft_printf("PID error.\n"), 1);
	sa.sa_handler = ft_signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (printf("Custom handler failed."), 1);
	encode_string(pid, argv[2]);
	while (1)
		pause();
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
