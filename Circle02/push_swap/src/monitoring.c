/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:31:35 by fbui-min          #+#    #+#             */
/*   Updated: 2025/07/27 13:31:35 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_error(int error_type)
{
	ft_putstr_fd("Error\n", 2);
	exit(error_type);
}

void	display_stack(t_stack *stack, char *message)
{
	if (!stack)
		return ;
	ft_putstr_fd(message, 1);
	while (stack)
	{
		ft_putnbr_fd(stack->num, 1);
		ft_putchar_fd('\n', 1);
		stack = stack->next;
	}
}
