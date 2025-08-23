/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:31:46 by fbui-min          #+#    #+#             */
/*   Updated: 2025/08/23 16:33:09 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	is_stack_sorted(t_stack *stack)
{
	if (!stack || !stack->next)
		return (true);
	while (stack->next)
	{
		if (stack->num > stack->next->num)
			return (false);
		stack = stack->next;
	}
	return (true);
}

int	get_median(t_stack *stack, int size)
{
	t_stack	*current;
	t_stack	*runner;
	int		count_smaller;

	current = stack;
	while (current)
	{
		runner = stack;
		count_smaller = 0;
		while (runner)
		{
			if (runner->num < current->num)
				count_smaller++;
			runner = runner->next;
		}
		if (count_smaller == (size - 1) / 2)
			return (current->num);
		current = current->next;
	}
	return (0);
}

int	cal_combined_cost(t_cost_cal cost, t_stack_info info)
{
	if (info.a_pos <= info.size_a / 2 && info.b_pos <= info.size_b / 2)
	{
		if (cost.ca < cost.cb)
			return (cost.ca);
		return (cost.cb);
	}
	return (0);
}

int	cal_rotation_cost(int size, int index)
{
	if (index <= size / 2)
		return (index);
	return (size - index);
}

int	get_signed_rotations(int index, int size, int rotation_count)
{
	if (index <= size / 2)
		return (rotation_count);
	return (-rotation_count);
}
