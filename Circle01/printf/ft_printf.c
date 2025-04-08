/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:25:54 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/08 17:53:40 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool	determine_format(va_list params, char c, size_t *count)
{
	bool	status;

	status = true;
	if (c == 'c')
		status = ft_put_char(va_arg(params, int), count);
	else if (c == 's')
		status = ft_put_str(va_arg(params, char *), count);
	else if (c == 'p')
		status = ft_put_ptr(va_arg(params, void *), count, true);
	else if (c == 'd' || c == 'i')
		status = ft_put_dec(va_arg(params, int), count);
	else if (c == 'u')
		status = ft_put_udec(va_arg(params, unsigned int), count);
	else if (c == 'x' || c == 'X')
		status = ft_put_hex(va_arg(params, int), count, c);
	else if (c == '%')
		status = ft_put_char('%', count);
	return (status);
}

int	ft_printf(const char *format, ...)
{
	size_t	count;
	va_list	params;

	count = 0;
	va_start(params, format);
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			if (!determine_format(params, *(format + 1), &count))
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

/*int	main(void)
{
	int	check = ft_printf("%s", (char *)NULL);
	ft_printf("%i\n", check);
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
}*/
