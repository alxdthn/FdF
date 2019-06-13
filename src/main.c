/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 09:52:28 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/13 06:07:23 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_mlx(t_mlx *mlx)
{
	draw_vectors(mlx);
	mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_PTR, 0, 0);
	draw_info(mlx);
	ft_bzero(IMG_DATA, WIN_WIDTH * WIN_HEIGHT * 4);
	if (MENU_MODE)
		mlx_put_image_to_window(MLX_PTR, WIN_PTR, MENU_PTR, 0, 160);
	if (MENU_BUTTON_MODE)
		mlx_put_image_to_window(MLX_PTR, WIN_PTR, MENU_BUTTON_PTR, 0,
		WIN_HEIGHT - 93);
}

void	set_start_param(t_mlx *mlx)
{
	VECTOR_SIZE = START_SIZE;
	X_ANGLE = 0.523599;
	Y_ANGLE = 0.523599;
	Z_ANGLE = 0;
	POSITION.posx = 0;
	POSITION.posy = 0;
	DEPTH = 1;
}

void	img_init(t_mlx *mlx)
{
	IMG_PTR = mlx_new_image(MLX_PTR, WIN_WIDTH, WIN_HEIGHT);
	IMG_DATA = (int *)mlx_get_data_addr(IMG_PTR, &BPP, &LINE_SIZE, &ENDIAN);
	LINE_SIZE /= 4;
	if (X_SIZE > (Y_SIZE + Z_SIZE))
		START_SIZE = (WIN_WIDTH - WIN_WIDTH / 100 * MARGIN) / (X_SIZE * 2);
	else
		START_SIZE = (WIN_WIDTH - WIN_WIDTH / 100 * MARGIN)
		/ ((Y_SIZE + Z_SIZE) * 2);
	set_start_param(mlx);
	COLORED = 0;
}

void	fdf_switch(char *mode1, char *mode2)
{
	char tmp;

	tmp = *mode1;
	*mode1 = *mode2;
	*mode2 = tmp;
}

int		main(int ac, char **av)
{
	t_mlx	*mlx;
	int		fd;

	if (ac != 2)
		fdf_exit(NULL, 1);
	if (ft_check_file_format(av[1], ".fdf"))
		fdf_exit("file is not .fdf\n", 1);
	if ((fd = open(av[1], O_RDONLY)) < 3)
		fdf_exit("can't open file\n", 0);
	mlx = fdf_parce(mlx, fd);
	WIN_WIDTH = 2560;
	WIN_HEIGHT = 1440;
	MLX_PTR = mlx_init();
	WIN_PTR = mlx_new_window(MLX_PTR, WIN_WIDTH, WIN_HEIGHT, "fdf by nalexand");
	img_init(mlx);
	info_init(mlx);
	mlx_key_hook(WIN_PTR, deal_key, mlx);
	mlx_hook(WIN_PTR, 2, 0, key_press, mlx);
	mlx_hook(WIN_PTR, 4, 0, mouse_press, mlx);
	mlx_hook(WIN_PTR, 5, 0, mouse_release, mlx);
	mlx_hook(WIN_PTR, 6, 0, mouse_move, mlx);
	draw_mlx(mlx);
	mlx_loop(MLX_PTR);
	return (0);
}
