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

void	print_error(int error_type)
{
	if (error_type == 0)
		ft_putstr_fd("Available parameters: Julia / Mandelbrot\n", 1);
	if (error_type == 1)
		ft_putstr_fd("Usage: ./fractol fractal (X) (Y)\n", 2);
	if (error_type == 2)
		ft_putstr_fd("Invalid arguments\n", 2);
	exit(error_type);
}

bool	ft_atof(const char *str, double *res)
{
	int		sign;
	double	dec_pos;
	int		i;

	*res = 0.0;
	sign = 1;
	dec_pos = 0.1;
	i = preprocess_atof(str, 0, &sign);
	if (i == -1)
		return (false);
	while (str[i] >= '0' && str[i] <= '9')
		*res = (*res * 10) + (str[i++] - '0');
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		*res += (str[i] - '0') * dec_pos;
		dec_pos *= 0.1;
		i++;
	}
	*res *= sign;
	if (*res < -2.5 || *res > 2)
		return (false);
	return (true);
}

void	input_validation(int argc, char **argv, t_fractal *f)
{
	if (argc == 1)
		print_error(0);
	if (argc > 4)
		print_error(1);
	if (argc == 3)
		print_error(2);
	if (!ft_strcasecmp(argv[1], "julia"))
		f->type = 'j';
	else if (!ft_strcasecmp(argv[1], "mandelbrot"))
		f->type = 'm';
	else
		print_error(0);
	if (argc == 4)
	{
		if (!ft_atof(argv[2], &f->c.x) || !ft_atof(argv[3], &f->c.y))
			print_error(2);
	}
	else
	{
		f->c.x = NAN;
		f->c.y = NAN;
	}
}

// t_complex julia_presets[] = {
// 	{-0.8, 0.156},
// 	{0.285, 0.01},
// 	{-0.4, 0.6},
// 	{-0.70176, -0.3842},
// 	{0.355, 0.355},
// 	{-0.835, -0.2321}
// };
