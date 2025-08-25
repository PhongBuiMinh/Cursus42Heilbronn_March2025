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

bool	has_n_nodes(t_stack *stack, int n)
{
	int	size;

	if (!stack)
		return (false);
	size = 0;
	while (stack && size < n + 1)
	{
		size++;
		stack = stack->next;
	}
	if (size != n)
		return (false);
	return (true);
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

t_stack	*last_node(t_stack *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}
