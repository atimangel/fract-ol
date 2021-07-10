#include "fractol.h"

float	map(int x, int max, float new_min, float new_max)
{
	float place;

	place = (((float)max * new_min) + (((float)new_max - new_min) * x))/ max;
	return (place);
}

void	put_color(unsigned char *pixel, unsigned char r, unsigned char g, unsigned char b)
{
	pixel[0] = r;
	pixel[1] = g;
	pixel[2] = b;
}

void	reset(t_mlx mlx, t_mandelbrot *man, int x, int y, float a, float b)
{
	man->pixel_byte = mlx.pix_str + mlx.bpp * x / 8 + mlx.len * y;
	man->r = 0;
	man->g = 0;
	man->blue = 0;
	man->ca = map(x, mlx.x, -2 * mlx.ratio, 2 * mlx.ratio);
	man->cb = map(y, mlx.y, -2, 2);
	man->a = a;
	man->b = b;
}

int	mandelbrot_iterative(t_mandelbrot *man, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		man->aa = pow(man->a, 2) - pow(man->b, 2) + man->ca;
		man->bb = 2 * man->a * man->b + man->cb;
		if (pow(man->aa, 2) + pow(man->bb, 2) > 4)
			break;
		man->a = man->aa;
		man->b = man->bb;
		i++;
	}
	return (i);
}

void	trans_color(t_mandelbrot *man, int i)
{
	if (pow(man->a, 2) + pow(man->b, 2) <= 4)
	{
		man->r = 60 * (i) % 255;
		man->g = 50 * (i) % 255;
		man->b = 70 * (i) % 255;
	}
}

void	mandelbrot(t_mlx mlx, int n, float a, float b)
{
	int		x;
	int		y;
	int		i;
	t_mandelbrot	man;

	x = 0;
	while (x < mlx.x)
	{
		y = 0;
		while (y < mlx.y)
		{
			reset(mlx, &man, x, y, a, b); 
			i = mandelbrot_iterative(&man, n);
			trans_color(&man, i);
			put_color(man.pixel_byte, man.r, man.g, man.blue);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
}
