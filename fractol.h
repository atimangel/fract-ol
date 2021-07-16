/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:01:51 by snpark            #+#    #+#             */
/*   Updated: 2021/07/16 13:16:51 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"

typedef struct s_mlx
{
	void			*ptr;
	void			*win;
	void			*img;
	void			*pix_str;
	int				bpp;
	int				len;
	int				endian;
	unsigned int	x;
	unsigned int	y;
	float			ratio;
	float			max;
	float			min;
	float			a;
	float			b;
	int				n;
}				t_mlx;

typedef struct s_mandelbrot
{
	float			ca;
	float			cb;
	float			a;
	float			b;
	float			aa;
	float			bb;
	unsigned char	r;
	unsigned char	g;
	unsigned char	blue;
	unsigned char	*pixel_byte;
}				t_mandelbrot;
/*
**EVENT
*/
int			escape(int key, void *parm);
int			red_cross(int arg, void *parm);
/*
**UTILITIE
*/
void		error(char *str);
int			ft_atoi(const char *string);
float		ft_atof(const char *string);
/*
**MANDELBROT
*/
float		map(int x, int max, float new_min, float new_max);
void		put_color(char *pixel, char r, char g, char b);
void		reset(t_mlx mlx, t_mandelbrot *man, int x, int y);
void		trans_color(t_mandelbrot *man, int i);
void		mandelbrot(t_mlx mlx);
#endif
