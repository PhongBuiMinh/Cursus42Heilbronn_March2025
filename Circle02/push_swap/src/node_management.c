/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:31:37 by fbui-min          #+#    #+#             */
/*   Updated: 2025/07/27 13:31:37 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*create_node(int num)
{
	t_stack	*new_node;

	new_node = (t_stack *)malloc(sizeof(t_stack));
	if (!new_node)
		return (NULL);
	new_node->num = num;
	new_node->next = NULL;
	return (new_node);
}

void	free_stack(t_stack **stack)
{
	t_stack	*clear;

	while (*stack)
	{
		clear = *stack;
		*stack = (*stack)->next;
		free(clear);
	}
	free(*stack);
	*stack = NULL;
}

void	insert_node(t_stack **root, int num)
{
	t_stack	*new_node;

	if (!root)
		return ;
	new_node = create_node(num);
	if (!new_node)
	{
		free_stack(root);
		print_error(3);
	}
	new_node->next = *root;
	*root = new_node;
}
