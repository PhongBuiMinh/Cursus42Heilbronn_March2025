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

void	set_pixel(t_context ctx, int x, int y, int iter)
{
	char	*pixel;
	int		red;
	int		green;
	int		blue;
	double	t;
	double	factor;

	pixel = ctx.im.data + (y * ctx.im.size_line + x * (ctx.im.bpp / 8));
	if (iter == ctx.fr.max_iter)
	{
		*(unsigned int *)pixel = 0x000000;
		return ;
	}
	t = (double)iter / ctx.fr.max_iter;
	factor = (1 - t) * t * 255;
	red = clamp((int)(9 * factor));
	green = clamp((int)(15 * factor));
	blue = clamp((int)(8.5 * factor));
	*(unsigned int *)pixel = red << 16 | green << 8 | blue;
}

void	render_fractal_image(t_context ctx)
{
	int	iter;
	int	x;
	int	y;

	y = -1;
	while (++y < ctx.rd.height)
	{
		x = -1;
		while (++x < ctx.rd.width)
		{
			if (ctx.fr.type == 'm')
				iter = compute_mandelbrot(x, y, ctx.rd, ctx.fr);
			else if (ctx.fr.type == 'j')
				iter = compute_julia(x, y, ctx.rd, ctx.fr);
			set_pixel(ctx, x, y, iter);
		}
	}
	mlx_put_image_to_window(
		ctx.rd.mlx_ptr, ctx.rd.win_ptr, ctx.im.ptr,
		0, 0
	);
}

int	main(int argc, char **argv)
{
	t_context	ctx;

	input_validation(argc, argv, &ctx.fr);
	init_render(&ctx);
	init_img(&ctx);
	init_fractal(&ctx.fr);
	render_fractal_image(ctx);
	mlx_hook(ctx.rd.win_ptr, 17, 0, exit_fractal, &ctx);
	mlx_key_hook(ctx.rd.win_ptr, key_hook, &ctx);
	mlx_mouse_hook(ctx.rd.win_ptr, mouse_hook, &ctx);
	mlx_loop(ctx.rd.mlx_ptr);
}

// void	set_pixel(t_context ctx, int x, int y, int iter)
// {
	// t = (double)iter / ctx.fr.max_iter;
	// Parabolic Curve — Smooth fade-in/out
	// factor = (1 - t) * t * 255;
	// red = (int)(9 * factor);
	// green = (int)(15 * factor);
	// blue  = (int)(8.5 * factor);
	// Sine Wave Curve — Rhythmic pulse
	// factor = sin(t * M_PI) * 255;
	// red = (int)(factor);
	// green = (int)(factor * 0.5);
	// blue = (int)(255 - factor);
	// Exponential Fade — Glowing effect
	// factor = (1 - exp(-5 * t)) * 255;
	// red = (int)(factor * 0.8);
	// green = (int)(factor);
	// blue = (int)(factor * 0.6);
	// Try without
	// if (red > 255)
	// 	red = 255;
	// if (green > 255)
	// 	green = 255;
	// if (blue > 255)
	// 	blue = 255;
// }
