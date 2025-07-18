/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:00:29 by fbui-min          #+#    #+#             */
/*   Updated: 2025/07/18 02:40:26 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_received = 0;

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
	usleep(100);
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
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
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
