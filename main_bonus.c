/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:01:55 by snpark            #+#    #+#             */
/*   Updated: 2021/07/14 12:04:46 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	zoom(t_mlx *m, char flag, float x_ratio, float y_ratio)
{
	void	*img;

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
	printf("x y %i %i\n", x, y);
}

void	parse(int arg_n, char **arg_s, t_mlx *mlx)
{
	if (arg_n >= 3)
	{
		mlx->a = ft_atof(arg_s[1]);
		mlx->b = ft_atof(arg_s[2]);
		mlx->n = 10;
		mlx->y_max = 2;
		mlx->y_min = -2;
	}
	else
		error("argumant is not enough or to much\na b n max min");
	if (arg_n >= 4)
		mlx->n = ft_atoi(arg_s[3]);
	if (arg_n >= 6)
	{
		mlx->y_max = ft_atof(arg_s[4]);
		mlx->y_min = ft_atof(arg_s[5]);
	}
	if (mlx->y_max <= mlx->y_min)
		error("max is small or same than min");
	mlx->x_max = mlx->ratio * mlx->y_max;
	mlx->x_min = mlx->ratio * mlx->y_min;
	mlx->r = 25;
	mlx->g = 50;
	mlx->blue = 125;
}

int	main(int arg_n, char **arg_s)
{
	t_mlx	mlx;
	t_triangle tri;

	tri.p0.x = 0.0;
	tri.p0.y = 0.0;
	tri.p1.x = 1.0;
	tri.p1.y = 1.0;
	tri.p2.x = 2.0;
	tri.p2.y = 0.0;
	tri.o1.x = tri.p1.x - tri.p0.x;
	tri.o1.y = tri.p1.y - tri.p0.y;
	tri.o2.x = tri.p2.x - tri.p0.x;
	tri.o2.y = tri.p2.y - tri.p0.y;
	mlx.x = 1920;
	mlx.y = 1080;
	mlx.ratio = (float)mlx.x / mlx.y;
	parse(arg_n, arg_s, &mlx);
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
	//mandelbrot(mlx);
	draw_triangle(mlx, tri, 5);
	mlx_loop(mlx.ptr);
}
