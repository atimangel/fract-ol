#include "fractol.h"

int	mouse_check(int button, int x, int y, void *parm)
{
	t_mlx	*mlx;
	void	*img;

	mlx = parm;
	if (button == 4)
	{
		printf("close\n");
		if (mlx->max > mlx->min)
		{
			mlx->max *= 0.9;
			mlx->min *= 0.9;
		}
	}
	else if (button == 5)
	{
		printf("far\n");
		if (mlx->max > mlx->min)
		{
			mlx->max *= 1.1;
			mlx->min *= 1.1;
		}
	}
	img = mlx->img;
	mlx->img = mlx_new_image(mlx->ptr, mlx->x, mlx->y);
	mlx->pix_str = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->len, &mlx->endian);
	mandelbrot(*mlx, 100, 0, 0);
	mlx_destroy_image(mlx->ptr, img);
}

int	main(int arg_n, char **arg_s)
{
	t_mlx	mlx;

	mlx.x = 1920;
	mlx.y = 1080;
	mlx.ratio = (float)mlx.x / mlx.y;
	mlx.ptr = mlx_init();
	mlx.max = 2;
	mlx.min = -2;
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
	mlx_key_hook(mlx.win, escape, 0);
	mlx_hook(mlx.win, 17, 0, red_cross, 0);
	mlx_mouse_hook(mlx.win, mouse_check, &mlx);
	mandelbrot(mlx, 100, 0, 0);
	mlx_loop(mlx.ptr);
}
