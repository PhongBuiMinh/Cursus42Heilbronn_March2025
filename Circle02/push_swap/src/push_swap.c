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

void	push_two_unchecked(t_stack **stack_a, t_stack **stack_b)
{
	if (count_nodes(*stack_a) != 3)
		pb(stack_a, stack_b);
	if (count_nodes(*stack_a) != 3)
		pb(stack_a, stack_b);
}

typedef struct	s_cheapest {
	int	num;
	int	total_ops;
	int	move_id;  // 0:ra+rb, 1:rra+rrb, 2:ra+rrb, 3:rra+rb
} t_cheapest;

void	pb_until_three(t_stack **stack_a, t_stack **stack_b)
{
	t_stack		*tmp;
	t_cheapest	*candidate;

	while (count_nodes(stack_a) != 3)
	{
		find_cheapest_move();

	}
}

void	sort_stack(t_stack **stack_a)
{
	t_stack	*stack_b;
	int		nodes;

	(void)stack_b;
	stack_b = NULL;
	if (!*stack_a || !stack_a)
		return ;
	nodes = count_nodes(*stack_a);
	if (nodes == 2)
		ra(stack_a);
	else
	{
		// 1. push 2 numbers to b without checks
		push_two_unchecked(stack_a, &stack_b);
		// 2. find the lowest cost(cheapest number) to push next
		pb_until_three(stack_a, &stack_b);
		// 3. handle last three elements
		sort_three(stack_a);
		// 4. push back to a
		// 5. final arrangement
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
