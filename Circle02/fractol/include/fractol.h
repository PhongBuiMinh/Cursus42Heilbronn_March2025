/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:34:27 by fbui-min          #+#    #+#             */
/*   Updated: 2025/09/01 16:37:27 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
// #include "../lib/minilibx-linux/mlx.h"

# define WIDTH 600
# define HEIGHT 500
# define MAX_ITER 250

# define ESC 27
# define KEY_ESC 65307
# define R 114
# define PLUS 61
# define MINUS 45
# define KEY_PLUS 65451
# define KEY_MINUS 65453
# define A 97
# define D 100
# define W 119
# define S 115
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define UP_ARROW 65362
# define DOWN_ARROW 65364

typedef struct	s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct	s_render
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
}	t_render;

typedef struct	s_img
{
	void	*ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct	s_fractal
{
	double		zoom;
	double		offset_x;
	double		offset_y;
	int			max_iter;
	char		type;
	t_complex	c;
}	t_fractal;

typedef struct	s_context
{
	t_render	rd;
	t_img		im;
	t_fractal	fr;
}	t_context;

void	init_img(t_render render, t_img *img);
void	init_render(t_render *render);
void	init_fractal(t_fractal *f);

void	input_validation(int argc, char **argv, t_fractal *f);

int		mouse_hook(int button, t_context *ctx);
int		key_hook(int keycode, t_context *ctx);
int		exit_fractal(t_context *ctx);

int	compute_mandelbrot(int x, int y, t_render rd, t_fractal fr);
int	compute_julia(int x, int y, t_render rd, t_fractal fr);

#endif
