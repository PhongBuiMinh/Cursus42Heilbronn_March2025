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

void	pa(t_stack **a, t_stack **b)
{
	push(b, a);
}

void	pb(t_stack **a, t_stack **b)
{
	push(a, b);
}
