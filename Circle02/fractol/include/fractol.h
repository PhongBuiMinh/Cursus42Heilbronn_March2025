/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:34:27 by fbui-min          #+#    #+#             */
/*   Updated: 2025/09/11 17:16:09 by fbui-min         ###   ########.fr       */
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

// WINDOW
# define WIDTH 350
# define HEIGHT 250
# define MAX_ITER 100

// KEYCODE
# define R 114
# define ESC 27
# define KEY_ESC 65307
# define PLUS 61
# define MINUS 45
# define KEY_PLUS 65451
# define KEY_MINUS 65453
# define LEFT_BRACKET 91
# define RIGHT_BRACKET 93
# define A 97
# define D 100
# define W 119
# define S 115
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define UP_ARROW 65362
# define DOWN_ARROW 65364

typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_render
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
}	t_render;

typedef struct s_img
{
	void	*ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_fractal
{
	double		zoom;
	double		offset_x;
	double		offset_y;
	int			max_iter;
	char		type;
	t_complex	c;
}	t_fractal;

typedef struct s_context
{
	t_render	rd;
	t_img		im;
	t_fractal	fr;
}	t_context;

void	init_img(t_context *ctx);
void	init_render(t_context *ctx);
void	init_fractal(t_fractal *f);

void	input_validation(int argc, char **argv, t_fractal *f);

int		mouse_hook(int button, int x, int y, t_context *ctx);
int		key_hook(int keycode, t_context *ctx);
int		exit_fractal(t_context *ctx);

int		compute_mandelbrot(int x, int y, t_render rd, t_fractal fr);
int		compute_julia(int x, int y, t_render rd, t_fractal fr);
void	render_fractal_image(t_context ctx);

int		preprocess_atof(const char *str, int i, int *sign);
int		ft_strcasecmp(char *s1, char *s2);
int		clamp(int intensity);

#endif
