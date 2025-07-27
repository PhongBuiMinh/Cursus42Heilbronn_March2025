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
	if (error_type == 1)
		ft_putstr_fd("User: ./push_swap arguments\n", 2);
	else if (error_type == 2)
		ft_putstr_fd("Invalid arguments!\n", 2);
	else if (error_type == 3)
		ft_putstr_fd("Allocation failed!\n", 2);
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
	ft_putchar_fd('\n', 1);
}
