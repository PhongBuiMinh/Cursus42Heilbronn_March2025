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

void	get_rgb(t_rgb *rgb, double t, int type)
{
	double	factor;

	if (type == 0)
	{
		factor = (1 - t) * t * 255;
		rgb->red = clamp((int)(9 * factor));
		rgb->green = clamp((int)(15 * factor));
		rgb->blue = clamp((int)(8.5 * factor));
	}
	else if (type == 1)
	{
		factor = sin(t * M_PI) * 255;
		rgb->red = (int)(factor);
		rgb->green = (int)(factor * 0.5);
		rgb->blue = (int)(255 - factor);
	}
	else
	{
		factor = (1 - exp(-5 * t)) * 255;
		rgb->red = (int)(factor * 0.8);
		rgb->green = (int)(factor);
		rgb->blue = (int)(factor * 0.6);
	}
}

void	set_pixel(t_context ctx, int x, int y, int iter)
{
	char	*pixel;
	t_rgb	rgb;
	double	t;

	pixel = ctx.im.data + (y * ctx.im.size_line + x * (ctx.im.bpp / 8));
	if (iter == ctx.fr.max_iter)
	{
		*(unsigned int *)pixel = 0x000000;
		return ;
	}
	t = (double)iter / ctx.fr.max_iter;
	get_rgb(&rgb, t, ctx.fr.color);
	*(unsigned int *)pixel = rgb.red << 16 | rgb.green << 8 | rgb.blue;
}
