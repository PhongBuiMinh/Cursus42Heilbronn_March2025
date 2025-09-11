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

void	init_render(t_context *ctx)
{
	ctx->rd.width = WIDTH;
	ctx->rd.height = HEIGHT;
	ctx->rd.mlx_ptr = mlx_init();
	ctx->rd.win_ptr = mlx_new_window(
			ctx->rd.mlx_ptr,
			ctx->rd.width,
			ctx->rd.height,
			"Fract-ol"
			);
	if (!ctx->rd.mlx_ptr || !ctx->rd.win_ptr)
		exit_fractal(ctx);
}

void	init_img(t_context *ctx)
{
	ctx->im.ptr = mlx_new_image(
			ctx->rd.mlx_ptr,
			ctx->rd.width,
			ctx->rd.height
			);
	if (!ctx->im.ptr)
		exit_fractal(ctx);
	ctx->im.data = mlx_get_data_addr(
			ctx->im.ptr,
			&ctx->im.bpp,
			&ctx->im.size_line,
			&ctx->im.endian
			);
}

void	init_fractal(t_fractal *f)
{
	f->zoom = 1.0;
	f->offset_x = 0.0;
	f->offset_y = 0.0;
	f->max_iter = MAX_ITER;
	if (isnan(f->c.x))
		f->c.x = -0.8;
	if (isnan(f->c.y))
		f->c.y = 0.156;
}
