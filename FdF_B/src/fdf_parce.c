/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:39:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/04 19:06:34 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t		ft_wrdncount(char const *s, size_t size, char c)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] && i < size)
	{
		while (s[i] && i < size && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && i < size && s[i] != c)
			i++;
	}
	return (count);
}

void	get_file_core(t_mlx *mlx, char *str)
{
	size_t	i;
	size_t	x;
	size_t	y;

	i = 0;
	y = 0;
	while (str[i])
	{
		x = 0;
		POINTS[y] = (t_point **)malloc(sizeof(t_point *) * (X_SIZE + 1));
		while (str[i] && str[i] != '\n')
		{
			if (ft_isdigit(str[i]))
			{
				POINTS[y][x] = (t_point *)malloc(sizeof(t_point));
				POINTS[y][(size_t)X_SIZE] = NULL;
				if ((POINTS[y][x]->z = ft_atoi(str + i)) > Z_MAX)
					Z_MAX = POINTS[y][x]->z;
				if (POINTS[y][x]->z < Z_MIN)
					Z_MIN = POINTS[y][x]->z;
				POINTS[y][x]->color = DEFAULT_COLOR;
				x++;
				while (ft_isdigit(str[i]))
					i++;
			}
			else
				i++;
		}
		if (str[i] == '\n')
			i++;
		y++;
	}
}

void		get_file(t_mlx *mlx, char *file)
{
	char	*str;
	char	buf[BUFF];
	ssize_t	ret;

	Z_MAX = 0;
	Z_MIN = 0;
	if ((ret = ft_read_to_str(file, &str, BUFF)) > 0)
	{
		str[ret - 1] = '\0';
		X_SIZE = ft_wrdncount(str, ft_strclen(str, '\n'), ' ');
		Y_SIZE = ft_wrdcount(str, '\n');
		if ((POINTS = (t_point ***)malloc(sizeof(t_point **) * (Y_SIZE + 1))))
		{
			POINTS[(size_t)Y_SIZE] = NULL;
			get_file_core(mlx, str);		
		}
		ft_strdel(&str);
	}
	X_SIZE = (X_SIZE - 1) / 2;
	Y_SIZE = (Y_SIZE - 1) / 2;
	X_STEP = 1;
	Y_STEP = 1;
}

void	vector_counter(t_mlx *mlx)
{
	size_t		x;
	size_t		y;

	y = 0;
	VECTOR_COUNT = 0;
	while (POINTS[y])
	{
		x = 0;
		while (POINTS[y][x])
		{
			if (POINTS[y][x + 1])
				VECTOR_COUNT++;
			if (POINTS[y + 1])
				VECTOR_COUNT++;
			x++;
		}
		y++;
	}
}

void	set_right_vector(t_mlx *mlx, size_t *i, size_t *x, size_t *y)
{

	VECTORS[*i] = (t_vector *)malloc(sizeof(t_vector));
	VECTORS[*i]->x1 = X_MAX;
	VECTORS[*i]->y1 = Y_MIN;
	VECTORS[*i]->z1 = POINTS[*y][*x]->z;
	VECTORS[*i]->color = POINTS[*y][*x]->color;
	VECTORS[*i]->x2 = X_MAX + X_STEP;
	VECTORS[*i]->y2 = Y_MIN;
	VECTORS[*i]->z2 = POINTS[*y][*x + 1]->z;
	(*i)++;
}

void	set_down_vector(t_mlx *mlx, size_t *i, size_t *x, size_t *y)
{
	VECTORS[*i] = (t_vector *)malloc(sizeof(t_vector));
	VECTORS[*i]->x1 = X_MAX;
	VECTORS[*i]->y1 = Y_MIN;
	VECTORS[*i]->z1 = POINTS[*y][*x]->z;
	VECTORS[*i]->color = POINTS[*y][*x]->color;
	VECTORS[*i]->x2 = X_MAX;
	VECTORS[*i]->y2 = Y_MIN - Y_STEP;
	VECTORS[*i]->z2 = POINTS[*y + 1][*x]->z;
	(*i)++;
}

void	fdf_parce(t_mlx *mlx, char *file)
{
	size_t		i;
	size_t		x;
	size_t		y;

	get_file(mlx, file);
	vector_counter(mlx);
	VECTORS = (t_vector **)malloc(sizeof(t_vector *) * (VECTOR_COUNT + 1));
	VECTORS[VECTOR_COUNT] = NULL;
	y = 0;
	X_MIN = -X_SIZE;
	Y_MAX = Y_SIZE;
	Y_MIN = Y_SIZE;
	while (POINTS[y])
	{
		x = 0;
		X_MAX = -X_SIZE;
		while (POINTS[y][x])
		{
			if (POINTS[y][x + 1])
				set_right_vector(mlx, &i, &x, &y);
			if (POINTS[y + 1])
				set_down_vector(mlx, &i, &x, &y);
			if (POINTS[y][x + 1])
				X_MAX += X_STEP;
			x++;
		}
		if (POINTS[y + 1])
			Y_MIN -= Y_STEP;
		y++;
	}
	X_SIZE = ABS(X_MIN) + ABS(X_MAX);
	Y_SIZE = ABS(Y_MIN) + ABS(Y_MAX);
	Z_SIZE = ABS(Z_MIN) + ABS(Z_MAX);
}
