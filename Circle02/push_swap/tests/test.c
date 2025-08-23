#include <stdio.h>

#define SIZE 3

int	find_median(int num[])
{
	int	count_smaller;
	int	median;
	int	i;
	int j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		count_smaller = 0;
		while (j < SIZE)
		{
			if (num[j] < num[i])
				count_smaller++;
			j++;
		}
		if (count_smaller == SIZE / 2)
		{
			median = num[i];
			break ;
		}
		i++;
	}
	return (median);
}

int	main(void)
{
	int	num[SIZE] = {9, 2, 5};
	printf("%d\n", find_median(num));
}

// void rotate_min_to_top(t_stack *s, void (*r)(), void (*rr)())
// {
// 	if (cost > 0) r(s, 1);	// ← Could be ra, rb, rc, etc.
// 	else rr(s, 1);			// ← Could be rra, rrb, rrc, etc.
// }

// // For stack A
// rotate_min_to_top(stack_a, ra, rra);

// // For stack B
// rotate_min_to_top(stack_b, rb, rrb);

// // For any other stack
// rotate_min_to_top(stack_c, rc, rrc);

void	process_input(t_stack **stack_a, int argc, char **argv)
{
	int		num;
	char	**split_argv;
	int		i;

	if (argc <= 1)
		print_error(1);
	if (argc == 2)
	{
		split_argv = ft_split(argv[1], ' ');
		if (!split_argv || !split_argv[0])
			print_error(2);
		i = 0;
		while (split_argv[i])
		{
			if (!ps_atoi(split_argv[i], &num) || has_duplicate(*stack_a, num))
			{
				free_split(split_argv);  // You need to create this function
				free_stack(stack_a);
				print_error(2);
			}
			insert_node(stack_a, num);
			i++;
		}
		free_split(split_argv);  // Free the allocated memory
		return;
	}
	while (--argc > 0)
	{
		if (!ps_atoi(argv[argc], &num) || has_duplicate(*stack_a, num))
		{
			free_stack(stack_a);
			print_error(2);
		}
		insert_node(stack_a, num);
	}
}

// (argc == 2) && (free_split(arr), 0);

// Function to free the split array
void	free_split(char **split_arr)
{
	int	i;

	if (!split_arr)
		return;

	i = 0;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}

Overall Strategy
This function implements an optimized transfer algorithm that minimizes the number of operations by:

Choosing the most efficient element to transfer next
Combining rotations when possible
Preparing both stacks before each transfer
Ensuring elements are placed in optimal positions in the destination stack
