/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_searching.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:31:39 by fbui-min          #+#    #+#             */
/*   Updated: 2025/08/23 19:09:01 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_pos(t_stack *stack)
{
	int	current_pos;
	int	min_pos;
	int	min;

	current_pos = 0;
	min_pos = 0;
	min = stack->num;
	while (stack)
	{
		if (stack->num < min)
		{
			min = stack->num;
			min_pos = current_pos;
		}
		current_pos++;
		stack = stack->next;
	}
	return (min_pos);
}

int	find_min(t_stack *stack)
{
	int	min;

	min = stack->num;
	while (stack)
	{
		if (stack->num < min)
			min = stack->num;
		stack = stack->next;
	}
	return (min);
}

int	find_max(t_stack *stack)
{
	int	max;

	max = stack->num;
	while (stack)
	{
		if (stack->num > max)
			max = stack->num;
		stack = stack->next;
	}
	return (max);
}

int	find_pos(t_stack *stack, int num)
{
	int	tar_pos;

	if (!stack)
		return (-1);
	tar_pos = 0;
	while (stack)
	{
		if (stack->num == num)
			return (tar_pos);
		tar_pos++;
		stack = stack->next;
	}
	return (-1);
}

int	find_insert_pos(t_stack *stack, int num)
{
	int		min;
	int		max;
	t_stack	*current;

	if (!stack)
		return (-1);
	min = find_min(stack);
	max = find_max(stack);
	if (num < min || num > max)
		return (find_min_pos(stack));
	current = stack;
	while (current->next)
	{
		if (current->num < num && current->next->num > num)
			return (find_pos(stack, current->next->num));
		current = current->next;
	}
	return (0);
}
