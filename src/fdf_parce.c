/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:39:20 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/02 00:06:06 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define LST_X ((t_info *)lst->content)->x
#define LST_Y ((t_info *)lst->content)->y
#define LST_Z ((t_info *)lst->content)->z
#define LST_COLOR ((t_info *)lst->content)->color

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
	char	*buf;
	ssize_t	ret;

	lst = NULL;
	if ((ret = ft_read_to_str(file, &buf, BUFF)) > 0)
	{
		buf[ret - 1] = '\0';
		info_set(&info);
		get_file_core(buf, &lst, info);
		ft_strdel(&buf);
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

t_point	***fdf_parce(char *file)
{
	t_point		***points;
	t_list		*lst;
	t_list		*tmp;
	long		cur_y;
	size_t		i;

	lst = get_file(file);
	tmp = lst;
	points = (t_point ***)malloc(sizeof(***points) * (LST_Y + 1));
	points[LST_Y] = NULL;
	i = LST_Y;
	while (lst && i)
	{
		points[LST_Y - 1] = (t_point **)malloc(sizeof(**points) * (LST_X + 1));
		points[LST_Y - 1][0] = (t_point *)(long)LST_X;
		cur_y = LST_Y;
		while (lst && LST_Y == cur_y)
		{
			points[LST_Y - 1][LST_X] = (t_point *)malloc(sizeof(*points));
			if (LST_X < (int)points[LST_Y - 1][0])
				points[LST_Y - 1][LST_X]->right = set_one_vector(LINE, 0);
			else
				points[LST_Y - 1][LST_X]->right = NULL;
			if (points[LST_Y])
				points[LST_Y - 1][LST_X]->down = set_one_vector(0, -LINE);
			else
				points[LST_Y - 1][LST_X]->down = NULL;
			points[LST_Y - 1][LST_X]->z = LST_Z;
			points[LST_Y - 1][LST_X]->color = LST_COLOR;
			points[LST_Y - 1][LST_X]->abs.x_abs = 0;
			points[LST_Y - 1][LST_X]->abs.y_abs = 0; 
			lst = lst->next;
		}
		i--;
	}
	ft_lstdel(&tmp, ft_lstclear);
	return (points);
}
