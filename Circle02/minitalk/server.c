/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:00:29 by fbui-min          #+#    #+#             */
/*   Updated: 2025/07/03 15:53:17 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	decode_string(char byte)
{
	static char	*message = NULL;
	static int	index = 0;
	int			str_size;

	str_size = 500;
	if (!message)
		message = (char *)ft_calloc(str_size, sizeof(char));
	if (!message)
		return ;
	if (index < str_size)
		message[index++] = byte;
	if (byte == '\0' || index == str_size)
	{
		ft_putstr_fd(message, 1);
		free(message);
		message = NULL;
		index = 0;
	}
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
			ft_putstr_fd("Error: failed to send confirmation signal\n", 2);
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
// ///////////////////////////////////////////////
// void	advanced_signal_handler(int sig, siginfo_t *info, void *ucontext)
// {
// 	(void)ucontext;
// 	printf("Signal received: %d from PID: %d\n", sig, info->si_pid);
// 	exit(0);
// }

// char	*append_message(char *src, char c)
// {
// 	char	*dst;
// 	int		i;

// 	i = 0;
// 	dst = (char *)malloc(ft_strlen(src) + 2 * sizeof(char));
// 	if (!dst)
// 	{
// 		free(src);
// 		return (NULL);
// 	}
// 	while (src[i])
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i++] = c;
// 	dst[i] = '\0';
// 	free(src);
// 	return (dst);
// }

// void	signal_handler(int sig)
// {
// 	static char	byte = 0;
// 	static int	bit_pos = 7;
// 	static char	*message;

// 	if (!message)
// 		message = ft_strdup("");
// 	if (sig == SIGUSR1)
// 		byte &= ~(1 << bit_pos);
// 	else if (sig == SIGUSR2)
// 		byte |= (1 << bit_pos);
// 	bit_pos--;
// 	if (bit_pos < 0)
// 	{
// 		message = append_message(message, byte);
// 		if (byte == '\0')
// 		{
// 			ft_printf("%s", message);
// 			message = NULL;
// 		}
// 		byte = 0;
// 		bit_pos = 7;
// 	}
// }

// int	main(void)
// {
// 	struct sigaction	action;

// 	ft_printf("%d\n", getpid());
// 	action.sa_handler = signal_handler;
// 	action.sa_flags = 0; // default beahvior (no SA_RESTART)
// 	// action.sa_sigaction = advanced_signal_handler;
// 	// sa.sa_flags = SA_SIGINFO;  // Enable advanced handler
// 	sigemptyset(&action.sa_mask);
// 	// clear signal sa_mask and initialize it (type sigset_t) no blocked signals
// 	// sigaddset(&sa.sa_mask, SIGTERM); // Block SIGTERM while handler runs

// 	// register handlers for multiple signals (SIGINT, SIGTERM)
// 	sigaction(SIGINT, &action, NULL);
// 	 // Handle Ctrl + C
// 	sigaction(SIGTERM, &action, NULL); // Termination signal
// 	sigaction(SIGUSR1, &action, NULL);
// 	sigaction(SIGUSR2, &action, NULL);
// 	// signal(SIGINT, signal_handler);
// 	// signal(SIGTERM, signal_handler);
// 	// signal(SIGUSR1, signal_handler);
// 	// signal(SIGUSR2, signal_handler);
// 	while (1) pause();

// 	return (0);
// }
