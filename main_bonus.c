/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:01:55 by snpark            #+#    #+#             */
/*   Updated: 2021/07/16 11:40:44 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	zoom(t_mlx *m, char flag, float x_ratio, float y_ratio)
{
	void	*img;

	if (m->flag == 's')
		return ;
	if (flag == 1 && m->x_max > m->x_min && m->y_max > m->y_min)
	{
		m->x_max -= m->x_max * 0.1 * (1 - x_ratio);
		m->x_min -= m->x_min * 0.1 * x_ratio;
		m->y_max -= m->y_max * 0.1 * (1 - y_ratio);
		m->y_min -= m->y_min * 0.1 * y_ratio;
	}
	else if (flag == -1 && m->x_max > m->x_min && m->y_max > m->y_min)
	{
		m->x_max += m->x_max * 0.1 * (1 - x_ratio);
		m->x_min += m->x_min * 0.1 * x_ratio;
		m->y_max += m->y_max * 0.1 * (1 - y_ratio);
		m->y_min += m->y_min * 0.1 * y_ratio;
	}
	img = m->img;
	m->img = mlx_new_image(m->ptr, m->x, m->y);
	m->pix_str = mlx_get_data_addr(m->img, &m->bpp, &m->len, &m->endian);
	mandelbrot(*m);
	mlx_destroy_image(m->ptr, img);
}

int	mouse_check(int button, int x, int y, void *parm)
{
	t_mlx	*m;

	m = parm;
	if (button == 4)
		zoom(m, 1, (float)x / m->x, (float)y / m->y);
	else if (button == 5)
		zoom(m, -1, (float)x / m->x, (float)y/ m->y);
}

void	parse_man(int arg_n, char **arg_s, t_mlx *mlx)
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
	mandelbrot(*mlx);
}

void	parse_sir(int arg_n, char **arg_s, t_mlx *mlx)
{
	t_triangle tr;

	if (arg_n >= 8)
	{
		tr.p0.x = ft_atof(arg_s[2]);
		tr.p0.y = ft_atof(arg_s[3]);
		tr.p1.x = ft_atof(arg_s[4]);
		tr.p1.y = ft_atof(arg_s[5]);
		tr.p2.x = ft_atof(arg_s[6]);
		tr.p2.y = ft_atof(arg_s[7]);
		mlx->n = 5;
		mlx->y_max = 2.0;
		mlx->y_min = -2.0;
	}
	else
		error("need 3 point 6 number foramt is 0x 0y 1x 1y 2x 2y n max min");
	tr.o1.x = tr.p1.x - tr.p0.x;
	tr.o1.y = tr.p1.y - tr.p0.y;
	tr.o2.x = tr.p2.x - tr.p0.x;
	tr.o2.y = tr.p2.y - tr.p0.y;
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
	draw_triangle(*mlx, tr);
}

void	parse(int arg_n, char **arg_s, t_mlx *mlx)
{
	if (arg_n == 1)
		error("type m or s, m for mandelbrot, s for triangle");
	else if (*arg_s[1] == 'm')
	{
		mlx->flag = 'm';
		parse_man(arg_n, arg_s, mlx);
	}
	else if (*arg_s[1] == 's')
	{
		mlx->flag = 's'; 
		parse_sir(arg_n, arg_s, mlx);
	}
	else
		error("type m or s, m for mandelbrot, s for triangle");
}

int	main(int arg_n, char **arg_s)
{
	t_mlx	mlx;
	
	mlx.x = 1920;
	mlx.y = 1080;
	mlx.ratio = (float)mlx.x / mlx.y;
	mlx.ptr = mlx_init();
	if (!mlx.ptr)
		error("mlx_init fail");
	mlx.win = mlx_new_window(mlx.ptr, mlx.x, mlx.y, "fractol");
	if (!mlx.win)
		error("mlx_new_window fail");
	mlx.img = mlx_new_image(mlx.ptr, mlx.x, mlx.y);
	if (mlx.img == NULL)
		error("mlx_new_image fail");
	mlx.pix_str = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.len, &mlx.endian);
	if (!mlx.pix_str)
		error("mlx_get_data_addr fail");
	mlx_key_hook(mlx.win, key_event, &mlx);
	mlx_hook(mlx.win, 17, 0, red_cross, &mlx);
	mlx_mouse_hook(mlx.win, mouse_check, &mlx);
	parse(arg_n, arg_s, &mlx);
	//mandelbrot(mlx);
	//draw_triangle(mlx, tri);
	mlx_loop(mlx.ptr);
}
