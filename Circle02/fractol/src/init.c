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

void	init_render(t_render *render)
{
	render->width = WIDTH;
	render->height = HEIGHT;
	render->mlx_ptr = mlx_init();
	// Free; Destroy window and image
	if (!render->mlx_ptr)
		exit(1);
	render->win_ptr = mlx_new_window(
		render->mlx_ptr,
		render->width,
		render->height,
		"Fract-ol"
	);
}

void	init_img(t_render render, t_img *img)
{
	img->ptr = mlx_new_image(render.mlx_ptr, render.width, render.height);
	img->data = mlx_get_data_addr(
		img->ptr,
		&img->bpp,
		&img->size_line,
		&img->endian
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
