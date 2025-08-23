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

int	main(int argc, char **argv)
{
	t_stack	*a;

	a = NULL;
	process_input(&a, argc, argv);
	if (!is_stack_sorted(a))
		sort_stack(&a);
	display_stack(a, "Sorted stack");
	free_stack(&a);
}

// int	main(int argc, char **argv)
// {
// 	t_stack	*a;

// 	stack_a = NULL;
// 	process_input(&a, argc, argv);
// 	display(a, "Inputs received\n");
// 	sa(&a);
// 	display(a, "Swap\n");
// 	rotate(&a);
// 	display(a, "Rotate\n");
// 	reverse_rotate(&a);
// 	display(a, "Reverse rotate\n");
// }
