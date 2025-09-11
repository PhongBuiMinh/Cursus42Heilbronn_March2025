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

int	mouse_hook(int button, int x, int y, t_context *ctx)
{
	(void)x;
	(void)y;
	if (button == 4)
		ctx->fr.zoom *= 1.2;
	else if (button == 5)
		ctx->fr.zoom /= 1.2;
	render_fractal_image(*ctx);
	return (0);
}

void	handle_zoom(int keycode, t_fractal *fr)
{
	if (keycode == LEFT_BRACKET)
	{
		if (fr->max_iter > 50)
			fr->max_iter -= 50;
	}
	else if (keycode == RIGHT_BRACKET)
	{
		if (fr->max_iter < 2000)
			fr->max_iter += 50;
	}
}

int	key_hook(int keycode, t_context *ctx)
{
	if (keycode == LEFT_ARROW || keycode == A)
		ctx->fr.offset_x -= 0.1 / ctx->fr.zoom;
	else if (keycode == RIGHT_ARROW || keycode == D)
		ctx->fr.offset_x += 0.1 / ctx->fr.zoom;
	else if (keycode == UP_ARROW || keycode == W)
		ctx->fr.offset_y -= 0.1 / ctx->fr.zoom;
	else if (keycode == DOWN_ARROW || keycode == S)
		ctx->fr.offset_y += 0.1 / ctx->fr.zoom;
	else if (keycode == KEY_PLUS || keycode == PLUS)
		ctx->fr.zoom *= 1.2;
	else if (keycode == KEY_MINUS || keycode == MINUS)
		ctx->fr.zoom /= 1.2;
	else if (keycode == R)
		init_fractal(&ctx->fr);
	else if (keycode == KEY_ESC || keycode == ESC)
		exit(0);
	else if (keycode == LEFT_BRACKET || RIGHT_BRACKET == 93)
		handle_zoom(keycode, &ctx->fr);
	render_fractal_image(*ctx);
	return (0);
}

int	exit_fractal(t_context *ctx)
{
	if (ctx->im.ptr)
		mlx_destroy_image(ctx->rd.mlx_ptr, ctx->im.ptr);
	if (ctx->rd.win_ptr)
		mlx_destroy_window(ctx->rd.mlx_ptr, ctx->rd.win_ptr);
	if (ctx->rd.mlx_ptr)
	{
		mlx_destroy_display(ctx->rd.mlx_ptr);
		free(ctx->rd.mlx_ptr);
	}
	exit(0);
}
