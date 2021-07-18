/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:01:55 by snpark            #+#    #+#             */
/*   Updated: 2021/07/18 15:03:23 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_check(int button, int x, int y, void *parm)
{
	t_mlx	*m;
	void	*img;

	m = parm;
	if (button == 4 && m->max > m->min)
	{
		m->max *= 0.9;
		m->min *= 0.9;
	}
	else if (button == 5 && m->max > m->min)
	{
		m->max *= 1.1;
		m->min *= 1.1;
	}
	img = m->img;
	m->img = mlx_new_image(m->ptr, m->x, m->y);
	m->pix_str = mlx_get_data_addr(m->img, &m->bpp, &m->len, &m->endian);
	make_fractal(*m);
	mlx_destroy_image(m->ptr, img);
}

void	parse(int arg_n, char **arg_s, t_mlx *mlx)
{
	mlx->flag = 0;
	if (arg_n >= 2)
		mlx->flag = *arg_s[1];
	if (!(mlx->flag == 'm' || mlx->flag == 'j'))
		error("select 'j' julia set or 'm' mandelbrot set");
	if (arg_n >= 4)
	{
		mlx->a = ft_atof(arg_s[2]);
		mlx->b = ft_atof(arg_s[3]);
		mlx->n = 10;
		mlx->max = 2;
		mlx->min = -2;
	}
	else
		error("argumant is not enough or to much\na b n max min");
	if (arg_n >= 5)
		mlx->n = ft_atoi(arg_s[4]);
	if (arg_n >= 7)
	{
		mlx->max = ft_atof(arg_s[5]);
		mlx->min = ft_atof(arg_s[6]);
	}
}

void	make_fractal(t_mlx mlx)
{
	if (mlx.flag == 'm')
		mandelbrot(mlx);
	else if (mlx.flag == 'j')
		julia(mlx);
}

int	main(int arg_n, char **arg_s)
{
	t_mlx	mlx;

	parse(arg_n, arg_s, &mlx);
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
	mlx_key_hook(mlx.win, escape, &mlx);
	mlx_hook(mlx.win, 17, 0, red_cross, &mlx);
	mlx_mouse_hook(mlx.win, mouse_check, &mlx);
	make_fractal(mlx);
	mlx_loop(mlx.ptr);
}
