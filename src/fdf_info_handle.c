/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_info_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:53:17 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/13 05:23:01 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*get_info_str(t_mlx *mlx, char *base, int value)
{
	char	*tmp;
	char	*res;

	if (!(tmp = ft_itoa(value)))
		fdf_clear_exit(mlx, "ft_itoa could not allocate memory");
	if (!(res = ft_strjoin(base, tmp)))
	{
		ft_strdel(&tmp);
		fdf_clear_exit(mlx, "ft_strjoin could not allocate memory");
	}
	ft_strdel(&tmp);
	return (res);
}

void		info_init(t_mlx *mlx)
{
	INFO_WIDTH = 140;
	INFO_HEIGHT = 180;
	INFO_PTR = mlx_new_image(MLX_PTR, INFO_WIDTH, INFO_HEIGHT);
	INFO_DATA = (int *)mlx_get_data_addr(INFO_PTR,
	&INFO_BPP, &INFO_LINE_SIZE, &INFO_ENDIAN);
	INFO_LINE_SIZE /= 4;
	MENU_PTR = mlx_xpm_file_to_image(MLX_PTR,
	"src/menu.xpm", &MENU_WIDTH, &MENU_HEIGHT);
	MENU_BUTTON_PTR = mlx_xpm_file_to_image(MLX_PTR, "src/menu_button.xpm",
	&MENU_BUTTON_WIDTH, &MENU_BUTTON_HEIGHT);
	MENU_BUTTON_MODE = 1;
	MENU_MODE = 0;
}

void		draw_info(t_mlx *mlx)
{
	char	*info;
	int		x;

	x = 0;
	while (x < 5)
	{
		if (x == 0)
			info = get_info_str(mlx, "size:  ", VECTOR_SIZE);
		else if (x == 1)
			info = get_info_str(mlx, "depth: ", DEPTH);
		else if (x == 2)
			info = get_info_str(mlx, "x:     ", (X_ANGLE) * (180 / 2));
		else if (x == 3)
			info = get_info_str(mlx, "y:     ", (Y_ANGLE) * (180 / M_PI));
		else if (x == 4)
			info = get_info_str(mlx, "z:     ", (Z_ANGLE) * (180 / M_PI));
		mlx_string_put(MLX_PTR, WIN_PTR, 20, x * 30 + 10, PLANE_COLOR, info);
		ft_strdel(&info);
		x++;
	}
}
