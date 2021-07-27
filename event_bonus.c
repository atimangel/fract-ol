/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:01:42 by snpark            #+#    #+#             */
/*   Updated: 2021/07/25 21:01:45 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static void	free_all(t_mlx mlx)
{
	mlx_destroy_window(mlx.ptr, mlx.win);
	mlx_destroy_image(mlx.ptr, mlx.img);
	mlx_destroy_display(mlx.ptr);
	free(mlx.ptr);
	if (mlx.flag == 's')
		free(mlx.tri);
	exit(0);
}

static void	move(t_mlx *mlx, char arrow)
{
	void	*img;
	float	x_len;
	float	y_len;

	x_len = (mlx->x_max - mlx->x_min) * 0.1;
	y_len = (mlx->y_max - mlx->y_min) * 0.1;
	if (arrow == 1 || arrow == 3)
	{
		mlx->y_max -= y_len / 2;
		mlx->y_min += y_len / 2;
		if (arrow == 3)
			mlx->x_min += x_len;
		else
			mlx->x_max -= x_len;
	}
	else if (arrow == 2 || arrow == 4)
	{
		mlx->x_max -= x_len / 2;
		mlx->x_min += x_len / 2;
		if (arrow == 2)
			mlx->y_max -= y_len;
		else
			mlx->y_min += y_len;
	}
	if (arrow >= 1 && arrow <= 4)
		new_img(mlx);
}

void	new_img(t_mlx *m)
{
	void	*img;

	img = m->img;
	m->img = mlx_new_image(m->ptr, m->x, m->y);
	m->pix_str = mlx_get_data_addr(m->img, &m->bpp, &m->len, &m->endian);
	make_fractal(m);
	mlx_destroy_image(m->ptr, img);
}

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
		make_fractal(mlx);
	}
	if (key == 65361)
		move(mlx, 1);
	else if (key == 65362)
		move(mlx, 2);
	else if (key == 65363)
		move(mlx, 3);
	else if (key == 65364)
		move(mlx, 4);
	if (key == 53 || key == 65307)
		free_all(*mlx);
}
/*
**LINUX UBUNTU KEY
**65361 left 65362 up 65363 right 65364 down
*/

int	red_cross(void *parm)
{
	free_all(*(t_mlx *)parm);
}
