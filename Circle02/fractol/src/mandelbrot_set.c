#include <stdio.h>

#define HEIGHT 10
#define WIDTH 10
#define MAX_ITER 1000

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

int	main(void)
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
				// printf("Pixel(%i, %i)\n", x, y);
				// printf("C(%f, %f)\n", c.r, c.i);
				// printf("Z%i = (%f, %f)\n", i, z.r, z.i);
			}
			if (i == MAX_ITER)
				printf("BLACK  ");
			else if (i < MAX_ITER / 2)
				printf("MEDIUM ");
			else
				printf("DARK   ");
			// printf("%i of %i\n\n", i, MAX_ITER);
			x++;
		}
		printf("\n");
		y++;
	}
}

//🧠 Fractal Rendering Logic
// 1. Map each pixel to a complex number C
// 	The screen is a 2D grid of pixels.
// 	Each pixel corresponds to a complex number C = (c.r, c.i) in the complex plane.
// 	For example, the left edge might be -2.0, the right edge 1.0, and the vertical range -1.5 to 1.5.

// 2. Initialize Z = 0
// 	For Mandelbrot sets, you always start with Z₀ = 0.

// 3. Iterate: Zₙ₊₁ = Zₙ² + C
// 	Repeat until either:
// 		|Z| > 2 (it escapes), or
// 		You hit a max iteration count (e.g. 1000)

// 4. Color the pixel based on how fast it escapes
// 	Fewer iterations = faster escape = brighter color
// 	More iterations = slower escape = darker color
// 	If it never escapes, color it black (or deep blue, etc.)
