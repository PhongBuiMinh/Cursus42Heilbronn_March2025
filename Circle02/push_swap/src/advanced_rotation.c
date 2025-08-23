/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_rotation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:31:46 by fbui-min          #+#    #+#             */
/*   Updated: 2025/08/23 19:19:01 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	single_rotation(t_stack **stack,
	int cost, void (*r)(t_stack **), void (*rr)(t_stack **))
{
	while (cost < 0)
	{
		rr(stack);
		cost++;
	}
	while (cost > 0)
	{
		r(stack);
		cost--;
	}
}

void	double_rotation(int *cost_a, int *cost_b, t_stack **a, t_stack **b)
{
	while (*cost_a < 0 && *cost_b < 0)
	{
		rrr(a, b);
		(*cost_a)++;
		(*cost_b)++;
	}
	while (*cost_a > 0 && *cost_b > 0)
	{
		rr(a, b);
		(*cost_a)--;
		(*cost_b)--;
	}
}

void	rotate_min_to_top(t_stack **stack,
	void (*r)(t_stack **), void (*rr)(t_stack **))
{
	int	min_pos;
	int	size;
	int	i;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	min_pos = find_min_pos(*stack);
	size = count_stack(*stack);
	i = 0;
	if (min_pos <= size / 2)
	{
		while (i++ < min_pos)
			r(stack);
	}
	else
	{
		while (i++ < size - min_pos)
			rr(stack);
	}
}
