/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:02:00 by snpark            #+#    #+#             */
/*   Updated: 2021/07/12 18:46:28 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static int	mandelbrot_iterative(t_mandelbrot *man, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		man->aa = pow(man->a, 2) - pow(man->b, 2) + man->ca;
		man->bb = 2 * man->a * man->b + man->cb;
		if (pow(man->aa, 2) + pow(man->bb, 2) > 4)
			break ;
		man->a = man->aa;
		man->b = man->bb;
		i++;
	}
	return (i);
}

void	mandelbrot(t_mlx mlx)
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
			reset(mlx, &man, x, y);
			i = mandelbrot_iterative(&man, mlx.n);
			trans_color(mlx, &man, i);
			put_color(man.pixel_byte, man.r, man.g, man.blue);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
}
