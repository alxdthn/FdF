/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 05:25:52 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/13 16:08:29 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_z(t_mlx *mlx, t_point *point, char *buf, size_t *i)
{
	point->z = ft_atoi(buf + *i);
	if (!Z_MIN)
		Z_MIN = point->z;
	if (!Z_MAX)
		Z_MAX = point->z;
	if (point->z > Z_MAX)
		Z_MAX = point->z;
	if (point->z < Z_MIN)
		Z_MIN = point->z;
	while (ft_isdigit(buf[*i]) || buf[*i] == '-')
		(*i)++;
}

static void	get_clr(t_mlx *mlx, t_point *point, char *buf, size_t *i)
{
	int		base;

	(*i)++;
	base = 10;
	if (buf[*i] && buf[*i] == '0')
	{
		(*i)++;
		if (buf[*i] && buf[*i] == 'x')
		{
			(*i)++;
			base = 16;
		}
		else if (buf[*i] && buf[*i] != '0' && ft_isdigit(buf[*i]))
			base = 8;
		else
			fdf_clear_exit(mlx, "map invalid\n");
	}
	else if (buf[*i] && buf[*i] != '0' && ft_isdigit(buf[*i]))
		base = 10;
	else
		fdf_clear_exit(mlx, "map invalid\n");
	point->color = ft_atoi_base(buf + *i, base);
	while (buf[*i] && buf[*i] != ' ')
		(*i)++;
}

static void	get_file_process(t_mlx *mlx, char *buf, t_point *point)
{
	size_t	i;

	i = 0;
	while (buf[i])
	{
		if (ft_isdigit(buf[i]) || buf[i] == '-')
		{
			get_z(mlx, point, buf, &i);
			point->color = PLANE_COLOR;
			if (buf[i] == ',')
				get_clr(mlx, point, buf, &i);
			ft_lstadd(&LST, ft_lstnew(point, sizeof(t_point)));
			if (!LST)
				fdf_clear_exit(mlx, "list is not allocated\n");
			point->x++;
		}
		else
			i++;
		if (buf[i] == '\n')
		{
			point->y++;
			point->x = 1;
		}
	}
}

void		get_file(t_mlx *mlx, int fd)
{
	t_point	point;
	char	*str;
	ssize_t	ret;

	if ((ret = ft_read_to_str(fd, &str, BUFF)) < 0)
		fdf_clear_exit(mlx, "buf from read is not allocated\n");
	if (ret < 2)
		fdf_clear_exit(mlx, "map invalid\n");
	if (str[ret - 1] != '\n')
		fdf_clear_exit(mlx, "no breakline in end of file\n");
	str[ret - 1] = '\0';
	point.x = 1;
	point.y = 1;
	point.z = 0;
	get_file_process(mlx, str, &point);
	if (LST_X == 1 && LST_Y == 1)
		fdf_clear_exit(mlx, "one point is not correct\n");
	ft_strdel(&str);
}
