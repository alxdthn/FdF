/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:40:26 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/04 20:21:00 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include "../libft/ft_printf/includes/ft_printf.h"
# define BUFF 5000
# define DEFAULT_COLOR 0x42f4bf
# define MARGIN 5

# define ESC 53
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define R_SHIFT 258
# define ENTER 36

# define MLX_PTR mlx->mlx_ptr
# define WIN_PTR mlx->win_ptr
# define IMG_PTR mlx->img.ptr
# define BPP mlx->img.bpp
# define LINE_SIZE mlx->img.line_size
# define ENDIAN mlx->img.endian
# define VECTOR_COUNT mlx->img.vector_count
# define VECTOR_SIZE mlx->img.vector_size
# define VECTORS mlx->img.vectors
# define POINTS mlx->img.points
# define X_SIZE mlx->img.x_size
# define Y_SIZE mlx->img.y_size
# define Z_SIZE mlx->img.z_size
# define X_MAX mlx->img.x_max
# define Y_MAX mlx->img.y_max
# define Z_MAX mlx->img.z_max
# define X_MIN mlx->img.x_min
# define Y_MIN mlx->img.y_min
# define Z_MIN mlx->img.z_min
# define X_STEP mlx->img.x_step
# define Y_STEP mlx->img.y_step
# define IMG_DATA mlx->img.data
# define WIN_WIDTH mlx->width
# define WIN_HEIGHT mlx->height
# define IMG_WIDTH mlx->img.width
# define IMG_HEIGHT mlx->img.height
# define ANGLE mlx->img.angle
# define ABS(x) ((x) > 0 ? (x) : -(x))

typedef struct		s_point
{
	int				z;
	int				color;
}					t_point;

typedef struct		s_vector
{
	double			x1;
	double			y1;
	double			z1;
	double			x2;
	double			y2;
	double			z2;
	int				color;
}					t_vector;

typedef struct		s_image
{
	t_point			***points;
	t_vector		**vectors;
	void			*ptr;
	int				*data;
	size_t			width;
	size_t			height;
	double			x_size;
	double			y_size;
	double			z_size;
	int				vector_size;
	int				vector_count;
	int				line_size;
	double			x_min;
	double			x_max;
	double			y_min;
	double			y_max;
	double			z_max;
	double			z_min;
	double			angle;
	int				x_step;
	int				y_step;
	int				bpp;
	int				endian;
}					t_image;

typedef struct		s_mlx
{
	t_image			img;
	void			*mlx_ptr;
	void			*win_ptr;
	size_t			width;
	size_t			height;
}					t_mlx;

void	fdf_parce(t_mlx *mlx, char *file);

#endif