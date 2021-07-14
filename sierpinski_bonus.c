/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinski_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:00:24 by snpark            #+#    #+#             */
/*   Updated: 2021/07/14 12:04:16 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	remove_triangle(t_mlx mlx, t_triangle tr, int n);//range of resolution will make efficient

void	remove_1(t_mlx mlx, t_triangle big, t_triangle small, int n)
{
	t_triangle left;

	left.p0.x = big.p0.x;
	left.p0.y = big.p0.y;
	left.p1.x = small.p0.x;
	left.p1.y = small.p0.y;
	left.p2.x = small.p2.x;
	left.p2.y = small.p2.y;
	left.o1.x = left.p1.x - left.p0.x;
	left.o1.y = left.p1.y - left.p0.y;
	left.o2.x = left.p2.x - left.p0.x;
	left.o2.y = left.p2.y - left.p0.y;
	remove_triangle(mlx, left, --n);
}

void	remove_2(t_mlx mlx, t_triangle big, t_triangle small, int n)
{
	t_triangle up;

	up.p0.x = small.p0.x;
	up.p0.y = small.p0.y;
	up.p1.x = big.p1.x;
	up.p1.y = big.p1.y;
	up.p2.x = small.p1.x;
	up.p2.y = small.p1.y;
	up.o1.x = up.p1.x - up.p0.x;
	up.o1.y = up.p1.y - up.p0.y;
	up.o2.x = up.p2.x - up.p0.x;
	up.o2.y = up.p2.y - up.p0.y;
	remove_triangle(mlx, up, --n);
}

void	remove_3(t_mlx mlx, t_triangle big, t_triangle small, int n)
{
	t_triangle right;

	right.p0.x = small.p2.x;
	right.p0.y = small.p2.y;
	right.p1.x = small.p1.x;
	right.p1.y = small.p1.y;
	right.p2.x = big.p2.x;
	right.p2.y = big.p2.y;
	right.o1.x = right.p1.x - right.p0.x;
	right.o1.y = right.p1.y - right.p0.y;
	right.o2.x = right.p2.x - right.p0.x;
	right.o2.y = right.p2.y - right.p0.y;
	remove_triangle(mlx, right, --n);
}
void	remove_triangle(t_mlx mlx, t_triangle tr, int n)//range of resolution will make efficient
{
	int	x;
	int	y;
	t_triangle new;
	float	a;
	float	b;
	unsigned char r;
	unsigned char g;
	unsigned char blue;
	t_vector o;
	float 	det;
	unsigned char *pixel_byte;

	if (!n)
		return ;
	new.p0.x = (tr.p0.x + tr.p1.x) / 2;
	new.p0.y = (tr.p0.y + tr.p1.y) / 2;
	new.p1.x = (tr.p1.x + tr.p2.x) / 2;
	new.p1.y = (tr.p1.y + tr.p2.y) / 2;
	new.p2.x = (tr.p2.x + tr.p0.x) / 2;
	new.p2.y = (tr.p2.y + tr.p0.y) / 2;
	new.o1.x = new.p1.x - new.p0.x;
	new.o1.y = new.p1.y - new.p0.y;
	new.o2.x = new.p2.x - new.p0.x;
	new.o2.y = new.p2.y - new.p0.y;
	x = 0;
	det = (new.o1.x * new.o2.y - new.o2.x * new.o1.y);
	r = 0;
	g = 0;
	blue = 0;
	while (x < mlx.x)
	{
		y = 0;
		while (y < mlx.y)
		{
			pixel_byte = mlx.pix_str + mlx.bpp * x / 8 + mlx.len * y;
			o.x = map(x, mlx.x, mlx.x_min, mlx.x_max) - new.p0.x;
			o.y = -1 * map(y, mlx.y, mlx.y_min, mlx.y_max) - new.p0.y;
			a = (o.x * new.o2.y - o.y * new.o2.x) / det;
			b = (new.o1.x * o.y - o.x * new.o1.y) / det;
			if (det && a >= 0.0 && b >= 0.0 && a + b <= 1.0)
				put_color(pixel_byte, r, g, blue);
			y++;
		}
		x++;
	}
	remove_1(mlx, tr, new, n);
	remove_2(mlx, tr, new, n);
	remove_3(mlx, tr, new, n);
}

void	draw_triangle(t_mlx mlx, t_triangle tr, int n)
{
	int	x;
	int	y;
	float	a;
	float	b;
	t_vector o;
	float	det;
	unsigned char r;
	unsigned char g;
	unsigned char blue;
	unsigned char *pixel_byte;

	x = 0;
	det = (tr.o1.x * tr.o2.y - tr.o2.x * tr.o1.y);
	while (x < mlx.x)
	{
		y = 0;
		while (y < mlx.y)
		{
			r = 0;
			g = 0;
			blue = 0;
			pixel_byte = mlx.pix_str + mlx.bpp * x / 8 + mlx.len * y;
			o.x = map(x, mlx.x, mlx.x_min, mlx.x_max) - tr.p0.x;
			o.y = -1 * map(y, mlx.y, mlx.y_min, mlx.y_max) - tr.p0.y;
			a = (o.x * tr.o2.y - o.y * tr.o2.x) / det;
			b = (tr.o1.x * o.y - o.x * tr.o1.y) / det;
			if (det && a >= 0.0 && b >= 0.0 && a + b <= 1.0)
			{
				r = 255;
				g = 255;
				blue = 255;
			}
			put_color(pixel_byte, r, g, blue);
			y++;
		}
		x++;
	}
	remove_triangle(mlx, tr, n);
	mlx_put_image_to_window(mlx.ptr, mlx.win,mlx.img, 0, 0);
}	
