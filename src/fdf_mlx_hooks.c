/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 05:43:21 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/13 16:10:49 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_move(int x, int y, t_mlx *mlx)
{
	mlx->mouse.last_posx = mlx->mouse.posx;
	mlx->mouse.last_posy = mlx->mouse.posy;
	mlx->mouse.posx = x;
	mlx->mouse.posy = y;
	if (mlx->mouse.startus)
	{
		Y_ANGLE -= (mlx->mouse.last_posx - mlx->mouse.posx) / 500.0;
		X_ANGLE += (mlx->mouse.last_posy - mlx->mouse.posy) / 500.0;
		if (Y_ANGLE > PI_X2 || Y_ANGLE < -PI_X2)
			Y_ANGLE = 0;
		if (X_ANGLE > PI_X2 || X_ANGLE < -PI_X2)
			X_ANGLE = 0;
	}
	draw_mlx(mlx);
	return (0);
}

int		mouse_press(int button, int x, int y, t_mlx *mlx)
{
	if (button == 1 && x < 202 && y > 1350)
		fdf_switch(&MENU_BUTTON_MODE, &MENU_MODE);
	else if (button == 1)
		mlx->mouse.startus = 1;
	draw_mlx(mlx);
	return (0);
}

int		mouse_release(int button, int x, int y, t_mlx *mlx)
{
	mlx->mouse.last_posx = x;
	mlx->mouse.last_posy = y;
	if (button == 1)
		mlx->mouse.startus = 0;
	return (0);
}

int		key_press(int key, t_mlx *mlx)
{
	int		ret;

	ret = 0;
	rotate_handle(mlx, key);
	if (size_handle(mlx, key))
		ret = 0;
	else if (move_handle(mlx, key))
		ret = 0;
	else if (depth_handle(mlx, key))
		ret = 0;
	draw_mlx(mlx);
	return (ret);
}

int		deal_key(int key, t_mlx *mlx)
{
	if (key == ESC)
	{
		ft_arraydel((void **)POINTS);
		free(mlx);
		exit(EXIT_SUCCESS);
	}
	else if (key == ENTER)
		set_start_param(mlx);
	else if (key == SPACE)
	{
		X_ANGLE = 0;
		Y_ANGLE = 0;
		Z_ANGLE = 0;
	}
	else if (key == C_KEY)
		COLOR_STATUS = (COLOR_STATUS) ? 0 : 1;
	else if (key == CTRL)
		fdf_switch(&MENU_BUTTON_MODE, &MENU_MODE);
	draw_mlx(mlx);
	return (0);
}
