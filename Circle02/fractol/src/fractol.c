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

int	ft_strcasecmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (unsigned char)*s1 - (unsigned char)*s2;
}

void	print_error(int error_type)
{
	if (error_type == 1)
		ft_putstr_fd("Usage: ./fractol fractal\n", 2);
	if (error_type == 1)
		ft_putstr_fd("Available parameters: Julia/Mandelbrot\n", 1);
	if (error_type == 2)
		ft_putstr_fd("Error\n", 2);
	exit(error_type);
}

void	input_validation(int argc, char **argv, t_fractal *f)
{
	if (argc != 2)
		print_error(1);
	if (!ft_strcasecmp(argv[1], "julia"))
	{
		f->type = 'j';
		return ;
	}
	else if (!ft_strcasecmp(argv[1], "mandelbrot"))
	{
		f->type = 'm';
		return ;
	}
	print_error(1);
}

int	get_color(int i)
{
	int red;
	int green;
	int blue;

	if (i == MAX_ITER)
		return 0x000000;
	red = (int)(9 * (1 - (double)i / MAX_ITER) * (double)i / MAX_ITER * 255);
	green = (int)(15 * (1 - (double)i / MAX_ITER) * (double)i / MAX_ITER * 255);
	blue  = (int)(8.5 * (1 - (double)i / MAX_ITER) * (double)i / MAX_ITER * 255);
	// red = fmax(30, red);
	// green = fmax(30, green);
	// blue = fmax(30, blue);
	return (red << 16 | green << 8 | blue);
}

void	set_pixel(t_img img, int x, int y, int color)
{
	char	*pixel;

	pixel = img.data + (y * img.size_line + x * (img.bpp / 8));
	*(unsigned int *)pixel = color;
}

int	compute_mandelbrot(int x, int y, t_render render, t_fractal f)
{
	t_complex	z;
	t_complex	c;
	double	tmp_x;
	int		iter;

	z.x = 0;
	z.y = 0;
	// CENTERED MAPPING
	// c.x = ((double)x / render.width - 0.5) * 3.0 - 0.75;
	// c.y = ((double)y / render.height - 0.5) * 3.0;
	// OFFSET MAPPING
	// c.x = -2.0 + x * (3.0 / render.width);
	// c.y = -1.5 + y * (3.0 / render.height);
	// CENTERED + ZOOM
	c.x = ((double)x / render.width - 0.5) * (3.0 / f.zoom) + f.offset_x -0.75;
	c.y = ((double)y / render.height - 0.5) * (3.0 / f.zoom) + f.offset_y;
	iter = -1;
	while (++iter < MAX_ITER)
	{
		tmp_x = (z.x * z.x - z.y * z.y + c.x);
		z.y = (2 * z.x * z.y + c.y);
		z.x = tmp_x;
		if (z.x * z.x + z.y * z.y >= 4.0)
			break ;
	}
	return (iter);
}

int	compute_julia(int x, int y, t_render render, t_fractal f)
{
	t_complex	z;
	t_complex	c;
	double	tmp_x;
	int		iter;

	z.x = ((double)x / render.width - 0.5) * (3.0 / f.zoom) + f.offset_x;
	z.y = ((double)y / render.height - 0.5) * (3.0 / f.zoom) + f.offset_y;
	c.x = -0.8;
	c.y = 0.156;
	iter = -1;
	while (++iter < MAX_ITER)
	{
		tmp_x = ((z.x * z.x) - (z.y * z.y) + c.x);
		z.y = ((2 * z.x * z.y) + c.y);
		z.x = tmp_x;
		if (z.x * z.x + z.y * z.y >= 4.0)
			break ;
	}
	return (iter);
}

void	render_fractal_image(t_context ctx)
{
	int		iter;
	int		color;
	int		x, y;

	y = -1;
	while (++y < ctx.render.height)
	{
		x = 0;
		while (x < ctx.render.width)
		{
			if (ctx.f.type == 'm')
				iter = compute_mandelbrot(x, y, ctx.render, ctx.f);
			else
				iter = compute_julia(x, y, ctx.render, ctx.f);
			color = get_color(iter);
			set_pixel(ctx.img, x, y, color);
			x++;
		}
	}
	mlx_put_image_to_window(
		ctx.render.mlx_ptr, ctx.render.win_ptr, ctx.img.ptr,
		0, 0
	);
}

int	key_hook(int keycode, t_context *ctx)
{
	if (keycode == 65361 || keycode == 97) // Left arrow
		ctx->f.offset_x -= 0.1 / ctx->f.zoom;
	else if (keycode == 65363 || keycode == 100) // Right arrow
		ctx->f.offset_x += 0.1 / ctx->f.zoom;
	else if (keycode == 65362 || keycode == 119) // Up arrow
		ctx->f.offset_y -= 0.1 / ctx->f.zoom;
	else if (keycode == 65364 || keycode == 115) // Down arrow
		ctx->f.offset_y += 0.1 / ctx->f.zoom;
	else if (keycode == 65451 || keycode == 61) // '+' key
		ctx->f.zoom *= 1.2;
	else if ( keycode == 65453 || keycode == 45) // '-' key
		ctx->f.zoom /= 1.2;
	else if (keycode == 114)
		init_fractal(&ctx->f);
	else if (keycode == 65307)
		exit(0);
	else if (keycode == 111)
		ctx->f.max_iter -= 50;
	else if (keycode == 112)
		ctx->f.max_iter += 50;
	printf("Keycode: %d, Iter: %d\n", keycode, ctx->f.max_iter);
	render_fractal_image(*ctx);
	return (0);
}

void	free_render() {}

int	main(int argc, char **argv)
{
	t_context	ctx;

	input_validation(argc, argv, &ctx.f);
	init_render(&ctx.render);
	init_img(ctx.render, &ctx.img);
	init_fractal(&ctx.f);
	mlx_key_hook(ctx.render.win_ptr, key_hook, &ctx);
	// mlx_hook(ctx.render.win_ptr, 2, 1L << 0, key_hook, &ctx); // 2 = KeyPress
	render_fractal_image(ctx);
	mlx_loop(ctx.render.mlx_ptr);
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

// int get_color(int i)
// {
//     if (i == MAX_ITER)
//         return 0x000000; // black

//     int shade = (int)(255.0 * i / MAX_ITER);
//     return (shade << 16 | shade << 8 | shade); // grayscale
// }
