/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:01:42 by snpark            #+#    #+#             */
/*   Updated: 2021/07/16 16:33:49 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	key_event(int key, void *parm)
{
	t_mlx			*mlx;
	unsigned char	tmp;

	mlx = (t_mlx *)parm;
	if (key == 65289)
	{
		tmp = mlx->r;
		mlx->r = mlx->g;
		mlx->g = mlx->blue;
		mlx->blue = tmp;
		mandelbrot(*mlx);
	}
	if (key == 65364)
		zoom(mlx, 1, 0.5, 0.5);
	else if (key == 65362)
		zoom(mlx, -1, 0.5, 0.5);
	if (key == 53 || key == 65307)
	{
		mlx_destroy_window(mlx->ptr, mlx->win);
		mlx_destroy_image(mlx->ptr, mlx->img);
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
		exit(0);
	}
}

int	red_cross(int arg, void *parm)
{
	t_mlx	*mlx;

	mlx = parm;
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_image(mlx->ptr, mlx->img);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}
