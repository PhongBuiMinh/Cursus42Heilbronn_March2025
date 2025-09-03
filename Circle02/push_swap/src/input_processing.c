/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:31:29 by fbui-min          #+#    #+#             */
/*   Updated: 2025/08/23 15:09:43 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	fill_stack(t_stack **stack, int argc, char **arr)
{
	int	i;
	int	num;

	i = 0;
	while (arr[i])
		i++;
	while (--i >= 0)
	{
		if (!ps_atoi(arr[i], &num) || has_duplicate(*stack, num))
		{
			if (argc == 2)
				free_split(arr);
			free_stack(stack);
			print_error(2);
		}
		insert_node(stack, num);
	}
	if (argc == 2)
		free_split(arr);
}

void	process_input(t_stack **stack, int argc, char **argv)
{
	char	**arr;

	if (argc == 1)
		exit(0);
	if (argc == 2)
		arr = ft_split(argv[1], ' ');
	else
		arr = argv + 1;
	if (!arr || !arr[0])
		print_error(2);
	fill_stack(stack, argc, arr);
}
