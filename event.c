/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:01:42 by snpark            #+#    #+#             */
/*   Updated: 2021/07/24 14:31:06 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	escape(int key, void *parm)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)parm;
	if (key == 53 || key == 65307)
	{
		mlx_destroy_window(mlx->ptr, mlx->win);
		mlx_destroy_image(mlx->ptr, mlx->img);
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
		exit(0);
	}
}

int	red_cross(void *parm)
{
	t_mlx	*mlx;

	mlx = parm;
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_image(mlx->ptr, mlx->img);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}
