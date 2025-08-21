/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:31:29 by fbui-min          #+#    #+#             */
/*   Updated: 2025/07/27 13:31:29 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	ps_atoi(const char *str, int *result)
{
	long	num;
	int		sign;
	int		i;

	sign = 1;
	num = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '-')
			return (false);
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
		num = (num * 10) + (str[i++] - 48);
	if (str[i] != '\0' || (num > INT_MAX && sign == 1)
		|| (num < INT_MIN && sign == -1))
		return (false);
	*result = num * sign;
	return (true);
}

bool	has_duplicate(t_stack *root, int num)
{
	t_stack	*current;

	current = root;
	while (current)
	{
		if (current->num == num)
			return (true);
		current = current->next;
	}
	return (false);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	fill_stack(t_stack **stack_a, int argc, char **arr)
{
	int	i;
	int	num;

	i = 0;
	while (arr[i])
		i++;
	while (--i > 0)
	{
		if (!ps_atoi(arr[i], &num) || has_duplicate(*stack_a, num))
		{
			if (argc == 2)
				free_split(arr);
			free_stack(stack_a);
			print_error(2);
		}
		insert_node(stack_a, num);
	}
	if (argc == 2)
		free_split(arr);
}

void	process_input(t_stack **stack_a, int argc, char **argv)
{
	char	**arr;

	if (argc <= 1)
		print_error(1);
	if (argc == 2)
		arr = ft_split(argv[1], ' ');
	else
		arr = argv + 1;
	if (!arr || !arr[0])
		print_error(2);
	fill_stack(stack_a, argc, arr);
}
