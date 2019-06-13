/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 23:12:10 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/13 05:42:01 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	x_rotate(t_mlx *mlx, t_point *point)
{
	double	cos_angle;
	double	sin_angle;
	int		tmp_y;
	int		tmp_z;

	cos_angle = cos(X_ANGLE);
	sin_angle = sin(X_ANGLE);
	tmp_y = point->y;
	tmp_z = point->z;
	point->y = tmp_y * cos_angle + tmp_z * sin_angle;
	point->z = -tmp_y * sin_angle + tmp_z * cos_angle;
}

static void	y_rotate(t_mlx *mlx, t_point *point)
{
	double	cos_angle;
	double	sin_angle;
	int		tmp_x;
	int		tmp_z;

	cos_angle = cos(Y_ANGLE);
	sin_angle = sin(Y_ANGLE);
	tmp_x = point->x;
	tmp_z = point->z;
	point->x = tmp_x * cos_angle + tmp_z * sin_angle;
	point->z = -tmp_x * sin_angle + tmp_z * cos_angle;
}

static void	z_rotate(t_mlx *mlx, t_point *point)
{
	double	cos_angle;
	double	sin_angle;
	int		tmp_x;
	int		tmp_y;

	cos_angle = cos(Z_ANGLE);
	sin_angle = sin(Z_ANGLE);
	tmp_x = point->x;
	tmp_y = point->y;
	point->x = tmp_x * cos_angle - tmp_y * sin_angle;
	point->y = tmp_x * sin_angle + tmp_y * cos_angle;
}

static void	size_set(t_mlx *mlx, t_point *res, t_vertex *point)
{
	res->x = point->x * VECTOR_SIZE;
	res->y = point->y * VECTOR_SIZE;
	res->z = point->z * VECTOR_SIZE * DEPTH;
	res->color = point->color;
}

void		render(t_mlx *mlx, t_vertex *point)
{
	size_set(mlx, &point->rendered, point);
	if (Z_ANGLE)
		z_rotate(mlx, &point->rendered);
	if (X_ANGLE)
		x_rotate(mlx, &point->rendered);
	if (Y_ANGLE)
		y_rotate(mlx, &point->rendered);
	point->rendered.x = WIN_WIDTH / 2 + point->rendered.x + POSITION.posx;
	point->rendered.y = WIN_HEIGHT / 2 - point->rendered.y + POSITION.posy;
	point->status = 1;
}
