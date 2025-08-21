/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:31:39 by fbui-min          #+#    #+#             */
/*   Updated: 2025/07/27 13:31:39 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_three_nodes(t_stack *stack)
{
	size_t	elements;

	if (!stack)
		return (0);
	elements = 0;
	while (stack && elements < 3)
	{
		elements++;
		stack = stack->next;
	}
	return (elements);
}

int	count_stack(t_stack *stack)
{
	size_t	elements;

	if (!stack)
		return (0);
	elements = 0;
	while (stack)
	{
		elements++;
		stack = stack->next;
	}
	return (elements);
}

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
