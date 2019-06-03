/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 09:52:28 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/03 03:25:06 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define COLOR 0xf442ee
#define ANGLE 45
#define ABS(x) (x > 0 ? x : -x)
#define MARGIN 50

t_abs	draw_vector(t_mlx *mlx, t_vector *vector, t_abs abs, int color)
{
	int		x1;
	int		y1;
	int		i;
    int		dx;
    int		dy;
	int		error;

	x1 = vector->x;
	y1 = vector->y;
	dx = ABS(x1);
	dy = ABS(y1);
	error = (vector->x > vector->y) ? dx / 2 : dy / 2;
	i = (dx > dy) ? dx : dy;
	while (i)
	{
		mlx->img_data[abs.x_abs + abs.y_abs * mlx->line_size] = color;
		error -= (dx > dy) ? dy : dx;
		if (error < 0)
		{
			if ((dx > dy))
			{
				(y1 > 0) ? abs.y_abs-- : abs.y_abs++;
				error += dx;
			}
			else
			{
				(x1 > 0) ? abs.x_abs++ : abs.x_abs--;
				error += dy;
			}
		}
		if ((dx > dy))
			(x1 > 0) ? abs.x_abs++ : abs.x_abs--;
		else
			(y1 > 0) ? abs.y_abs-- : abs.y_abs++;
		i--;
	}
	return (abs);
}

void	set_vector_to_image(t_mlx *mlx)
{
	size_t		x;
	size_t		y;

	y = 0;
	while (mlx->points[y])
	{
		x = 0;
		while (mlx->points[y][x])
		{
			if (mlx->points[y][x]->right)
				mlx->points[y][x + 1]->abs = draw_vector(mlx, mlx->points[y][x]->right, mlx->points[y][x]->abs, mlx->points[y][x]->color);
			if (mlx->points[y][x]->down)
				mlx->points[y + 1][x]->abs = draw_vector(mlx, mlx->points[y][x]->down, mlx->points[y][x]->abs, mlx->points[y][x]->color);
			x++;
		}
		y++;
	}
	mlx->img_data[mlx->points[y - 1][x - 1]->abs.x_abs + mlx->points[y - 1][x - 1]->abs.y_abs * mlx->line_size] = mlx->points[y - 1][x - 1]->color;
}

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
}

void	set_iso(t_mlx *mlx)
{
	size_t	x;
	size_t	y;
	int		tmp_x;
	int		tmp_y;

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
				mlx->points[y][x]->right->x = tmp_x - tmp_y;
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
}

int		deal_key(int key, void *param)
{
	static t_mlx	mlx;
	size_t			i;
	int				width;
	int				height;
	int				half_sum_y_deltas;

	i = 0;
	if (!mlx.win_ptr)
		mlx = *(t_mlx *)param;
	if (key == 53)
		exit(1);
	if (key == 36)
	{
		mlx_clear_window(mlx.mlx_ptr, mlx.win_ptr);
		if (mlx.mode == 'i')
			set_card(&mlx);
		mlx.img_width = sum_of_x_deltas(mlx.points) + 1;
		mlx.img_height = sum_of_y_deltas(mlx.points, &half_sum_y_deltas) + 1;
		mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, mlx.img_width, mlx.img_height);
		mlx.img_data = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.line_size, &mlx.endian);
		mlx.line_size /= 4;
		mlx.points[0][0]->abs.y_abs = 0;
		set_vector_to_image(&mlx);
		mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, mlx.win_width / 2 - mlx.img_width / 2, mlx.win_height / 2 - mlx.img_height / 2);
		mlx_destroy_image(mlx.mlx_ptr, mlx.img_ptr);
		mlx.mode = 'c';
	}
	else if (key == 258)
	{
		if (mlx.mode == 'c' || !mlx.mode)
		{

			mlx_clear_window(mlx.mlx_ptr, mlx.win_ptr);
			set_iso(&mlx);
			mlx.img_width = sum_of_x_deltas(mlx.points) + 1;
			mlx.img_height = sum_of_y_deltas(mlx.points, &half_sum_y_deltas) + 1;
			mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, mlx.img_width, mlx.img_height);
			mlx.img_data = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.line_size, &mlx.endian);
			mlx.line_size /= 4;
			mlx.points[0][0]->abs.y_abs = ABS(half_sum_y_deltas);
			set_vector_to_image(&mlx);
			mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, mlx.win_width / 2 - mlx.img_width / 2, mlx.win_height / 2 - mlx.img_height / 2);
			mlx_destroy_image(mlx.mlx_ptr, mlx.img_ptr);
			mlx.mode = 'i';
		}
	}
	return (0);
}

void	set_vector_size(t_mlx *mlx)
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
				mlx->points[y][x]->right->x *= mlx->vector_size;
			if (mlx->points[y][x]->down)
				mlx->points[y][x]->down->y *= mlx->vector_size;
			x++;
		}
		y++;
	}
}

void	prepare_image(t_mlx *mlx)
{
	if ((mlx->win_width / mlx->win_height) && (mlx->points_x_count / mlx->points_y_count) && mlx->points_x_count != mlx->points_y_count)
	{
		mlx->win_margin = mlx->win_width / 100 * MARGIN;
		mlx->img_width = mlx->win_width - mlx->win_margin + 1;
		mlx->vector_size = (mlx->img_width - 1) / (mlx->points_x_count - 1);
		mlx->img_width = mlx->vector_size * (mlx->points_x_count - 1) + 1;
		mlx->img_height = mlx->vector_size * (mlx->points_y_count - 1) + 1;
	}
	else
	{
		mlx->win_margin = mlx->win_height / 100 * MARGIN;
		mlx->img_height = mlx->win_height - mlx->win_margin + 1;
		mlx->vector_size = (mlx->img_height - 1) / (mlx->points_y_count - 1);
		mlx->img_height = mlx->vector_size * (mlx->points_y_count - 1) + 1;
		mlx->img_width = mlx->vector_size * (mlx->points_x_count - 1) + 1;
	}
	mlx->mode = 0;
	set_vector_size(mlx);
}

int		main(void)
{
	t_mlx	mlx;		

	mlx.win_width = 800;
	mlx.win_height = 600;
	mlx.points = fdf_parce("test_maps/3-3.fdf", &mlx.points_x_count, &mlx.points_y_count);
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.win_width, mlx.win_height, "fdf");
	prepare_image(&mlx);
	//ft_printf("%zu\n", sum_of_x_deltas(mlx.points));
	//ft_printf("%zu\n", sum_of_y_deltas(mlx.points));
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