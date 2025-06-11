/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phong <phong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 02:07:23 by phong             #+#    #+#             */
/*   Updated: 2025/06/11 07:41:20 by phong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

// int	main()
// {
// 	unsigned char	letter = 'A';
// 	int				i;

// 	i = 8;
// 	while (i-- > 0)
// 		printf("Bit %d // %d\n", i, ((letter >> i) & 1));

// 	return (0);
// }

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
