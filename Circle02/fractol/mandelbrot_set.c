#include <stdio.h>

#define HEIGHT 10
#define WIDTH 10
#define MAX_ITER 1000

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

// z.x = ((double)x / render.width - 0.5) * 3.0;
// z.y = ((double)y / render.height - 0.5) * 3.0;
// z.x = -1.5 + x * (3.0 / render.width); // mapped_x
// z.y = -1.5 + y * (3.0 / render.height); // mapped_y
// z.x = ((double)x / render.width - 0.5) * (3.0 / f.zoom) + f.offset_x;
// z.y = ((double)y / render.height - 0.5) * (3.0 / f.zoom) + f.offset_y;

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

// mlx_pixel_put(mlx, win, 10, 10, 0x00FF00);
// mlx_string_put(mlx, win, 100, 100, 0x00FF00, "Hello world");

// Zn+1 = Z^2 + C
// Z0 = 0
// n ->

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

// 🧠 What Is Scaling in Fractals?
// You're drawing pixels on a screen (like 800×600), but the Mandelbrot set lives in a mathematical space — specifically, the complex plane from about −2 to +1 on the real axis, and −1.5 to +1.5 on the imaginary axis.
// So you need to map each pixel (x, y) to a complex number (r, i) in that space.

// 🔁 Mandelbrot vs Julia: Key Difference
// Mandelbrot Set: Each pixel maps to a complex number c, and you iterate z = z² + c starting from z = 0.
// Julia Set: You fix a complex number c (the parameter that defines the shape of the Julia set), and each pixel maps to an initial z, then you iterate z = z² + c.

// 🔍 Breakdown:
// x / render.width gives you a value from 0.0 to 1.0
// Subtracting 0.5 shifts that range to −0.5 to +0.5
// Multiplying by 3.0 stretches it to −1.5 to +1.5
