/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phong <phong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:27:04 by phong             #+#    #+#             */
/*   Updated: 2025/04/07 13:41:11 by phong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool	ft_put_char(char c, size_t *count)
{
	if (write(1, &c, 1) < 0)
		return (false);
	(*count)++;
	return (true);
}

bool	ft_put_udec(unsigned int n, size_t *count)
{
	if (n >= 10)
		if (!ft_put_udec(n / 10, count))
			return (false);
	return (ft_put_char((n % 10) + 48, count));
}

bool	ft_put_str(char *str, size_t *count)
{
	if (!str)
	{
		write(1, "(null)", 6);
		return (false);
	}
	while (*str)
	{
		if (!ft_put_char(*str, count))
			return (false);
		str++;
	}
	return (true);
}

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

bool	ft_put_ptr(void *address, size_t *count, bool is_first_call)
{
	char			digit;
	unsigned long	nbr;

	nbr = (unsigned long)address;
	if (is_first_call)
	{
		if (address == 0 || !ft_put_str("0x", count))
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

bool	check(va_list params, char c, size_t *count)
{
	bool	check;

	if (c == 'c')
		check = ft_put_char(va_arg(params, int), count);
	else if (c == 's')
		check = ft_put_str(va_arg(params, char *), count);
	else if (c == 'p')
		check = ft_put_ptr(va_arg(params, void *), count, true);
	else if (c == 'd' || c == 'i')
		check = ft_put_dec(va_arg(params, int), count);
	else if (c == 'u')
		check = ft_put_udec(va_arg(params, unsigned int), count);
	else if (c == 'x' || c == 'X')
		check = ft_put_hex(va_arg(params, int), count, c);
	else if (c == '%')
		check = ft_put_char('%', count);
	return (check);
}

int	ft_printf(const char *format, ...)
{
	size_t	count;
	va_list	params;

	count = 0;
	va_start(params, format);
	if (!(*format))
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			if (!check(params, *(format + 1), &count))
				return (va_end(params), -1);
			format += 2;
			continue ;
		}
		if (!ft_put_char(*format, &count))
			return (va_end(params), -1);
		format++;
	}
	va_end(params);
	return (count);
}

int	main(void)
{
	int	value = 0;
	ft_printf("=========================\n");
	ft_printf("My function\n");
	int check = ft_printf("pointer: %p, %%, %p\n", &check, 0);
	ft_printf("%i\n", check);

	printf("\n");

	printf("Original function\n");
	check = printf("pointer: %p, %%\n", &check);
	printf("%i\n", check);

	ft_printf("=========================\n");
	ft_printf("My function\n");
	check = ft_printf("hexadecimal: %x, %X\n", 1407268, 15);
	ft_printf("%i\n", check);

	printf("\n");

	printf("Original function\n");
	check = printf("hexadecimal: %x, %X\n", 1407268, 15);
	printf("%i\n", check);

	ft_printf("=========================\n");
	ft_printf("My function\n");
	check = ft_printf("decimal: %d, %i, %u\n", -255, -255, 255);
	ft_printf("%i\n", check);

	printf("\n");

	printf("Original function\n");
	check = printf("decimal: %d, %i, %u\n", -255, -255, 255);
	printf("%i\n", check);

	ft_printf("=========================\n");
	ft_printf("My function\n");
	check = ft_printf("Hello %c, %s\n", 'P', NULL);
	ft_printf("%i\n", check);

	printf("\n");

	printf("Original function\n");
	check = printf("Hello %c, %s\n", 'P', "its nice to meet you");
	printf("%i\n", check);

	ft_printf("=========================\n");
	printf("%x\n", -1);
	return (0);
}
