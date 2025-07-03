/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:00:29 by fbui-min          #+#    #+#             */
/*   Updated: 2025/07/03 15:16:29 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	*decode_string(char byte)
{
	static char	*message = NULL;
	static int	index = 0;
	int			str_size;

	str_size = 500;
	if (!message)
		message = (char *)ft_calloc(str_size, sizeof(char));
	if (!message)
		return (NULL);
	if (index < str_size)
		message[index++] = byte;
	if (byte == '\0' || index == str_size)
	{
		ft_putstr_fd(message, 1);
		free(message);
		message = NULL;
		index = 0;
	}
	return (message);
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static char	byte = 0;
	static int	bit_pos = 7;

	(void)context;
	if (sig == SIGUSR1)
		byte &= ~(1 << bit_pos);
	else if (sig == SIGUSR2)
		byte |= (1 << bit_pos);
	if (--bit_pos < 0)
	{
		decode_string(byte);
		if (kill(info->si_pid, SIGUSR1) == -1)
		{
			decode_string('\0');
			ft_putstr_fd("Error: failed to send confirmation signal\n", 2);
		}
		byte = 0;
		bit_pos = 7;
	}
}

void	configure_signal(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(-1);
}

int	main(void)
{
	ft_printf("%d\n", getpid());
	configure_signal();
	while (1)
		pause();
	return (0);
}

// Version 1
// void	signal_handler(int sig)
// {
// 	static char	byte = 0;
// 	static int	bit_pos = 7;

// 	if (sig == SIGINT || sig == SIGTERM)
// 		exit(0);
// 	else if (sig == SIGUSR1)
// 		byte &= ~(1 << bit_pos);
// 	else if (sig == SIGUSR2)
// 		byte |= (1 << bit_pos);
// 	bit_pos--;
// 	if (bit_pos < 0)
// 	{
// 		write(1, &byte, 1);
// 		byte = 0;
// 		bit_pos = 7;
// 	}
// }

// int	main(void)
// {
// 	struct sigaction	action;

// 	ft_printf("%d\n", getpid());
// 	action.sa_handler = signal_handler;
// 	action.sa_flags = 0;
// 	sigemptyset(&action.sa_mask);
// 	sigaction(SIGINT, &action, NULL);
// 	sigaction(SIGTERM, &action, NULL);
// 	sigaction(SIGUSR1, &action, NULL);
// 	sigaction(SIGUSR2, &action, NULL);
// 	while (1)
// 		pause();
// 	return (0);
// }
