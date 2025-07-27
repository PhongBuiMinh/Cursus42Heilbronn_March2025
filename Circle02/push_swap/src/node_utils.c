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

t_stack	*last_node(t_stack *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

int	count_nodes(t_stack *stack)
{
	size_t	elements;

	if (!stack)
		return (0);
	elements = 0;
	while (stack && elements < 5)
	{
		elements++;
		stack = stack->next;
	}
	return (elements);
}

int	stack_size(t_stack *stack)
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
