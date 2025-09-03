/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:32:01 by fbui-min          #+#    #+#             */
/*   Updated: 2025/07/27 13:32:01 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <limits.h>
# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"

typedef struct s_stack
{
	int				num;
	struct s_stack	*next;
}	t_stack;

typedef struct s_cost_cal
{
	int	current_cost;
	int	lowest_cost;
	int	ca;
	int	cb;
}	t_cost_cal;

typedef struct s_stack_info
{
	int	a_pos;
	int	b_pos;
	int	size_a;
	int	size_b;
}	t_stack_info;

// LINKED LIST MANAGEMENT
t_stack		*create_node(int num);
void		free_stack(t_stack **stack);
void		insert_node(t_stack **root, int num);

t_stack		*last_node(t_stack *stack);
int			count_stack(t_stack *stack);
bool		has_n_nodes(t_stack *stack, int n);

int			find_max(t_stack *stack);
int			find_min(t_stack *stack);
int			find_min_pos(t_stack *stack);
int			find_pos(t_stack *stack, int num);
int			find_insert_pos(t_stack *stack, int num);

// STACK COMMANDS
void		pa(t_stack **b, t_stack **a);
void		pb(t_stack **a, t_stack **b);
void		sa(t_stack **a);
void		sb(t_stack **b);
void		ss(t_stack **a, t_stack **b);
void		ra(t_stack **a);
void		rb(t_stack **b);
void		rr(t_stack **a, t_stack **b);
void		rra(t_stack **a);
void		rrb(t_stack **b);
void		rrr(t_stack **a, t_stack **b);

// STACK OPERATIONS
void		push(t_stack **src, t_stack **dst);
void		swap(t_stack **stack);
void		rotate(t_stack **stack);
void		reverse_rotate(t_stack **stack);
void		single_rotation(t_stack **stack, int cost,
				void (*r)(t_stack **), void (*rr)(t_stack **));
void		double_rotation(int *cost_a, int *cost_b, t_stack **a, t_stack **b);
void		rotate_min_to_top(t_stack **stack,
				void (*r)(t_stack **), void (*rr)(t_stack **));

// INPUT / OUTPUT
void		process_input(t_stack **stack, int argc, char **argv);
bool		ps_atoi(const char *str, int *result);
bool		has_duplicate(t_stack *root, int num);

void		print_error(int error);
void		display_stack(t_stack *stack, char *message);

// ALGORITHM
void		find_cheapest_num(t_stack *a, t_stack *b, int *cost_a, int *cost_b);
void		push_back_to_a(t_stack **a, t_stack **b);
void		sort_three(t_stack **stack);
void		sort_stack(t_stack **a);

bool		is_stack_sorted(t_stack *stack);
int			get_median(t_stack *stack, int size);
int			cal_combined_cost(t_cost_cal cost, t_stack_info info);
int			cal_rotation_cost(int size, int index);
int			get_signed_rotations(int index, int size, int rotation_count);

#endif
