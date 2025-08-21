/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:31:41 by fbui-min          #+#    #+#             */
/*   Updated: 2025/07/27 13:31:41 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_stack **src, t_stack **dst)
{
	t_stack	*node_to_push;

	if (!*src || !src || !dst)
		return ;
	node_to_push = *src;
	*src = node_to_push->next;
	node_to_push->next = *dst;
	*dst = node_to_push;
	}

void	pa(t_stack **b, t_stack **a)
{
	push(b, a);
}

void	pb(t_stack **a, t_stack **b)
{
	push(a, b);
}
