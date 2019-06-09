/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 09:52:28 by nalexand          #+#    #+#             */
/*   W_KEYdated: 2019/06/09 00:46:35 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_abs	get_start_coordinates(t_mlx *mlx, t_point *point)
{
	t_abs	abs;

	abs.x = ABS(IMG_WIDTH / 2 + (int)point->x);
	abs.y = ABS(IMG_HEIGHT / 2 - (int)point->y);
	return (abs);
}

void	draw_line(t_mlx *mlx, t_point p1, t_point p2)
{
	int		i;
    int		dx;
    int		dy;
	int		error;
	t_abs	abs;

	abs = get_start_coordinates(mlx, &p1);
	dx = ABS(p2.x - p1.x);
	dy = ABS(p2.y - p1.y);
	error = (p2.x > p2.y) ? dx / 2 : dy / 2;
	i = (dx > dy) ? dx : dy;
	while (i)
	{
		if (abs.x >= 0 && abs.y >= 0)
			IMG_DATA[abs.x + abs.y * LINE_SIZE] = p1.color;
		error -= (dx > dy) ? dy : dx;
		if (error < 0)
		{
			if ((dx > dy))
			{
				(p2.y > p1.y) ? abs.y-- : abs.y++;
				error += dx;
			}
			else
			{
				(p2.x > p1.x) ? abs.x++ : abs.x--;
				error += dy;
			}
		}
		if ((dx > dy))
			(p2.x > p1.x) ? abs.x++ : abs.x--;
		else
			(p2.y > p1.y) ? abs.y-- : abs.y++;
		i--;
	}
	if (abs.x >= 0 && abs.y >= 0)
		IMG_DATA[abs.x + abs.y * LINE_SIZE] = p1.color;
}

t_point		set_iso(t_mlx *mlx, t_point	*point)
{
	int		tmp_x;
	int		tmp_y;
	t_point	res;

	tmp_x = point->x * VECTOR_SIZE;
	tmp_y = point->y * VECTOR_SIZE;
	res.x = (tmp_x - tmp_y) * cos(0.523599);
	res.y = point->z * VECTOR_SIZE + (tmp_x + tmp_y) * sin(0.523599);
	res.color = point->color;
	return (res);
}

void	draw_vectors(t_mlx *mlx, t_point (conv)(t_mlx *, t_point *))
{
	t_point	p1;
	t_point p2;
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	while (y < Y_SIZE)
	{
		if (POINTS[x + y * X_SIZE])
			p1 = conv(mlx, POINTS[x + y * X_SIZE]);
		if (x + 1 < X_SIZE)
		{
			p2 = conv(mlx, POINTS[x + 1 + y * X_SIZE]);
			draw_line(mlx, p1, p2);
		}
		if (y + 1 < Y_SIZE)
		{
			p2 = conv(mlx, POINTS[x + (y + 1) * X_SIZE]);
			draw_line(mlx, p1, p2);
		}
		x++;
		if (x == X_SIZE)
		{
			x = 0;
			y++;
		}
	}
}

t_point	x_conv(t_mlx *mlx, t_point *point)
{
	t_point	res;
	double	tmp_y;
	double	tmp_z;

    tmp_y = point->y;
	tmp_z = point->z;
    res.x = point->x;
	res.y = tmp_y * cos(X_ANGLE) + tmp_z * sin(X_ANGLE);
	res.z = -tmp_y * sin(X_ANGLE) + tmp_z * cos(X_ANGLE);
	res.color = point->color;
	return (res);
}

t_point	y_conv(t_mlx *mlx, t_point *point)
{
	t_point	res;
	double	tmp_x;
	double	tmp_z;

    tmp_x = point->x;
	tmp_z = point->z;
    res.x = tmp_x * cos(Y_ANGLE) + tmp_z * sin(Y_ANGLE);
	res.y = point->y;
	res.z = -tmp_x * sin(Y_ANGLE) + tmp_z * cos(Y_ANGLE);
	res.color = point->color;
	return (res);
}

t_point	z_conv(t_mlx *mlx, t_point *point)
{
	t_point	res;
	double	tmp_x;
	double	tmp_y;

    tmp_x = point->x;
	tmp_y = point->y;
    res.x = tmp_x * cos(Z_ANGLE) - tmp_y * sin(Z_ANGLE);
	res.y = tmp_x * sin(Z_ANGLE) + tmp_y * cos(Z_ANGLE);
	res.z = point->z;
	res.color = point->color;
	return (res);
}

t_point	just_set(t_mlx *mlx, t_point *point)
{
	t_point	res;

    res.x = point->x * VECTOR_SIZE;
	res.y = point->y * VECTOR_SIZE;
	res.z = point->z * VECTOR_SIZE;
	res.color = point->color;
	return (res);
}


t_point	rotate(t_mlx *mlx, t_point *point)
{
	t_point	res;

	res = just_set(mlx, point);
	if (Z_ANGLE)
		res = z_conv(mlx, &res);
	//move_to_start(mlx, &res);
	if (X_ANGLE)
		res = x_conv(mlx, &res);
	if (Y_ANGLE)
		res = y_conv(mlx, &res);
	//move_back(mlx, &res);
	return (res);
}

int		deal_key(int key, void *param)
{
	t_mlx		*mlx;
	void		*conv;

	mlx = (t_mlx *)param;
	if (key == ESC)
		exit(EXIT_SUCCESS);
	else if (key == ENTER)
	{
		X_ANGLE = 0;
		Y_ANGLE = 0;
		Z_ANGLE = 0.523599;
		conv = &rotate;
	}
	if (key == ESC || key == R_SHIFT || key == ENTER)
	{
		mlx_clear_window(MLX_PTR, WIN_PTR);
		draw_vectors(mlx, conv);
		mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_PTR, 0, 0);
		ft_bzero(IMG_DATA, IMG_WIDTH * IMG_HEIGHT * 4);
	}
	return (0);
}

int		key_press(int key, void *param)
{
	t_mlx		*mlx;
	void		*conv;

	mlx = (t_mlx *)param;
	if (key == E_KEY || key == D_KEY || key == W_KEY || key == S_KEY || key == A_KEY || key == Q_KEY)
	{
		if (key == E_KEY || key == D_KEY)
		{
			if (key == E_KEY)
				Z_ANGLE += ROTATE_STEP;
			if (key == D_KEY)
				Z_ANGLE -= ROTATE_STEP;
		}
		if (key == W_KEY || key == S_KEY)
		{
			if (key == W_KEY)
				Y_ANGLE += ROTATE_STEP;
			if (key == S_KEY)
				Y_ANGLE -= ROTATE_STEP;
		}
		if (key == A_KEY || key == Q_KEY)
		{
			if (key == Q_KEY)
				X_ANGLE += ROTATE_STEP;
			if (key == A_KEY)
				X_ANGLE -= ROTATE_STEP;
		}
		conv = &rotate;
		mlx_clear_window(MLX_PTR, WIN_PTR);
		draw_vectors(mlx, conv);
		mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_PTR, 0, 0);
		ft_bzero(IMG_DATA, IMG_WIDTH * IMG_HEIGHT * 4);
	}
	return (0);
}

void	img_init(t_mlx *mlx)
{
	IMG_HEIGHT = WIN_HEIGHT;
	IMG_WIDTH = WIN_WIDTH;
	IMG_PTR = mlx_new_image(MLX_PTR, IMG_WIDTH, IMG_HEIGHT);
	IMG_DATA = (int *)mlx_get_data_addr(IMG_PTR, &BPP, &LINE_SIZE, &ENDIAN);
	LINE_SIZE /= 4;
	if (X_SIZE > (Y_SIZE + Z_SIZE))
		VECTOR_SIZE = (WIN_WIDTH - WIN_WIDTH / 100 * MARGIN) / X_SIZE;
	else
		VECTOR_SIZE = (WIN_WIDTH - WIN_WIDTH / 100 * MARGIN) / (Y_SIZE + Z_SIZE);
	X_ANGLE = 0.523599;
	Y_ANGLE = 0.0;
	Z_ANGLE = 0.523599;
}

int		main(void)
{
	t_mlx	*mlx;

	mlx = fdf_parce("../test_maps/3-3.fdf");
	WIN_WIDTH = 1200;
	WIN_HEIGHT = 1300;
	MLX_PTR = mlx_init();
	WIN_PTR = mlx_new_window(MLX_PTR, WIN_WIDTH, WIN_HEIGHT, "fdf by nalexand");
	img_init(mlx);
	mlx_key_hook(WIN_PTR, deal_key, mlx);
	mlx_hook(WIN_PTR, 2, 0, &key_press, mlx);
	mlx_loop(MLX_PTR);
	return 0;
}
