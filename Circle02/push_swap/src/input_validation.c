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

int	preprocess_atoi(const char *str, int i, int *sign)
{
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (!ft_isdigit(str[i + 1]))
			return (-1);
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

bool	ps_atoi(const char *str, int *result)
{
	long	num;
	int		sign;
	int		i;

	sign = 1;
	num = 0;
	i = preprocess_atoi(str, 0, &sign);
	if (i == -1)
		return (false);
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i++] - 48);
		if ((num > INT_MAX && sign == 1)
			|| (num > (long)INT_MAX + 1 && sign == -1))
			return (false);
	}
	if (str[i] != '\0')
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
