/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:39:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/02 19:09:46 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	info_set(t_info *info)
{
	info->x = 1;
	info->y = 1;
	info->z = 0;
	info->color = DEFAULT_COLOR;
}

void	get_file_core(char *buf, t_list **lst, t_info info)
{
	size_t	i;

	i = 0;
	while (buf[i])
	{
		if (ft_isdigit(buf[i]))
		{
			info.z = ft_atoi(buf + i);
			ft_lstadd(lst, ft_lstnew(&info, sizeof(info)));
			info.x++;
			while (ft_isdigit(buf[i]))
				i++;
		}
		else
			i++;
		if (buf[i] == '\n')
		{
			info.y++;
			info.x = 1;
		}
	}
}

t_list	*get_file(char *file)
{
	t_list	*lst;
	t_info	info;
	char	*str;
	char	buf[BUFF];
	ssize_t	ret;

	lst = NULL;
	if ((ret = ft_read_to_str(file, &str, BUFF)) > 0)
	{
		str[ret - 1] = '\0';
		info_set(&info);
		get_file_core(str, &lst, info);
		ft_strdel(&str);
	}
	return (lst);
}

t_vector *set_one_vector(int x, int y)
{
	t_vector 	*vector;

	vector = (t_vector *)malloc(sizeof(*vector));
	vector->x = x;
	vector->y = y;
	return (vector);
}

t_point	***fdf_parce(char *file, int *points_x_count, int *points_y_count)
{
	t_point		***points;
	t_list		*lst;
	size_t		cur_y;
	size_t		x_size;

	lst = get_file(file);
	points = (t_point ***)malloc(sizeof(***points) * (LST_Y + 1));
	points[LST_Y] = NULL;
	*points_x_count = LST_X;
	*points_y_count = LST_Y;
	while (lst)
	{
		points[LST_Y - 1] = (t_point **)malloc(sizeof(*points) * (LST_X + 1));
		points[LST_Y - 1][LST_X] = NULL;
		cur_y = LST_Y;
		x_size = LST_X;
		while (lst && LST_Y == cur_y)
		{
			points[LST_Y - 1][LST_X - 1] = (t_point *)malloc(sizeof(t_point));
			if (LST_X < x_size)
				points[LST_Y - 1][LST_X - 1]->right = set_one_vector(1, 0);
			else
				points[LST_Y - 1][LST_X - 1]->right = NULL;
			if (points[LST_Y])
				points[LST_Y - 1][LST_X - 1]->down = set_one_vector(0, -1);
			else
				points[LST_Y - 1][LST_X - 1]->down = NULL;
			points[LST_Y - 1][LST_X - 1]->z = LST_Z;
			points[LST_Y - 1][LST_X - 1]->color = LST_COLOR;
			points[LST_Y - 1][LST_X - 1]->abs.x_abs = 0;
			points[LST_Y - 1][LST_X - 1]->abs.y_abs = 0;
			lst = lst->next;
		}
	}
	//ft_lstdel(&tmp, ft_lstclear);
	return (points);
}
