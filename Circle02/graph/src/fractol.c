#include "../lib/minilibx-linux/mlx.h"
#include "../lib/libft/libft.h"
#include <stdlib.h>

#define WIDTH 1400
#define HEIGHT 700

int	ft_strcasecmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (ft_tolower(*s1) != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

void	print_error(int error_type)
{
	if (error_type == 1)
		ft_putstr_fd("Usage: ./fractol [Julia/Mandelbrot]\n", 2);
	if (error_type == 2)
		ft_putstr_fd("Error\n", 2);
	exit(error_type);
}

int	input_validation(int argc, char **argv)
{
	if (argc != 2)
		print_error(1);
	if (ft_strcasecmp(argv[1], "julia") == 0)
		return (0);
	else if (ft_strcasecmp(argv[1], "mandelbrot") == 0)
		return (1);
	return (-1);
}
#define MAX_ITER 1000

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

void	render_fractal_image(void)
{
	t_complex	z;
	t_complex	c;
	int	i;

	// Zn+1 = Z^2 + C
	// Z0 = 0
	// n ->
	double	tmp_r;
	int		x, y;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			z.i = 0;
			z.r = 0;
			i = -1;
			c.r = -2.0 + (x / (double)WIDTH) * 3.0;
			c.i = -1.5 + (y / (double)HEIGHT) * 3.0;
			while (++i < MAX_ITER && z.r * z.r + z.i * z.i < 4.0)
			{
				tmp_r = ((z.r * z.r) - (z.i * z.i) + c.r);
				z.i = ((2 * z.r * z.i) + c.i);
				z.r = tmp_r;
			}
			int	color;
			if (i == MAX_ITER)
				color = 0x000000;
			else
				color = (255 * i / MAX_ITER) << 16;
			x++;
		}
		printf("\n");
		y++;
	}
}

int	main(int argc, char **argv)
{
	int		type;
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;

	type = input_validation(argc, argv);
	mlx = mlx_init();
	if (!mlx)
		exit (1);
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "fractol");
	// mlx_pixel_put(mlx, win, 10, 10, 0x00FF00);
	// mlx_string_put(mlx, win, 100, 100, 0x00FF00, "Hello world");
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img_data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	// render_fractal_image();
		// complex = map_pixel_to_complex(x,y)
		// inter = compute_fractal(complex)
		// color = get_color(iter)
		// set_pixel(img, x, y, color)
	int	y, x;
	y = -1;
	x = -1;
	while (++y < HEIGHT)
	{
		while (++x < WIDTH)
		{

		}
	}
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);
	(void)type;
	(void)img_data;
}
