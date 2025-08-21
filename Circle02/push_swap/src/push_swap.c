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

#include "../includes/push_swap.h"

bool	is_stack_sorted(t_stack *stack)
{
	int	tmp;

	tmp = stack->num;
	while (stack)
	{
		if (tmp > stack->num)
		return (false);
		tmp = stack->num;
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

// typedef struct	s_cheapest {
// 	int	num;
// 	int	total_ops;
// 	int	move_id; // 0:ra+rb, 1:rra+rrb, 2:ra+rrb, 3:rra+rb
// } t_cheapest;

// void	find_cheapest_move()
// {
// 	// iretate through the list to find the best candidate
// 		// get the cheapest operation type out of 4
// }

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

void	sort_stack(t_stack **stack_a)
{
	t_stack	*stack_b;
	int		nodes;
	int		median;

	(void)stack_b;
	stack_b = NULL;
	if (!*stack_a || !stack_a)
		return ;
	nodes = count_stack(*stack_a);
	if (nodes == 2)
		ra(stack_a);
	else
	{
		median = get_median(*stack_a, nodes);
		printf("%d\n", median);
		while (count_three_nodes(*stack_a) != 3)
		{
			pb(stack_a, &stack_b);
			if (stack_b->num > median)
				rb(&stack_b);
		}
		sort_three(stack_a);
		// 4. push back to a
		rotate_min_to_top(stack_a, ra, rra);
	}
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;

	stack_a = NULL;
	process_input(&stack_a, argc, argv);
	if (!is_stack_sorted(stack_a))
		sort_stack(&stack_a);
	// display_stack(stack_a, "Sorted stack\n");
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
