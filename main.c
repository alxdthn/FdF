/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 09:52:28 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/02 00:29:46 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define COLOR 0xf442ee
#define ANGLE 45
#define ABS(x) (x > 0 ? x : -x)

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
	//ft_printf("x0 = %d; y0 = %d; x1 = %d; y1 = %d; dx = %d; dy = %d\n", x, y, x1, y1, dx, dy);
	while (i)
	{
		mlx->img_data[abs.x_abs + abs.y_abs * mlx->line_size] = color;
		//ft_printf("x = %d; y = %d error = %d\n", x_abs, y_abs, error);
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
		while (x < (size_t)mlx->points[y][0])
		{
			if (mlx->points[y][x + 1]->right)
				mlx->points[y][x + 2]->abs = draw_vector(mlx, mlx->points[y][x + 1]->right, mlx->points[y][x + 1]->abs, mlx->points[y][x + 1]->color);
			if (mlx->points[y][x + 1]->down)
				mlx->points[y + 1][x + 1]->abs = draw_vector(mlx, mlx->points[y][x + 1]->down, mlx->points[y][x + 1]->abs, mlx->points[y][x + 1]->color);
			x++;
		}
		y++;
	}
}

int		deal_key(int key, void *param)
{
	t_mlx	mlx;
	size_t	i;
	int		width;
	int		height;

	i = 0;
	mlx = *(t_mlx *)param;
	if (key == 53)
		exit(1);
	if (key == 36)
	{
		mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, mlx.win_width / 2, mlx.win_height / 2);
		ft_bzero(mlx.img_data, mlx.img_width * mlx.img_height * sizeof(int));
	}
	if (key == 258)
		mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, mlx.win_width / 2, mlx.win_height / 2);
	return (0);
}

int		main(void)
{
	t_mlx		mlx;

	mlx.win_width = 800;
	mlx.win_height = 600;
	mlx.img_width = 300;
	mlx.img_height = 300;
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.win_width, mlx.win_height, "fdf");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, mlx.img_width, mlx.img_height);
	mlx.img_data = (int *)mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.line_size, &mlx.endian);
	mlx.line_size /= 4;
	mlx.points = fdf_parce("test_maps/my.fdf");
	set_vector_to_image(&mlx);
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