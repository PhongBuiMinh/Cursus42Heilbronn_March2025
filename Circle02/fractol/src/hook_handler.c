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

int	mouse_hook(int button, t_context *ctx)
{
	// (void)x;
	// (void)y;

	if (button == 4)
		ctx->fr.zoom *= 1.2;
	else if (button == 5)
		ctx->fr.zoom /= 1.2;
	render_fractal_image(*ctx);
	return (0);
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
	else if ( keycode == KEY_MINUS || keycode == MINUS)
		ctx->fr.zoom /= 1.2;
	else if (keycode == R)
		init_fractal(&ctx->fr);
	else if (keycode == KEY_ESC || keycode == ESC)
		exit(0);
	else if (keycode == 91)
		ctx->fr.max_iter -= 50;
	else if (keycode == 93)
		ctx->fr.max_iter += 50;
	else if (keycode == 106)
	{
		ctx->fr.c.x = ((double)rand() / RAND_MAX - 0.5) * 3.0;
		ctx->fr.c.y = ((double)rand() / RAND_MAX - 0.5) * 3.0;
	}
	printf("Keycode: %d, Iter: %d\n", keycode, ctx->fr.max_iter);
	render_fractal_image(*ctx);
	return (0);
}

int	exit_fractal(t_context *ctx)
{
	(void) ctx;

	exit(0);
}
