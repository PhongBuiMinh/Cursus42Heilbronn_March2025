#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

# include <stdio.h>
# include "../libft/libft.h"
# include "../printf/ft_printf.h"
# include <limits.h>

typedef struct s_stack
{
	int				num;
	int				index;
	struct s_stack	*next;
} t_stack;

// linked_list
t_stack		*create_node(int num);
void		insert_node(t_stack **root, int num);
t_stack		*last_node(t_stack *stack);
void		free_stack(t_stack **lst);
int			count_nodes(t_stack *stack);
int			find_max(t_stack *stack_a);
int			find_min(t_stack *stack);
int			stack_size(t_stack *stack);

// stack commands
void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);
void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);
void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);
void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);

// stack operations
void	push(t_stack **src, t_stack **dst);
void	swap(t_stack **stack);
void	rotate(t_stack **stack);
void	reverse_rotate(t_stack **stack);

bool	ps_atoi(const char *str, int *result);
bool	has_duplicate(t_stack *root, int num);
void	print_error(int error);
void	display_stack(t_stack *stack, char *message);
void	process_input(t_stack **stack_a, int argc, char **argv);

#endif
