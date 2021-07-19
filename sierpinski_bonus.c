/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinski_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:00:24 by snpark            #+#    #+#             */
/*   Updated: 2021/07/19 10:48:31 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"
void	set_new_tri(t_mlx *mlx, t_triangle tr, t_triangle *new)
{
	new->p0.x = (tr.p0.x + tr.p1.x) / 2;
	new->p0.y = (tr.p0.y + tr.p1.y) / 2;
	new->p1.x = (tr.p1.x + tr.p2.x) / 2;
	new->p1.y = (tr.p1.y + tr.p2.y) / 2;
	new->p2.x = (tr.p2.x + tr.p0.x) / 2;
	new->p2.y = (tr.p2.y + tr.p0.y) / 2;
	new->o1.x = new->p1.x - new->p0.x;
	new->o1.y = new->p1.y - new->p0.y;
	new->o2.x = new->p2.x - new->p0.x;
	new->o2.y = new->p2.y - new->p0.y;
	new->det = (new->o1.x * new->o2.y - new->o2.x * new->o1.y);
	mlx->r = 0;
	mlx->g = 0;
	mlx->blue = 0;
}

void	remove_triangle(t_mlx mlx, t_triangle tr)
{
	int			x;
	int			y;
	t_triangle	new;

	if (!mlx.n)
		return ;
	set_new_tri(&mlx, tr, &new);
	x = 0;
	while (x < mlx.x)
	{
		y = 0;
		while (y < mlx.y)
		{
			sir_reset(&mlx, &new, x, y);
			is_inside(&mlx, &new, 0);
			y++;
		}
		x++;
	}
	remove_1(mlx, tr, new);
	remove_2(mlx, tr, new);
	remove_3(mlx, tr, new);
}

void	sir_reset(t_mlx *mlx, t_triangle *tr, int x, int y)
{
	mlx->r = 0;
	mlx->g = 0;
	mlx->blue = 0;
	tr->pixel_byte = mlx->pix_str + mlx->bpp * x / 8 + mlx->len * y;
	if (tr->det)
	{
		tr->o.x = map(x, mlx->x, mlx->x_min, mlx->x_max) - tr->p0.x;
		tr->o.y = -1 * map(y, mlx->y, mlx->y_min, mlx->y_max) - tr->p0.y;
		mlx->a = (tr->o.x * tr->o2.y - tr->o.y * tr->o2.x) / tr->det;
		mlx->b = (tr->o1.x * tr->o.y - tr->o.x * tr->o1.y) / tr->det;
	}
}

void	is_inside(t_mlx *mlx, t_triangle *tr, char flag)
{
	float	a;
	float	b;

	a = mlx->a;
	b = mlx->b;
	if (tr->det && a >= 0.0 && b >= 0.0 && a + b <= 1.0)
	{
		if (flag)
		{
			mlx->r = 255;
			mlx->g = 255;
			mlx->blue = 255;
		}
		else if (!flag)
			put_color(tr->pixel_byte, mlx->r, mlx->g, mlx->blue);
	}
}

void	draw_triangle(t_mlx mlx, t_triangle tr)
{
	int	x;
	int	y;

	x = 0;
	tr.det = (tr.o1.x * tr.o2.y - tr.o2.x * tr.o1.y);
	while (x < mlx.x)
	{
		y = 0;
		while (y < mlx.y)
		{
			sir_reset(&mlx, &tr, x, y);
			is_inside(&mlx, &tr, 1);
			put_color(tr.pixel_byte, mlx.r, mlx.g, mlx.blue);
			y++;
		}
		x++;
	}
	remove_triangle(mlx, tr);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
}
