/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:02:00 by snpark            #+#    #+#             */
/*   Updated: 2021/07/18 15:08:51 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia_iterative(t_mandelbrot *man, int n)
{
	int	i;

	i = 0;
	while(i < n)
	{
		if(pow(man->a, 2) + pow(man->b, 2) > 4)
			break ;
		man->aa = pow(man->a, 2) - pow(man->b, 2) + man->ca;
		man->bb = 2 * man->a * man->b + man->cb;
		man->a = man->aa;
		man->b = man->bb;
		i++;
	}
	return (i);
}

void	jul_reset(t_mlx mlx, t_mandelbrot *man, int x, int y)
{
	man->pixel_byte = mlx.pix_str + mlx.bpp * x / 8 + mlx.len * y;
	man->r = 0;
	man->g = 0;
	man->blue = 0;
	man->a = map(x, mlx.x, mlx.min * mlx.ratio, mlx.max * mlx.ratio);
	man->b = -1 * map(y, mlx.y, mlx.min, mlx.max);
}

void	julia(t_mlx mlx)
{
	int				x;
	int				y;
	int				i;
	t_mandelbrot	man;

	x = 0;
	man.ca = mlx.a;
	man.cb = mlx.b;
	while (x < mlx.x)
	{
		y = 0;
		while (y < mlx.y)
		{
			jul_reset(mlx, &man, x, y);
			i = julia_iterative(&man, mlx.n);
			trans_color(&man, i);
			put_color(man.pixel_byte, man.r, man.g, man.blue);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
}
