#include "fractol.h"

float	map(int x, int max, float new_min, float new_max)
{
	float place;

	place = (((float)max * new_min) + (((float)new_max - new_min) * x))/ max;
	return (place);
}

void	mandelbrot(t_mlx mlx)
{
	int	x;
	int	y;
	float	ca;
	float	cb;
	float	a;
	float	b;
	float	aa;
	float	bb;
	int	n;
	int	i;
	unsigned char r;
	unsigned char g;
	unsigned char blue;
	unsigned char *pixel_byte;
	float	ratio;

	ratio = (float)mlx.x / mlx.y;
	n = 0;//변수로 사용 가능
	x = 0;
	while (x < mlx.x)
	{
		y = 0;
		while (y < mlx.y)
		{
			pixel_byte = mlx.pix_str + mlx.bpp * x / 8 + mlx.len * y;
			r = 0;
			g = 0;
			blue = 0;
			ca = map(x, mlx.x, -2 * ratio , 2 * ratio);//뒤에 두 값도 변수로 사용 가능
			cb = map(y, mlx.y, -2, 2);
			a = ca;
			b = cb;
			i = 0;
			while (i < n)
			{
				aa = pow(a, 2) - pow(b, 2) + ca;//승수도 변수로 사용 가능
				bb = 2 * a * b + cb;
				a = aa;
				b = bb;
				i++;
			}
			if (pow(a, 2) + pow(b, 2) <= 4)
			{
				r = 255;
				g = 255;
				blue = 255;
			}
			pixel_byte[0] = r;
			pixel_byte[1] = g;
			pixel_byte[2] = blue;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
}
