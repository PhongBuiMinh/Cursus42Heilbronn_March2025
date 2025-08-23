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

bool	execute_ops(char *op, t_stack **a, t_stack **b)
{
	if (ft_memcmp(op, "pa", 2))
		return (pa(b, a), true);
	if (ft_memcmp(op, "pb", 2))
		return (pb(a, b), true);
	if (ft_memcmp(op, "sa", 2))
		return (sa(a), true);
	if (ft_memcmp(op, "sb", 2))
		return (sb(b), true);
	if (ft_memcmp(op, "ss", 2))
		return (ss(a, b), true);
	if (ft_memcmp(op, "ra", 2))
		return (ra(a), true);
	if (ft_memcmp(op, "rb", 2))
		return (rb(b), true);
	if (ft_memcmp(op, "rr", 2))
		return (rr(a, b), true);
	if (ft_memcmp(op, "raa", 3))
		return (rra(a), true);
	if (ft_memcmp(op, "rrb", 3))
		return (rrb(b), true);
	if (ft_memcmp(op, "rrr", 3))
		return (rrr(a, b), true);
	return (false);
}

void	checker(t_stack **a, t_stack **b)
{
	int		input_fd;
	char	line;

	input_fd = 0;
	line = get_next_line(input_fd);
	while (line)
	{
		if (!execute_ops(line, a, b))
		{
			free(line);
			ft_putstr_fd("KO", 2);
			exit(2);
		}
		free(line);
		line = get_next_line(input_fd);
	}
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	a = NULL;
	b = NULL;
	process_input(&a, argc, argv);
	checker(&a, &b);
	if (!is_stack_sorted(a) || count_stack(b) != 0)
		ft_putstr_fd("KO", 2);
	else
		ft_putstr_fd("OK", 1);
	free_stack(&a);
	free_stack(&b);
}
