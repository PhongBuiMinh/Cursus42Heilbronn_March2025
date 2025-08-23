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
