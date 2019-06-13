/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_clear_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:47:02 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/13 06:03:25 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_exit(char *message, char usage)
{
	if (message)
		ft_putstr_fd(message, 2);
	if (usage)
		ft_putstr("usage: fdf map.fdf\n");
	exit(EXIT_FAILURE);
}

void	fdf_clear_exit(t_mlx *mlx, char *message)
{
	ft_putstr_fd(message, 2);
	if (LST)
		ft_lstdel(&LST, ft_lstclear);
	if (POINTS)
	{
		if (POINTS[0])
			ft_arraydel((void **)POINTS);
		ft_memdel((void **)POINTS);
	}
	ft_memdel((void **)&mlx);
	exit(EXIT_FAILURE);
}
