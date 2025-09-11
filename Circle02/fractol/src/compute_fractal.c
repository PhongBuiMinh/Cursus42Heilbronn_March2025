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

int	compute_mandelbrot(int x, int y, t_render rd, t_fractal fr)
{
	t_complex	z;
	t_complex	c;
	double		tmp_x;
	int			iter;

	z.x = 0;
	z.y = 0;
	c.x = ((double)x / rd.width - 0.5)
			* (3.0 / fr.zoom) + fr.offset_x -0.75;
	c.y = ((double)y / rd.height - 0.5)
			* (3.0 / fr.zoom) + fr.offset_y;
	iter = -1;
	while (++iter < fr.max_iter)
	{
		tmp_x = (z.x * z.x - z.y * z.y) + c.x;
		z.y = (2 * z.x * z.y) + c.y;
		z.x = tmp_x;
		if (z.x * z.x + z.y * z.y >= 4.0)
			break ;
	}
	return (iter);
}

int	compute_julia(int x, int y, t_render rd, t_fractal fr)
{
	t_complex	z;
	t_complex	c;
	double		tmp_x;
	int			iter;

	z.x = ((double)x / rd.width - 0.5)
			* (3.0 / fr.zoom) + fr.offset_x;
	z.y = ((double)y / rd.height - 0.5)
			* (3.0 / fr.zoom) + fr.offset_y;
	c.x = fr.c.x;
	c.y = fr.c.y;
	iter = -1;
	while (++iter < fr.max_iter)
	{
		tmp_x = (z.x * z.x - z.y * z.y) + c.x;
		z.y = (2 * z.x * z.y) + c.y;
		z.x = tmp_x;
		if (z.x * z.x + z.y * z.y >= 4.0)
			break ;
	}
	return (iter);
}

// CENTERED MAPPING
// c.x = ((double)x / render.width - 0.5) * 3.0 - 0.75;
// c.y = ((double)y / render.height - 0.5) * 3.0;
// OFFSET MAPPING
// c.x = -2.0 + x * (3.0 / render.width);
// c.y = -1.5 + y * (3.0 / render.height);
// CENTERED + ZOOM
// c.x = ((double)x / rd.width - 0.5) * (3.0 / fr.zoom) + fr.offset_x -0.75;
// c.y = ((double)y / rd.height - 0.5) * (3.0 / fr.zoom) + fr.offset_y;
