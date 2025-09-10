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
	double	t;
	double	factor;
	int		red;
	int		green;
	int		blue;

	pixel = ctx.im.data + (y * ctx.im.size_line + x * (ctx.im.bpp / 8));
	if (iter == ctx.fr.max_iter)
	{
		*(unsigned int *)pixel = 0x000000;
		return ;
	}
	t = (double)iter / ctx.fr.max_iter;
	factor = (1 - t) * t * 255;
	red = (int)(9 * factor);
	green = (int)(15 * factor);
	blue  = (int)(8.5 * factor);
	// red   = (int)(sin(0.016 * iter + 4) * 127 + 128);
	// green = (int)(sin(0.013 * iter + 2) * 127 + 128);
	// blue  = (int)(sin(0.01  * iter + 1) * 127 + 128);
	*(unsigned int *)pixel = red << 16 | green << 8 | blue;
}

void	free_render() {}

void	render_fractal_image(t_context ctx)
{
	int	iter;
	int	x;
	int	y;

	y = -1;
	while (++y < ctx.rd.height)
	{
		x = 0;
		while (x < ctx.rd.width)
		{
			if (ctx.fr.type == 'm')
				iter = compute_mandelbrot(x, y, ctx.rd, ctx.fr);
			else
				iter = compute_julia(x, y, ctx.rd, ctx.fr);
			set_pixel(ctx, x, y, iter);
			x++;
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
	init_render(&ctx.rd);
	init_img(ctx.rd, &ctx.im);
	init_fractal(&ctx.fr);
	mlx_hook(ctx.rd.win_ptr, 17, 0, exit_fractal, &ctx);
	mlx_key_hook(ctx.rd.win_ptr, key_hook, &ctx);
	mlx_mouse_hook(ctx.rd.win_ptr, mouse_hook, &ctx);
	render_fractal_image(ctx);
	mlx_loop(ctx.rd.mlx_ptr);
}

// int	get_color(int i)
// {
// 	int	color;

// 	if (i == MAX_ITER)
// 		color = 0x000000;
// 	else
// 		color = (255 * i / MAX_ITER) << 16;
// 	return (color);
// }

// int	get_color(int i)
// {
// 	int	red;
// 	int	green;
// 	int	blue;

// 	if (i == MAX_ITER)
// 		return (0x000000);
// 	red = 0;
// 	green = (int)(255 * i / MAX_ITER);
// 	blue = (int)(255 * (MAX_ITER - i) / MAX_ITER);
// 	return (red << 16 | green << 8 | blue);
// }

// void	set_pixel(t_context ctx, int x, int y, int iter)
// {
// 	// int shade = (int)(255.0 * iter / ctx.fr.max_iter);
// 	// char*pixel = ctx.im.data + (y * ctx.im.size_line + x * (ctx.im.bpp / 8));
// 	// *(unsigned int *)pixel = (shade << 16) | (shade << 8) | shade;

// 	// int red = (255 * iter / ctx.fr.max_iter);
// 	// int green = (255 * (ctx.fr.max_iter - iter) / ctx.fr.max_iter);
// 	// int blue = 128;
// 	// char*pixel = ctx.im.data + (y * ctx.im.size_line + x * (ctx.im.bpp / 8));
// 	// *(unsigned int *)pixel = (red << 16) | (green << 8) | blue;

// 	// int band = iter % 16;
// 	// char*pixel = ctx.im.data + (y * ctx.im.size_line + x * (ctx.im.bpp / 8));
// 	// *(unsigned int *)pixel = band * 0x111111;
// }
