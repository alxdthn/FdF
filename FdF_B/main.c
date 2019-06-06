/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 09:52:28 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/06 17:28:27 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*

size_t		sum_of_x_deltas(t_point ***points)
{
	size_t	x;
	size_t	y;
	size_t	res;

	x = 0;
	y = 0;
	res = 0;
	while (points[y][x])
	{
		if (points[y][x]->right)
			res += ABS(points[y][x]->right->x);
		x++;
	}
	while (points[y])
	{
		if (points[y][x - 1]->down)
			res += ABS(points[y][x - 1]->down->x);
		y++;
	}
	return (res);
}

size_t		sum_of_y_deltas(t_point ***points, int *half)
{
	size_t	x;
	size_t	y;
	size_t	res;

	x = 0;
	y = 0;
	res = 0;
	while (points[y][x])
	{
		if (points[y][x]->right)
			res += ABS(points[y][x]->right->y);
		x++;
	}
	*half = res;
	while (points[y])
	{
		if (points[y][x - 1]->down)
			res += ABS(points[y][x - 1]->down->y);
		y++;
	}
	return (res);
}

void	set_card(t_mlx *mlx)
{
	size_t	x;
	size_t	y;
	int		tmp_x;
	int		tmp_y;

	if (mlx->mode == 'c')
		return ;
	y = 0;
	while (mlx->points[y])
	{
		x = 0;
		while (mlx->points[y][x])
		{
			if (mlx->points[y][x]->right)
			{
				tmp_x = mlx->points[y][x]->right->x;
				tmp_y = mlx->points[y][x]->right->y;
				mlx->points[y][x]->right->x = (2 * tmp_y + tmp_x) / 2;
				mlx->points[y][x]->right->y = (2 * tmp_y - tmp_x) / 2;
			}
			if (mlx->points[y][x]->down)
			{
				tmp_x = mlx->points[y][x]->down->x;
				tmp_y = mlx->points[y][x]->down->y;
				mlx->points[y][x]->down->x = (2 * tmp_y + tmp_x) / 2;
				mlx->points[y][x]->down->y = (2 * tmp_y - tmp_x) / 2;
			}
			x++;
		}
		y++;
	}
	mlx->mode = 'c';
}

void	set_iso(t_mlx *mlx)
{
	size_t	x;
	size_t	y;
	int		tmp_x;
	int		tmp_y;

	if (mlx->mode == 'i')
		return ;
	y = 0;
	while (mlx->points[y])
	{
		x = 0;
		while (mlx->points[y][x])
		{
			if (mlx->points[y][x]->right)
			{
				tmp_x = mlx->points[y][x]->right->x;
				tmp_y = mlx->points[y][x]->right->y;
				mlx->points[y][x]->right->x =
				. tmp_x - tmp_y;
				mlx->points[y][x]->right->y = (tmp_x + tmp_y) / 2;
			}
			if (mlx->points[y][x]->down)
			{
				tmp_x = mlx->points[y][x]->down->x;
				tmp_y = mlx->points[y][x]->down->y;
				mlx->points[y][x]->down->x = tmp_x - tmp_y;
				mlx->points[y][x]->down->y = (tmp_x + tmp_y) / 2;			
			}
			x++;
		}
		y++;
	}
	mlx->mode = 'i';
}

void	add_size(t_mlx *mlx)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (mlx->points[y])
	{
		x = 0;
		while (mlx->points[y][x])
		{
			if (mlx->points[y][x]->right)
			{
				if (mlx->points[y][x]->right->x)
					mlx->points[y][x]->right->x += (mlx->points[y][x]->right->x > 0) ? 1 : -1;
				if (mlx->points[y][x]->right->y)
					mlx->points[y][x]->right->y += (mlx->points[y][x]->right->y > 0) ? 1 : -1;
			}
			if (mlx->points[y][x]->down)
			{
				if (mlx->points[y][x]->down->x)
					mlx->points[y][x]->down->x += (mlx->points[y][x]->down->x > 0) ? 1 : -1;
				if (mlx->points[y][x]->down->y)
					mlx->points[y][x]->down->y += (mlx->points[y][x]->down->y > 0) ? 1 : -1;
			}
			x++;
		}
		y++;
	}
}

void	reduce_size(t_mlx *mlx)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (mlx->points[y])
	{
		x = 0;
		while (mlx->points[y][x])
		{
			if (mlx->points[y][x]->right)
			{
				if (mlx->points[y][x]->right->x)
					mlx->points[y][x]->right->x -= (mlx->points[y][x]->right->x > 0) ? 1 : -1;
				if (mlx->points[y][x]->right->y)
					mlx->points[y][x]->right->y -= (mlx->points[y][x]->right->y > 0) ? 1 : -1;
			}
			if (mlx->points[y][x]->down)
			{
				if (mlx->points[y][x]->down->x)
					mlx->points[y][x]->down->x -= (mlx->points[y][x]->down->x > 0) ? 1 : -1;
				if (mlx->points[y][x]->down->y)
					mlx->points[y][x]->down->y -= (mlx->points[y][x]->down->y > 0) ? 1 : -1;
			}
			x++;
		}
		y++;
	}
}

*/

int		ft_abs_sum(int a, int b)
{
	if (a == b)
		return (0);
	if (a <= 0 && b >= 0)
		return (ABS(a) + b);
	else if (a <= 0 && b <= 0)
		return (ABS(a + b));
	else if (a >= 0 && b >= 0)
		return (a - b);
	else if (a >= 0 && b <= 0)
		return (a + ABS(b));
	return (0);
}

void	draw_vector(t_mlx *mlx, t_vector *vector)
{
	int		x_abs;
	int		y_abs;
	int		i;
    int		dx;
    int		dy;
	int		error;

	x_abs = IMG_WIDTH / 2 + vector->x1;
	y_abs = IMG_HEIGHT / 2 - vector->y1;
	dx = ABS(vector->x2 - vector->x1);
	dy = ABS(vector->y2 - vector->y1);
	error = (vector->x2 > vector->y2) ? dx / 2 : dy / 2;
	i = (dx > dy) ? dx : dy;
//	ft_printf("x1 = %f; y1 = %f; x2 = %f; y2 = %f; dx = %d; dy = %d;      %d | %d : ", vector->x1, vector->y1, vector->x2, vector->y2, dx, dy, x_abs, y_abs);
	while (i)
	{
		IMG_DATA[x_abs + y_abs * LINE_SIZE] = vector->color;
		error -= (dx > dy) ? dy : dx;
		if (error < 0)
		{
			if ((dx > dy))
			{
				(vector->y2 >= 0) ? y_abs-- : y_abs++;
				error += dx;
			}
			else
			{
				(vector->x2 >= 0) ? x_abs++ : x_abs--;
				error += dy;
			}
		}
		if ((dx > dy))
			x_abs++;
		else
			y_abs++;
		i--;
	}
//	ft_printf("%d | %d\n", x_abs, y_abs);

}

void	set_vector_to_image(t_mlx *mlx)
{
	size_t		i;

	i = 0;
	while (VECTORS[i])
		draw_vector(mlx, VECTORS[i++]);
}

void	set_iso(t_mlx *mlx)
{
	size_t	i;
	int		new_x;
	int		new_y;
	double	angle;

	angle = 30;
	i = 0;
	while (VECTORS[i])
	{
		new_x = (VECTORS[i]->x1 + VECTORS[i]->y1) * cos(angle);
		new_y = (VECTORS[i]->x1 - VECTORS[i]->y1) * sin(angle) - VECTORS[i]->z1;
		VECTORS[i]->x1 = new_x;
		VECTORS[i]->y1 = new_y;
		new_x = (VECTORS[i]->x2 + VECTORS[i]->y2) * cos(angle);
		new_y = (VECTORS[i]->x2 - VECTORS[i]->y2) * sin(angle) - VECTORS[i]->z2;
		VECTORS[i]->x2 = new_x;
		VECTORS[i]->y2 = new_y;
		i++;
	}
}

/*
void	set_iso(t_mlx *mlx)
{
	size_t		i;
	double		xx;
	double		tmp_xx;
	double		tmp_yx;
	double		xy;
	double		yx;
	double		yy;

	xx = 1;
	tmp_xx = 1;
	tmp_yx = 0;
	xy = 0;
	yx = 0;
	yy = 1;
	xx = cos(ANGLE) * tmp_xx - sin(ANGLE) * xy;
	xy = sin(ANGLE) * tmp_xx + cos(ANGLE) * xy;
	yx = cos(ANGLE) * tmp_yx - sin(ANGLE) * yy;
	yy = sin(ANGLE) * tmp_yx + cos(ANGLE) * yy;
	i = 0;

	while (VECTORS[i])
	{
		tmp_xx = VECTORS[i]->x1;
		tmp_yx = VECTORS[i]->y1;
		VECTORS[i]->x1 = tmp_xx - tmp_yx;
		VECTORS[i]->y1 = (tmp_xx + tmp_yx) / 2;
		tmp_xx = VECTORS[i]->x2;
		tmp_yx = VECTORS[i]->y2;
		VECTORS[i]->x2 = tmp_xx - tmp_yx;
		VECTORS[i]->y2 = (tmp_xx + tmp_yx) / 2;
		i++;
	}


	while (VECTORS[i])
	{
		tmp_xx = VECTORS[i]->x1;
		VECTORS[i]->x1 = tmp_xx * xx + VECTORS[i]->y1 * xy;
		VECTORS[i]->y1 = tmp_xx * yx + VECTORS[i]->y1 * yy;
		tmp_xx = VECTORS[i]->x2;		
		VECTORS[i]->x2 = tmp_xx * xx + VECTORS[i]->y2 * xy;
		VECTORS[i]->y2 = tmp_xx * yx + VECTORS[i]->y2 * yy;
		VECTORS[i]->z1 = xx;
		VECTORS[i]->z2 = xx;
		i++;
	}
	ANGLE += 0.01;
}
*/
int		deal_key(int key, void *param)
{
	static t_mlx	*mlx;

	if (!mlx)
	{
		mlx = (t_mlx *)param;
		ANGLE = 0.01;
	}
	if (key == ESC)
		exit(EXIT_SUCCESS);
	if (key == R_SHIFT)
	{
		mlx_clear_window(MLX_PTR, WIN_PTR);
		set_iso(mlx);
		IMG_PTR = mlx_new_image(MLX_PTR, IMG_WIDTH, IMG_HEIGHT);
		IMG_DATA = (int *)mlx_get_data_addr(IMG_PTR, &BPP, &LINE_SIZE, &ENDIAN);
		LINE_SIZE /= 4;
		set_vector_to_image(mlx);
		mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_PTR, 0, 0);
	}
	if (key == ENTER)
	{
		IMG_PTR = mlx_new_image(MLX_PTR, IMG_WIDTH, IMG_HEIGHT);
		IMG_DATA = (int *)mlx_get_data_addr(IMG_PTR, &BPP, &LINE_SIZE, &ENDIAN);
		LINE_SIZE /= 4;
		set_vector_to_image(mlx);
		mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_PTR, 0, 0);
	}
	return (0);
}

void	set_vector_size(t_mlx *mlx)
{
	size_t	i;

	i = 0;
	while (VECTORS[i])
	{
		VECTORS[i]->x1 *= VECTOR_SIZE;
		VECTORS[i]->y1 *= VECTOR_SIZE;
		VECTORS[i]->z1 *= VECTOR_SIZE;
		VECTORS[i]->x2 *= VECTOR_SIZE;
		VECTORS[i]->y2 *= VECTOR_SIZE;
		VECTORS[i]->z2 *= VECTOR_SIZE;
		i++;
	}
}

void		elem_counter(t_mlx *mlx)
{
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	while (POINTS[y][x])
		x++;
	X_SIZE = x;
	while (POINTS[y])
		y++;
	Y_SIZE = y;
}

void	prepare_image(t_mlx *mlx)
{
	elem_counter(mlx);
	if ((WIN_WIDTH / WIN_HEIGHT) && (X_SIZE / Y_SIZE > 1) && X_SIZE != Y_SIZE)
		VECTOR_SIZE = (WIN_WIDTH - WIN_WIDTH / 100 * MARGIN) / (X_SIZE - 1) / 2;
	else
		VECTOR_SIZE = (WIN_HEIGHT - WIN_HEIGHT / 100 * MARGIN) / (Y_SIZE - 1) / 2;
	VECTOR_SIZE = 50;
	IMG_WIDTH = WIN_WIDTH;
	IMG_HEIGHT = WIN_HEIGHT;
	X_MIN *= VECTOR_SIZE;
	X_MAX *= VECTOR_SIZE;
	Y_MIN *= VECTOR_SIZE;
	Y_MAX *= VECTOR_SIZE;
	Z_MIN *= VECTOR_SIZE;
	Z_MAX *= VECTOR_SIZE;
	X_SIZE *= VECTOR_SIZE;
	Y_SIZE *= VECTOR_SIZE;
	Z_SIZE *= VECTOR_SIZE;
	set_vector_size(mlx);
}

int		main(void)
{
	t_mlx	mlx;

	mlx.width = 1920;
	mlx.height = 1080;
	fdf_parce(&mlx, "test_maps/2-2.fdf");
	prepare_image(&mlx);
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.width, mlx.height, "fdf");
	mlx_key_hook(mlx.win_ptr, deal_key, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return 0;
}

/*
int		main(void)
{
	char *line;
	int	fd;

	fd = 1;
	write(fd, "asa", 3);
	printf("%d %s", get_next_line(fd, &line), line);
}
*/