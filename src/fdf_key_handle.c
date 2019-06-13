/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 23:15:13 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/13 06:12:17 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_handle(t_mlx *mlx, int key)
{
	if (key == E_KEY)
		Z_ANGLE += ROTATE_STEP;
	else if (key == D_KEY)
		Z_ANGLE -= ROTATE_STEP;
	else if (key == W_KEY)
		Y_ANGLE += ROTATE_STEP;
	else if (key == S_KEY)
		Y_ANGLE -= ROTATE_STEP;
	else if (key == Q_KEY)
		X_ANGLE += ROTATE_STEP;
	else if (key == A_KEY)
		X_ANGLE -= ROTATE_STEP;
	if (Z_ANGLE > PI_X2 || Z_ANGLE < -PI_X2)
		Z_ANGLE = 0;
	if (Y_ANGLE > PI_X2 || Y_ANGLE < -PI_X2)
		Y_ANGLE = 0;
	if (X_ANGLE > PI_X2 || X_ANGLE < -PI_X2)
		X_ANGLE = 0;
}

int		size_handle(t_mlx *mlx, int key)
{
	double	step;

	step = VECTOR_SIZE / 100 * 2;
	if (step < 1)
		step = 1;
	if (key == X_KEY || key == SCROLL_UP)
	{
		VECTOR_SIZE += (int)step;
		if (VECTOR_SIZE < 2)
			VECTOR_SIZE = 2;
		else if (VECTOR_SIZE > 500)
			VECTOR_SIZE = 500;
		return (VECTOR_SIZE);
	}
	else if (key == Z_KEY || key == SCROLL_DOWN)
	{
		VECTOR_SIZE -= (int)step;
		if (VECTOR_SIZE < 2)
			VECTOR_SIZE = 2;
		else if (VECTOR_SIZE > 500)
			VECTOR_SIZE = 500;
		return (VECTOR_SIZE);
	}
	return (0);
}

int		move_handle(t_mlx *mlx, int key)
{
	int		step;

	step = VECTOR_SIZE / 100 * 10;
	if (!step)
		step = 10;
	if (key == UP)
		return (POSITION.posy -= step);
	else if (key == DOWN)
		return (POSITION.posy += step);
	else if (key == RIGHT)
		return (POSITION.posx += step);
	else if (key == LEFT)
		return (POSITION.posx -= step);
	return (0);
}

int		depth_handle(t_mlx *mlx, int key)
{
	if (key == R_KEY)
		return (DEPTH += DEPTH_STEP);
	else if (key == F_KEY)
		return (DEPTH -= DEPTH_STEP);
	return (0);
}
