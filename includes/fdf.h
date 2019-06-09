/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:40:26 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/09 03:30:55 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include "../../libft/includes/libft.h"
# include "../../libft/ft_printf/includes/ft_printf.h"
# define BUFF 5000
# define DEFAULT_COLOR 0x42f4bf
# define LINE 100
# define MARGIN 20
# define ROTATE_STEP M_PI / 180

# define ESC 53
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define R_SHIFT 258
# define ENTER 36
# define RIGHT 124
# define LEFT 123
# define UP 126
# define DOWN 125
# define Z_KEY 6
# define Q_KEY 12
# define W_KEY 13
# define E_KEY 14
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2

# define LST_X (size_t)((t_point *)lst->content)->x
# define LST_Y (size_t)((t_point *)lst->content)->y
# define LST_Z (size_t)((t_point *)lst->content)->z
# define LST_COLOR ((t_point *)lst->content)->color
# define LST_CONTENT (t_point *)lst->content
# define LST_CONTENT_SIZE lst->content_size

# define MLX_PTR mlx->mlx_ptr
# define WIN_PTR mlx->win_ptr
# define IMG_PTR mlx->img.ptr
# define BPP mlx->img.bpp
# define LINE_SIZE mlx->img.line_size
# define ENDIAN mlx->img.endian
# define VECTOR_COUNT mlx->img.vector_count
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
# define X_ANGLE mlx->img.x_angle
# define Y_ANGLE mlx->img.y_angle
# define Z_ANGLE mlx->img.z_angle
# define IMG_DATA mlx->img.data
# define WIN_WIDTH mlx->width
# define WIN_HEIGHT mlx->height
# define IMG_WIDTH mlx->img.width
# define IMG_HEIGHT mlx->img.height
# define DOWN_VECTOR mlx->img.down_vector
# define RIGHT_VECTOR mlx->img.right_vector
# define VECTOR_SIZE mlx->img.vector_size
# define ANGLE mlx->img.angle
# define MAP_WIDTH mlx->img.map_width
# define MAP_HEIGHT mlx->img.map_height
# define ABS(x) ((x) > 0 ? (x) : -(x))

typedef struct		s_abs
{
	int				x;
	int				y;
}					t_abs;

typedef struct		s_point
{
	t_abs			abs;
	int				x;
	int				y;
	int				z;
	int				color;
	int				prespective;
}					t_point;


typedef struct		s_image
{
	t_point			**points;
	void			*ptr;
	int				*data;
	size_t			width;
	size_t			height;
	size_t			map_width;
	size_t			map_height;
	double			x_angle;
	double			y_angle;
	double			z_angle;
	int				x_size;
	int				y_size;
	int				z_size;
	int				x_min;
	int				x_max;
	int				y_min;
	int				y_max;
	int				z_max;
	int				z_min;
	int				bpp;
	int				endian;
	int				line_size;
	int				vector_size;
}					t_image;

typedef struct		s_mlx
{
	t_image			img;
	void			*mlx_ptr;
	void			*win_ptr;
	size_t			width;
	size_t			height;
}					t_mlx;

t_mlx	*fdf_parce(char *file);

#endif
