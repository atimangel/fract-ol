#ifndef FRACTOL_H
# define FRACTOL_H

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
/*
**EVENT
*/
int			escape(int key, void *parm);
int			red_cross(int arg, void *parm);
/*
**UTILITIE
*/
void			error(char *str);
/*
**MANDELBROT
*/
void			mandelbrot(t_mlx mlx, int n, float a, float b);
#endif
