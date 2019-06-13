/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:39:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/13 05:40:55 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_parce_set_sizes(t_mlx *mlx, int lst_x, int lst_y)
{
	int			tmp_x;

	X_SIZE = lst_x;
	Y_SIZE = lst_y;
	Z_SIZE = (Z_MAX - Z_MIN);
	tmp_x = (lst_x - 1);
	X_MAX = (lst_x - 1);
	Y_MAX = -(lst_y - 1);
	Y_MIN = -(lst_y - 1);
	return (tmp_x);
}

void	fdf_parce_set_params(t_mlx *mlx, t_vertex *vertex, int z, int color)
{
	vertex->x = X_MIN;
	vertex->y = Y_MAX;
	vertex->z = z;
	vertex->color = color;
	vertex->status = 0;
}

void	fdf_write_process(t_mlx *mlx)
{
	t_list		*tmp;
	int			cur_y;
	int			tmp_x;
	size_t		i;

	tmp_x = fdf_parce_set_sizes(mlx, LST_X, LST_Y);
	TMP = LST;
	while (TMP)
	{
		cur_y = TMP_Y;
		X_MIN = tmp_x;
		while (TMP && TMP_Y == cur_y)
		{
			i = TMP_X - 1 + (TMP_Y - 1) * X_SIZE;
			if (!(POINTS[i] = (t_vertex *)malloc(sizeof(t_vertex))))
				fdf_clear_exit(mlx, "point array element is not allocated\n");
			fdf_parce_set_params(mlx, POINTS[i], TMP_Z, TMP_COLOR);
			TMP = TMP_NEXT;
			if (TMP && TMP_Y == cur_y)
				X_MIN -= 2;
		}
		if (TMP)
			Y_MAX += 2;
	}
	ft_lstdel(&LST, ft_lstclear);
}

void	validate(t_mlx *mlx)
{
	t_list	*tmp;
	int		x_value;
	int		y_value;

	TMP = LST;
	x_value = TMP_X;
	while (TMP)
	{
		y_value = TMP_Y;
		if (TMP_X != x_value)
			fdf_clear_exit(mlx, "map invalid\n");
		while (TMP && TMP_Y == y_value)
			TMP = TMP_NEXT;
	}
}

t_mlx	*fdf_parce(t_mlx *mlx, int fd)
{
	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		fdf_clear_exit(mlx, "mlx is not allocated\n");
	MLX_PTR = NULL;
	WIN_PTR = NULL;
	POINTS = NULL;
	LST = NULL;
	Z_MIN = 0;
	Z_MAX = 0;
	get_file(mlx, fd);
	validate(mlx);
	if (!(POINTS = (t_vertex **)ft_memalloc(
		sizeof(t_vertex *) * (LST_X * LST_Y + 1))))
		fdf_clear_exit(mlx, "point array is not allocated\n");
	fdf_write_process(mlx);
	reparce_colors(mlx);
	return (mlx);
}
