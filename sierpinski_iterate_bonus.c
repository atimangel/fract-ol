/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinski_iterate_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:00:24 by snpark            #+#    #+#             */
/*   Updated: 2021/07/16 15:30:50 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	remove_1(t_mlx mlx, t_triangle big, t_triangle small)
{
	t_triangle	left;

	left.p0.x = big.p0.x;
	left.p0.y = big.p0.y;
	left.p1.x = small.p0.x;
	left.p1.y = small.p0.y;
	left.p2.x = small.p2.x;
	left.p2.y = small.p2.y;
	left.o1.x = left.p1.x - left.p0.x;
	left.o1.y = left.p1.y - left.p0.y;
	left.o2.x = left.p2.x - left.p0.x;
	left.o2.y = left.p2.y - left.p0.y;
	mlx.n--;
	remove_triangle(mlx, left);
}

void	remove_2(t_mlx mlx, t_triangle big, t_triangle small)
{
	t_triangle	up;

	up.p0.x = small.p0.x;
	up.p0.y = small.p0.y;
	up.p1.x = big.p1.x;
	up.p1.y = big.p1.y;
	up.p2.x = small.p1.x;
	up.p2.y = small.p1.y;
	up.o1.x = up.p1.x - up.p0.x;
	up.o1.y = up.p1.y - up.p0.y;
	up.o2.x = up.p2.x - up.p0.x;
	up.o2.y = up.p2.y - up.p0.y;
	mlx.n--;
	remove_triangle(mlx, up);
}

void	remove_3(t_mlx mlx, t_triangle big, t_triangle small)
{
	t_triangle	right;

	right.p0.x = small.p2.x;
	right.p0.y = small.p2.y;
	right.p1.x = small.p1.x;
	right.p1.y = small.p1.y;
	right.p2.x = big.p2.x;
	right.p2.y = big.p2.y;
	right.o1.x = right.p1.x - right.p0.x;
	right.o1.y = right.p1.y - right.p0.y;
	right.o2.x = right.p2.x - right.p0.x;
	right.o2.y = right.p2.y - right.p0.y;
	mlx.n--;
	remove_triangle(mlx, right);
}
