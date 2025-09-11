/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:04:34 by fbui-min          #+#    #+#             */
/*   Updated: 2025/09/01 16:04:34 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	clamp(int intensity)
{
	if (intensity > 250)
		return (255);
	return (intensity);
}

int	ft_strcasecmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	preprocess_atof(const char *str, int i, int *sign)
{
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
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
