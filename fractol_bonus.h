/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:01:51 by snpark            #+#    #+#             */
/*   Updated: 2021/07/13 16:39:44 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"

typedef	struct		s_mlx
{
	void		*ptr;
	void		*win;
	void		*img;
	void		*pix_str;
	int		bpp;
	int		len;
	int		endian;
	unsigned int	x;
	unsigned int	y;
	float		ratio;
	float		x_max;
	float		x_min;
	float		y_max;
	float		y_min;
	float		a;
	float		b;
	int		n;
	unsigned char	r;
	unsigned char	g;
	unsigned char	blue;
}			t_mlx;

typedef struct		s_mandelbrot
{
	float		ca;
	float		cb;
	float		a;
	float		b;
	float		aa;
	float		bb;
	unsigned char	r;
	unsigned char	g;
	unsigned char	blue;
	unsigned char	*pixel_byte;
}			t_mandelbrot;

typedef struct		s_vector
{
	float		x;
	float		y;
}			t_vector;

typedef struct		s_triangle
{
	t_vector	p0;
	t_vector	p1;
	t_vector	p2;
	t_vector	o1;
	t_vector	o2;
}			t_triangle;
/*
**EVENT
*/
void			zoom(t_mlx *m, char flag, float x_ratio, float y_ratio);
int			key_event(int key, void *parm);
int			red_cross(int arg, void *parm);
/*
**UTILITIE
*/
void			error(char *str);
int			ft_atoi(const char *string);
float			ft_atof(const char *string);
/*
**MANDELBROT
*/
float			map(int x, int max, float new_min, float new_max);
void			put_color(char *pixel, char r, char g, char b);
void			reset(t_mlx mlx, t_mandelbrot *man, int x, int y);
void			trans_color(t_mlx mlx, t_mandelbrot *man, int i);
void			mandelbrot(t_mlx mlx);
void			draw_triangle(t_mlx mlx, t_triangle tr, int n);
#endif
