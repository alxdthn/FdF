/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:39:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/09 02:17:15 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	point_set(t_point *point)
{
	point->x = 1;
	point->y = 1;
	point->z = 0;
	point->color = DEFAULT_COLOR;
}

void	get_file_core(t_mlx *mlx, char *buf, t_list **lst, t_point point)
{
	size_t	i;

	i = 0;
	while (buf[i])
	{
		if (ft_isdigit(buf[i]))
		{
			point.z = ft_atoi(buf + i);
			if (point.z > Z_MAX)
				Z_MAX = point.z;
			if (point.z < Z_MIN)
				Z_MIN = point.z;
			ft_lstadd(lst, ft_lstnew(&point, sizeof(t_point)));
			point.x++;
			while (ft_isdigit(buf[i]))
				i++;
		}
		else
			i++;
		if (buf[i] == '\n')
		{
			point.y++;
			point.x = 1;
		}
	}
}

t_list	*get_file(t_mlx *mlx, char *file)
{
	t_list	*lst;
	t_point	point;
	char	*str;
	char	buf[BUFF];
	ssize_t	ret;

	lst = NULL;
	Z_MAX = 0;
	Z_MIN = 0;
	if ((ret = ft_read_to_str(file, &str, BUFF)) > 0)
	{
		str[ret - 1] = '\0';
		point_set(&point);
		get_file_core(mlx, str, &lst, point);
		ft_strdel(&str);
	}
	return (lst);
}

int		set_sizes(t_mlx *mlx, int lst_x, int lst_y)
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

t_mlx	*fdf_parce(char *file)
{
	t_mlx		*mlx;
	t_list		*lst;
	size_t		cur_y;
	size_t		i;
	int			tmp_x;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	lst = get_file(mlx, file);
	tmp_x = set_sizes(mlx, LST_X, LST_Y);
	POINTS = (t_point **)malloc(sizeof(t_point *) * (LST_X * LST_Y + 1));
	POINTS[LST_X * LST_Y] = NULL;
	while (lst)
	{
		cur_y = LST_Y;
		X_MIN = tmp_x;
		while (lst && LST_Y == cur_y)
		{
			i = LST_X - 1 + (LST_Y - 1) * X_SIZE;
			POINTS[i] = (t_point *)malloc(sizeof(t_point));
			POINTS[i]->x = X_MIN;
			POINTS[i]->y = Y_MAX;
			POINTS[i]->z = LST_Z;
			POINTS[i]->color = LST_COLOR;
			POINTS[i]->prespective = 0;
			lst = lst->next;
			if (lst == NULL || LST_Y != cur_y)
				break ;
			X_MIN -= 2;
		}
		if (!lst)
			break ;
		Y_MAX += 2;
	}
	return (mlx);
}
