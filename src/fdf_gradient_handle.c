/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_gradient_handle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 02:46:13 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/13 05:10:33 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	percentage(int start, int end, int cur)
{
	double	placement;
	double	distance;

	placement = cur - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

void	get_light(int *value, int start, int end, double percent)
{
	*value = (int)((1 - percent) * start + percent * end);
}

int		get_gradient(t_point *cur, t_point *end, t_point *delta, t_point *start)
{
	double	percent;
	int		red;
	int		green;
	int		blue;

	if (cur->color == end->color)
		return (cur->color);
	if (delta->x > delta->y)
		percent = percentage(start->x, end->x, cur->x);
	else
		percent = percentage(start->y, end->y, cur->y);
	get_light(&red, (start->color >> 16) & 0xFF,
	(end->color >> 16) & 0xFF, percent);
	get_light(&green, (start->color >> 8) & 0xFF,
	(end->color >> 8) & 0xFF, percent);
	get_light(&blue, start->color & 0xFF,
	end->color & 0xFF, percent);
	return ((red << 16) | (green << 8) | blue);
}

int		parce_gradient(t_mlx *mlx, t_vertex *p)
{
	double	percent;
	int		red;
	int		green;
	int		blue;

	if (p->color != PLANE_COLOR)
		return (p->color);
	percent = percentage(Z_MIN, Z_MAX, p->z);
	get_light(&red, (PLANE_COLOR >> 16) & 0xFF,
	(VERTEX_COLOR >> 16) & 0xFF, percent);
	get_light(&green, (PLANE_COLOR >> 8) & 0xFF,
	(VERTEX_COLOR >> 8) & 0xFF, percent);
	get_light(&blue, PLANE_COLOR & 0xFF,
	VERTEX_COLOR & 0xFF, percent);
	return ((red << 16) | (green << 8) | blue);
}

void	reparce_colors(t_mlx *mlx)
{
	size_t	i;

	i = 0;
	while (POINTS[i])
	{
		POINTS[i]->color = parce_gradient(mlx, POINTS[i]);
		i++;
	}
}
