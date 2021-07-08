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
}			t_mlx;

/*
**EVENT
*/
int			escape(int key, void *parm);
int			red_cross(int arg, void *parm);
/*
**UTILITIE
*/
void			error(char *str);
#endif
