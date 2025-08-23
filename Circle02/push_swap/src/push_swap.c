/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:31:43 by fbui-min          #+#    #+#             */
/*   Updated: 2025/07/27 13:31:43 by fbui-min         ###   ########.fr       */
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

void	sort_three(t_stack **stack_a)
{
	int	first;
	int	second;
	int	max;

	first = (*stack_a)->num;
	second = (*stack_a)->next->num;
	max = find_max(*stack_a);
	if (max == first)
	ra(stack_a);
	else if (max == second)
	rra(stack_a);
	if (!is_stack_sorted(*stack_a))
	sa(stack_a);
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

void	rotate_min_to_top(t_stack **stack, void (*r)(t_stack **), void (*rr)(t_stack **))
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

int	calculate_rotation_cost(int size, int index)
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
	int	min;
	int	max;

	if (!stack)
		return (-1);
	min = find_min(stack);
	max = find_max(stack);
	if (num < min || num > max)
		return (find_min_pos(stack));
	while (stack->next)
	{
		if (stack->num < num && stack->next->num > num)
			return (find_pos(stack, stack->next->num));
		stack = stack->next;
	}
	return (0);
}

int	cal_combined_cost(t_cost_cal cost, t_stack_info info)
{
	if (info.ins <= info.size_a / 2 && info.i <= info.size_b / 2)
	{
		if (cost.ca < cost.cb)
			return (cost.ca);
		return (cost.cb);
	}
	return (0);
}

void	find_cheapest_num(t_stack *stack_a, t_stack *stack_b, int *cost_a, int *cost_b)
{
	t_cost_cal		cost;
	t_stack_info	info;

	info.i = 0;
	cost.lowest_cost = INT_MAX;
	info.size_a = count_stack(stack_a);
	info.size_b = count_stack(stack_b);
	while (stack_b)
	{
		cost.cb = calculate_rotation_cost(info.size_b, info.i);
		info.ins = find_insert_pos(stack_a, stack_b->num);
		cost.ca = calculate_rotation_cost(info.size_a, info.ins);
		cost.current_cost = cost.ca + cost.cb - cal_combined_cost(cost, info);
		if (cost.current_cost < cost.lowest_cost)
		{
			cost.lowest_cost = cost.current_cost;
			*cost_b = get_signed_rotations(info.i, info.size_b, cost.cb);
			*cost_a = get_signed_rotations(info.ins, info.size_a, cost.ca);
		}
		info.i++;
		stack_b = stack_b->next;
	}
}

void	double_rotation(int *cost_a, int *cost_b, t_stack **stack_a, t_stack **stack_b)
{
	while (*cost_a < 0 && *cost_b < 0)
	{
		rrr(stack_a, stack_b);
		(*cost_a)++;
		(*cost_b)++;
	}
	while (*cost_a > 0 && *cost_b > 0)
	{
		rr(stack_a, stack_b);
		(*cost_a)--;
		(*cost_b)--;
	}
}

void	single_rotation(t_stack **stack, int cost, void (*r)(t_stack **), void (*rr)(t_stack **))
{
	while (cost < 0)
	{
		r(stack);
		cost++;
	}
	while (cost > 0)
	{
		rr(stack);
		cost--;
	}
}

void	push_back_to_a(t_stack **stack_a, t_stack **stack_b)
{
	int	cost_a;
	int	cost_b;

	while (*stack_b)
	{
		find_cheapest_num(*stack_a, *stack_b, &cost_a, &cost_b);
		double_rotation(&cost_a, &cost_b, stack_a, stack_b);
		single_rotation(stack_b, cost_b, rb, rrb);
		single_rotation(stack_a, cost_a, ra, rra);
		pa(stack_b, stack_a);
	}
}

void	sort_stack(t_stack **stack_a)
{
	t_stack	*stack_b;
	int		nodes;
	int		median;

	stack_b = NULL;
	if (!*stack_a || !stack_a)
		return ;
	nodes = count_stack(*stack_a);
	if (nodes == 2)
		ra(stack_a);
	else
	{
		median = get_median(*stack_a, nodes);
		while (count_three_nodes(*stack_a) != 3)
		{
			pb(stack_a, &stack_b);
			if (stack_b->num > median)
				rb(&stack_b);
		}
		sort_three(stack_a);
		// push_back_to_a(stack_a, &stack_b);
		// rotate_min_to_top(stack_a, ra, rra);
	}
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;

	stack_a = NULL;
	process_input(&stack_a, argc, argv);
	if (!is_stack_sorted(stack_a))
		sort_stack(&stack_a);
	display_stack(stack_a, "Sorted stack");
}

// int	main(int argc, char **argv)
// {
// 	t_stack	*stack_a;

// 	stack_a = NULL;
// 	process_input(&stack_a, argc, argv);
// 	display(stack_a, "Inputs received\n");
// 	sa(&stack_a);
// 	display(stack_a, "Swap\n");
// 	rotate(&stack_a);
// 	display(stack_a, "Rotate\n");
// 	reverse_rotate(&stack_a);
// 	display(stack_a, "Reverse rotate\n");
// }
