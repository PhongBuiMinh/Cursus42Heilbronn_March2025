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
// #include "../lib/minilibx-linux/mlx.h"

# define WIDTH 600
# define HEIGHT 500
# define MAX_ITER 42

typedef struct	s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_render
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
	t_render	render;
	t_img		img;
	t_fractal	f;
}	t_context;

void	init_img(t_render render, t_img *img);
void	init_render(t_render *render);
void	init_fractal(t_fractal *f);

#endif
