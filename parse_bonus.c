/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:01:55 by snpark            #+#    #+#             */
/*   Updated: 2021/07/19 10:55:52 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static void	parse_man(int arg_n, char **arg_s, t_mlx *mlx)
{
	if (arg_n >= 4)
	{
		mlx->a = ft_atof(arg_s[2]);
		mlx->b = ft_atof(arg_s[3]);
		mlx->n = 10;
		mlx->y_max = 2;
		mlx->y_min = -2;
	}
	else
		error("argumant is not enough or to much\na b n max min");
	if (arg_n >= 5)
		mlx->n = ft_atoi(arg_s[4]);
	if (arg_n >= 7)
	{
		mlx->y_max = ft_atof(arg_s[5]);
		mlx->y_min = ft_atof(arg_s[6]);
	}
	if (mlx->y_max <= mlx->y_min)
		error("max is small or same than min");
	mlx->x_max = mlx->ratio * mlx->y_max;
	mlx->x_min = mlx->ratio * mlx->y_min;
	mlx->r = 25;
	mlx->g = 50;
	mlx->blue = 125;
}

static void	put_triangle(int arg_n, char **arg_s, t_mlx *mlx, t_triangle *tr)
{
	tr->p0.x = ft_atof(arg_s[2]);
	tr->p0.y = ft_atof(arg_s[3]);
	tr->p1.x = ft_atof(arg_s[4]);
	tr->p1.y = ft_atof(arg_s[5]);
	tr->p2.x = ft_atof(arg_s[6]);
	tr->p2.y = ft_atof(arg_s[7]);
	mlx->n = 5;
	mlx->y_max = 2.0;
	mlx->y_min = -2.0;
	tr->o1.x = tr->p1.x - tr->p0.x;
	tr->o1.y = tr->p1.y - tr->p0.y;
	tr->o2.x = tr->p2.x - tr->p0.x;
	tr->o2.y = tr->p2.y - tr->p0.y;
}

static void	parse_sir(int arg_n, char **arg_s, t_mlx *mlx)
{
	t_triangle	*tr;

	tr = (t_triangle *)malloc(sizeof(t_triangle));
	if (!tr)
		error("malloc fail");
	if (arg_n >= 8)
		put_triangle(arg_n, arg_s, mlx, tr);
	else
		error("need 3 point 6 number foramt is 0x 0y 1x 1y 2x 2y n max min");
	if (arg_n >= 9)
		mlx->n = ft_atoi(arg_s[8]);
	if (arg_n >= 11)
	{
		mlx->y_max = ft_atof(arg_s[9]);
		mlx->y_min = ft_atof(arg_s[10]);
	}
	if (mlx->y_max < mlx->y_min)
		error("range max is smaller than min");
	mlx->x_max = mlx->ratio * mlx->y_max;
	mlx->x_min = mlx->ratio * mlx->y_min;
	mlx->r = 25;
	mlx->g = 50;
	mlx->blue = 125;
	mlx->tri = tr;
	draw_triangle(*mlx, *tr);
}

void	parse(int arg_n, char **arg_s, t_mlx *mlx)
{
	if (arg_n == 1)
		error("type m or s, j");
	else if (*arg_s[1] == 'm' || *arg_s[1] == 'j')
	{
		mlx->flag = *arg_s[1];
		parse_man(arg_n, arg_s, mlx);
		if (mlx->flag == 'm')
			mandelbrot(*mlx);
		else
			julia(*mlx);
	}
	else if (*arg_s[1] == 's')
	{
		mlx->flag = 's';
		parse_sir(arg_n, arg_s, mlx);
	}
	else
		error("type m or s, m, j");
}
