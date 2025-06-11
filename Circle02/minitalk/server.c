/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phong <phong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 02:07:38 by phong             #+#    #+#             */
/*   Updated: 2025/06/11 07:27:48 by phong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "libft.h"
#include "ft_printf.h"

void	advanced_signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	printf("Signal received: %d from PID: %d\n", sig, info->si_pid);
	exit(0);
}

char	*append_message(char *src, char c)
{
	char	*dst;
	int		i;

	i = 0;
	dst = (char *)malloc(ft_strlen(src) + 2 * sizeof(char));
	if (!dst)
	{
		free(src);
		return (NULL);
	}
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i++] = c;
	dst[i] = '\0';
	free(src);
	return (dst);
}

void	signal_handler(int sig)
{
	static char	byte = 0;
	static int	bit_pos = 7;
	static char	*message;

	if (!message)
		message = ft_strdup("");
	if (sig == 10)
		byte &= ~(1 << bit_pos);
	else if (sig == 12)
		byte |= (1 << bit_pos);
	bit_pos--;
	if (bit_pos < 0)
	{
		if (!message)
			return ;
		message = append_message(message, byte);
		if (byte == '\0')
		{
			ft_printf("%s", message);
			message = NULL;
		}
		byte = 0;
		bit_pos = 7;
	}
}

int	main(void)
{
	struct sigaction	action;

	ft_printf("%d\n", getpid());
	action.sa_handler = signal_handler;
	action.sa_flags = 0;
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGTERM, &action, NULL);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
	return (0);
}

// void	signal_handler(int sig)
// {
// 	static char	byte = 0;
// 	static int	bit_pos = 7;
// 	static char	*message;

// 	if (!message)
// 		message = ft_strdup("");
// 	// printf("Signal received: %d\n", sig);
// 	if (sig == 15 || sig == 2) // 2 - interrupt, 15 -
// termination, default for kill
// 		exit(0);
// 	else if (sig == 10)
// 		byte &= ~(1 << bit_pos);
// 	else if (sig == 12)
// 		byte |= (1 << bit_pos);
// 	bit_pos--;
// 	if (bit_pos < 0)
// 	{
// 		message = append_message(message, byte);
// 		if (byte == '\0')
// 		{
// 			ft_printf("%s\n", message);
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
// 	// clear signal sa_mask and initialize it (type sigset_t)
//  // no blocked signals
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
