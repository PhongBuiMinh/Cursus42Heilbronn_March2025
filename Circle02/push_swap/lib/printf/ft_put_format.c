/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:53:45 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/08 17:54:48 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool	ft_put_dec(int n, size_t *count)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		if (!ft_put_char('-', count))
			return (false);
		nbr = -nbr;
	}
	if (nbr >= 10)
		if (!ft_put_dec(nbr / 10, count))
			return (false);
	return (ft_put_char((nbr % 10) + 48, count));
}

bool	ft_put_udec(unsigned int n, size_t *count)
{
	if (n >= 10)
		if (!ft_put_udec(n / 10, count))
			return (false);
	return (ft_put_char((n % 10) + 48, count));
}

bool	ft_put_hex(unsigned int nbr, size_t *count, char cap)
{
	char	digit;

	if (nbr >= 16)
		if (!ft_put_hex(nbr / 16, count, cap))
			return (false);
	digit = nbr % 16;
	if (digit < 10)
		digit += 48;
	else if (cap == 'X')
		digit += 65 - 10;
	else if (cap == 'x')
		digit += 97 - 10;
	return (ft_put_char(digit, count));
}

bool	ft_put_str(char *str, size_t *count)
{
	if (!str)
	{
		if (!ft_put_str("(null)", count))
			return (false);
		else
			return (true);
	}
	while (*str)
	{
		if (!ft_put_char(*str, count))
			return (false);
		str++;
	}
	return (true);
}

bool	ft_put_ptr(void *address, size_t *count, bool is_first_call)
{
	char			digit;
	unsigned long	nbr;

	nbr = (unsigned long)address;
	if (is_first_call)
	{
		if (!ft_put_str("0x", count))
			return (false);
	}
	if (nbr >= 16)
		if (!ft_put_ptr((void *)(nbr / 16), count, false))
			return (false);
	digit = nbr % 16;
	if (digit < 10)
		digit += 48;
	else
		digit += 97 - 10;
	return (ft_put_char(digit, count));
}
