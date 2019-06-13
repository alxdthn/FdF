/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:40:26 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/13 15:56:49 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include "../libft/includes/libft.h"
# define BUFF 5000
# define PLANE_COLOR 0x4328F4
# define VERTEX_COLOR 0xff4dff
# define DEFAULT_COLOR 0x4328F4
# define MARGIN 20
# define ROTATE_STEP 0.0174532925199433
# define SIZE_STEP VECTOR_SIZE / 100 * 1
# define DEPTH_STEP 1
# define ABS(x) ((x) > 0 ? (x) : -(x))
# define PI_X2 6.283185307179586476925286

# define ESC 53
# define CTRL 256
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define R_SHIFT 258
# define SPACE 49
# define ENTER 36
# define RIGHT 124
# define LEFT 123
# define UP 126
# define DOWN 125
# define Z_KEY 6
# define X_KEY 7
# define C_KEY 8
# define Q_KEY 12
# define W_KEY 13
# define E_KEY 14
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define R_KEY 15
# define F_KEY 3
# define PLUS_KEY 69
# define MINUS_KEY 78

# define LST_X ((t_point *)mlx->lst->content)->x
# define LST_Y ((t_point *)mlx->lst->content)->y
# define LST_Z ((t_point *)mlx->lst->content)->z
# define LST_COLOR ((t_point *)mlx->lst->content)->color
# define LST_CONTENT (t_point *)mlx->lst->content
# define LST_CONTENT_SIZE mlx->lst->content_size
# define LST mlx->lst
# define LST_NEXT mlx->lst->next

# define TMP_X ((t_point *)tmp->content)->x
# define TMP_Y ((t_point *)tmp->content)->y
# define TMP_Z ((t_point *)tmp->content)->z
# define TMP_COLOR ((t_point *)tmp->content)->color
# define TMP_CONTENT (t_point *)tmp->content
# define TMP_CONTENT_SIZE tmp->content_size
# define TMP tmp
# define TMP_NEXT tmp->next

# define COLOR_STATUS mlx->img.color_status

# define MLX_PTR mlx->mlx_ptr
# define WIN_PTR mlx->win_ptr
# define IMG_PTR mlx->img.ptr
# define IMG_DATA mlx->img.data
# define INFO_PTR mlx->info.ptr
# define INFO_DATA mlx->info.data
# define INFO_WIDTH mlx->info.width
# define INFO_HEIGHT mlx->info.height
# define INFO_BPP mlx->info.bpp
# define INFO_LINE_SIZE mlx->info.line_size
# define INFO_ENDIAN mlx->info.endian

# define MENU_PTR mlx->info.menu.ptr
# define MENU_WIDTH mlx->info.menu.width
# define MENU_HEIGHT mlx->info.menu.height
# define MENU_MODE mlx->info.menu.status
# define MENU_BUTTON_PTR mlx->info.menu_button.ptr
# define MENU_BUTTON_WIDTH mlx->info.menu_button.width
# define MENU_BUTTON_HEIGHT mlx->info.menu_button.height
# define MENU_BUTTON_MODE mlx->info.menu_button.status

# define WIN_WIDTH mlx->width
# define WIN_HEIGHT mlx->height

# define BPP mlx->img.bpp
# define LINE_SIZE mlx->img.line_size
# define ENDIAN mlx->img.endian

# define START_SIZE mlx->img.start_size
# define VECTOR_SIZE mlx->img.size
# define POINTS mlx->img.points
# define POSITION mlx->img
# define DEPTH mlx->img.depth

# define X_SIZE mlx->img.x_size
# define Y_SIZE mlx->img.y_size
# define Z_SIZE mlx->img.z_size

# define X_MAX mlx->img.x_max
# define X_MIN mlx->img.x_min
# define Y_MAX mlx->img.y_max
# define Y_MIN mlx->img.y_min
# define Z_MAX mlx->img.z_max
# define Z_MIN mlx->img.z_min

# define X_ANGLE mlx->img.x_angle
# define Y_ANGLE mlx->img.y_angle
# define Z_ANGLE mlx->img.z_angle

typedef	struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef	struct		s_points
{
	t_point			p1;
	t_point			p2;
	t_point			start;
	t_point			delta;
	t_point			dir;
}					t_points;

typedef struct		s_vertex
{
	t_point			rendered;
	int				color;
	int				x;
	int				y;
	int				z;
	char			status;
}					t_vertex;

typedef struct		s_image
{
	t_vertex		**points;
	int				posx;
	int				posy;
	int				color_status;
	int				start_size;
	int				size;
	int				depth;
	void			*ptr;
	int				*data;
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
}					t_image;

typedef struct		s_xpm
{
	void			*ptr;
	int				width;
	int				height;
	char			status;
}					t_xpm;

typedef struct		s_info
{
	t_xpm			menu;
	t_xpm			menu_button;
	int				*data;
	void			*ptr;
	int				width;
	int				height;
	int				bpp;
	int				endian;
	int				line_size;
}					t_info;

typedef struct		s_mouse
{
	int				posx;
	int				posy;
	int				last_posx;
	int				last_posy;
	char			startus;
}					t_mouse;

typedef struct		s_mlx
{
	t_image			img;
	t_info			info;
	t_mouse			mouse;
	t_list			*lst;
	void			*mlx_ptr;
	void			*win_ptr;
	int				width;
	int				height;
}					t_mlx;

void				fdf_clear_exit(t_mlx *mlx, char *message);
void				fdf_exit(char *message, char usage);

t_mlx				*fdf_parce(t_mlx *mlx, int fd);
void				get_file(t_mlx *mlx, int fd);
void				fdf_switch(char *mode1, char *mode2);

int					deal_key(int key, t_mlx *mlx);
int					key_press(int key, t_mlx *mlx);
int					mouse_press(int button, int x, int y, t_mlx *mlx);
int					mouse_move(int x, int y, t_mlx *mlx);
int					mouse_release(int button, int x, int y, t_mlx *mlx);

void				draw_mlx(t_mlx *mlx);
void				draw_vectors(t_mlx *mlx);
void				draw_info(t_mlx *mlx);
void				draw_line(t_mlx *mlx, t_vertex *p1, t_vertex *p2);
void				render(t_mlx *mlx, t_vertex *point);
void				info_init(t_mlx *mlx);
void				set_start_param(t_mlx *mlx);

int					depth_handle(t_mlx *mlx, int key);
int					move_handle(t_mlx *mlx, int key);
int					size_handle(t_mlx *mlx, int key);
void				rotate_handle(t_mlx *mlx, int key);

void				reparce_colors(t_mlx *mlx);
int					parce_gradient(t_mlx *mlx, t_vertex *p);
int					get_gradient(t_point *current, t_point *end,
					t_point *delta, t_point *start);
double				percentage(int start, int end, int current);
void				get_light(int *value, int start, int end, double percent);

#endif
