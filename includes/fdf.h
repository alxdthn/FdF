/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:40:26 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/02 00:04:15 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include "ft_printf.h"
# define BUFF 5000
# define DEFAULT_COLOR 0x42f4bf
# define LINE 50

typedef struct		s_abs
{
	int				x_abs;
	int				y_abs;
}					t_abs;

typedef struct		s_info
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_info;

typedef struct		s_vector
{
	int				x;
	int				y;
}					t_vector;

typedef struct		s_point
{
	t_vector		*right;
	t_vector		*down;
	t_abs			abs;
	int				z;
	int				color;
}					t_point;

typedef struct		s_mlx
{
	int				bpp;
	int				endian;
	int				win_width;
	int				win_height;
	int				line_size;
	int				img_width;
	int				img_height;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*img_data;
	t_point			***points;
}					t_mlx;

t_point		***fdf_parce(char *file);

#endif