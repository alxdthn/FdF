/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 04:34:07 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/13 16:07:34 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_pixel(t_mlx *mlx, t_points *p)
{
	int		color;

	if (COLOR_STATUS)
		color = get_gradient(&p->p1, &p->p2, &p->delta, &p->start);
	else
		color = DEFAULT_COLOR;
	if (p->p1.x >= 0 && p->p1.y >= 0
	&& p->p1.x < WIN_WIDTH && p->p1.y < WIN_HEIGHT)
		IMG_DATA[p->p1.x + p->p1.y * LINE_SIZE] = color;
}

void	bresenhem(t_mlx *mlx, t_points *p)
{
	int		error;
	int		error2;

	error = p->delta.x - p->delta.y;
	while (p->p1.x != p->p2.x || p->p1.y != p->p2.y)
	{
		set_pixel(mlx, p);
		error2 = error * 2;
		if (error2 > -p->delta.y)
		{
			error -= p->delta.y;
			p->p1.x += p->dir.x;
		}
		else if (error2 < p->delta.x)
		{
			error += p->delta.x;
			p->p1.y += p->dir.y;
		}
	}
}

void	draw_line(t_mlx *mlx, t_vertex *p1, t_vertex *p2)
{
	t_points	p;

	if (p1->status == 0)
		render(mlx, p1);
	if (p2->status == 0)
		render(mlx, p2);
	if ((p1->rendered.x < 0 || p1->rendered.x > WIN_WIDTH)
	&& (p1->rendered.y < 0 || p1->rendered.y > WIN_HEIGHT)
	&& (p2->rendered.x < 0 || p2->rendered.x > WIN_WIDTH)
	&& (p2->rendered.y < 0 || p2->rendered.y > WIN_HEIGHT))
		return ;
	p.start = p1->rendered;
	p.p1 = p1->rendered;
	p.p2 = p2->rendered;
	p.delta.x = ABS(p.p2.x - p.p1.x);
	p.delta.y = ABS(p.p2.y - p.p1.y);
	p.dir.x = p.p1.x < p.p2.x ? 1 : -1;
	p.dir.y = p.p1.y < p.p2.y ? 1 : -1;
	bresenhem(mlx, &p);
}

void	draw_vectors(t_mlx *mlx)
{
	int		x;
	int		y;
	int		current;

	y = 0;
	x = 0;
	while (y < Y_SIZE)
	{
		current = x + y * X_SIZE;
		if (x + 1 < X_SIZE)
			draw_line(mlx, POINTS[current], POINTS[x + 1 + y * X_SIZE]);
		if (y + 1 < Y_SIZE)
			draw_line(mlx, POINTS[current], POINTS[x + (y + 1) * X_SIZE]);
		POINTS[current]->status = 0;
		x++;
		if (x == X_SIZE)
		{
			x = 0;
			y++;
		}
	}
}
