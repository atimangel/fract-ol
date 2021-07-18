/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:02:00 by snpark            #+#    #+#             */
/*   Updated: 2021/07/17 09:18:12 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

float	map(int x, int max, float new_min, float new_max)
{
	float	place;

	place = (((float)max * new_min) + (((float)new_max - new_min) * x))
		/ max;
	return (place);
}

void	put_color(char *pixel, char r, char g, char b)
{
	pixel[0] = b;
	pixel[1] = g;
	pixel[2] = r;
}

void	reset(t_mlx mlx, t_mandelbrot *man, int x, int y)
{
	man->pixel_byte = mlx.pix_str + mlx.bpp * x / 8 + mlx.len * y;
	man->r = 0;
	man->g = 0;
	man->blue = 0;
	man->ca = map(x, mlx.x, mlx.min * mlx.ratio, mlx.max * mlx.ratio);
	man->cb = -1 * map(y, mlx.y, mlx.min, mlx.max);
	man->a = mlx.a;
	man->b = mlx.b;
}

void	trans_color(t_mandelbrot *man, int i)
{
	man->r = (25 * 5 * i) % 255;
	man->g = (25 * 2 * i) % 255;
	man->b = (25 * 3 * i) % 255;
}
