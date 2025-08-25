/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:31:43 by fbui-min          #+#    #+#             */
/*   Updated: 2025/08/25 06:15:48 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	find_cheapest_num(t_stack *a, t_stack *b, int *cost_a, int *cost_b)
{
	t_cost_cal		cost;
	t_stack_info	info;

	info.b_pos = 0;
	cost.lowest_cost = INT_MAX;
	info.size_a = count_stack(a);
	info.size_b = count_stack(b);
	while (b)
	{
		cost.cb = cal_rotation_cost(info.size_b, info.b_pos);
		info.a_pos = find_insert_pos(a, b->num);
		cost.ca = cal_rotation_cost(info.size_a, info.a_pos);
		cost.current_cost = cost.ca + cost.cb - cal_combined_cost(cost, info);
		if (cost.current_cost < cost.lowest_cost)
		{
			cost.lowest_cost = cost.current_cost;
			*cost_b = get_signed_rotations(info.b_pos, info.size_b, cost.cb);
			*cost_a = get_signed_rotations(info.a_pos, info.size_a, cost.ca);
		}
		info.b_pos++;
		b = b->next;
	}
}

void	push_back_to_a(t_stack **a, t_stack **b)
{
	int	cost_a;
	int	cost_b;

	while (*b)
	{
		find_cheapest_num(*a, *b, &cost_a, &cost_b);
		double_rotation(&cost_a, &cost_b, a, b);
		single_rotation(b, cost_b, rb, rrb);
		single_rotation(a, cost_a, ra, rra);
		pa(b, a);
	}
}

void	sort_three(t_stack **stack)
{
	int	first;
	int	second;
	int	max;

	first = (*stack)->num;
	second = (*stack)->next->num;
	max = find_max(*stack);
	if (max == first)
		ra(stack);
	else if (max == second)
		rra(stack);
	if (!is_stack_sorted(*stack))
		sa(stack);
}

void	sort_stack(t_stack **a)
{
	t_stack	*b;
	int		size;
	int		median;

	b = NULL;
	if (!*a || !a)
		return ;
	size = count_stack(*a);
	if (size == 2)
		ra(a);
	else
	{
		median = get_median(*a, size);
		while (!has_n_nodes(*a, 3))
		{
			pb(a, &b);
			if (b->num > median && has_n_nodes(b, 2))
				rb(&b);
		}
		sort_three(a);
		push_back_to_a(a, &b);
		rotate_min_to_top(a, ra, rra);
	}
}
