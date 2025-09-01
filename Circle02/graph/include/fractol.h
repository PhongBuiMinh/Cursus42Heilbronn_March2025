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
// #include "../lib/minilibx-linux/mlx.h"

# define WIDTH 1400
# define HEIGHT 700
# define MAX_ITER 1000

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

#endif
