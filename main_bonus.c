/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:01:55 by snpark            #+#    #+#             */
/*   Updated: 2021/07/27 09:25:47 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	make_fractal(t_mlx *mlx)
{
	if (mlx->flag == 'm')
		mandelbrot(*mlx);
	else if (mlx->flag == 'j')
		julia(*mlx);
	else if (mlx->flag == 's')
		draw_triangle(*mlx, *(t_triangle *)mlx->tri);
}

void	zoom(t_mlx *m, char flag, float x_ratio, float y_ratio)
{
	void	*img;
	float	x_len;
	float	y_len;

	x_len = m->x_max - m->x_min;
	y_len = m->y_max - m->y_min;
	if (flag == 1 && m->x_max > m->x_min && m->y_max > m->y_min)
	{
		m->x_max = m->x_max - x_len * 0.1 * (1 - x_ratio);
		m->x_min = m->x_min + x_len * 0.1 * x_ratio;
		m->y_max = m->y_max - y_len * 0.1 * (1 - y_ratio);
		m->y_min = m->y_min + y_len * 0.1 * y_ratio;
	}
	else if (flag == -1 && m->x_max > m->x_min && m->y_max > m->y_min)
	{
		m->x_max = m->x_max + x_len * 0.1 * (1 - x_ratio);
		m->x_min = m->x_min - x_len * 0.1 * x_ratio;
		m->y_max = m->y_max + y_len * 0.1 * (1 - y_ratio);
		m->y_min = m->y_min - y_len * 0.1 * y_ratio;
	}
	new_img(m);
}

int	mouse_check(int button, int x, int y, void *parm)
{
	t_mlx	*m;

	m = parm;
	if (button == 4)
		zoom(m, 1, (float)x / m->x, (float)y / m->y);
	else if (button == 5)
		zoom(m, -1, (float)x / m->x, (float)y / m->y);
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
	mlx_loop(mlx.ptr);
}
