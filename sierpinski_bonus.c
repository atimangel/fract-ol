/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinski_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:00:24 by snpark            #+#    #+#             */
/*   Updated: 2021/07/13 21:05:12 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

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
