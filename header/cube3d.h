/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:43:25 by graja             #+#    #+#             */
/*   Updated: 2022/01/07 12:50:28 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

// a color typedef for HSV colors
typedef struct s_hsv {
	double	h;
	double	s;
	double	v;
}	t_hsv;

// a color typedef for ARGB colors like in MiniLibX
typedef struct s_color {
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

// the basic data type for handling the minilibx
typedef struct s_data {
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				type;
	size_t			win_x;		//windowsize x
	size_t			win_y;		//windowsize y
	unsigned char	tilesize;		//size of a game tile == texture size in Bit
	unsigned char	fov;			//field of view of player in degrees
	unsigned char	speed;			//player speed in pixel of gametile / movement unit
	float			rotspeed;	//player rotation speed;
	float			dir;		//player look direction
	float			px;		//player x position
	float			py;		//player y position
	t_color			cfloor_far;	//floor color
	t_color			cfloor_near;	//floor color
	int				csky;	//sky color
	int				**map;	//2d array, map representation from cub file
	size_t			mapx;
	size_t			mapy;		//dimension of loaded map
}	t_data;

// common: colors.c
int		ft_make_trgb(int t, int r, int g, int b);
int		ft_make_color(t_color src);
t_color	ft_rgb2col(int t, int r, int g, int b);
t_hsv	ft_interpolate_hsv(t_hsv col1, t_hsv col2, int i, int maxi);
// common: col_hsv2rgb.c
t_color	hsv2rgb(t_hsv in);
// common: rgb2hsv.c
t_hsv	rgb2hsv(t_color in);
// common: draw.c
void	ft_draw_pixel(t_data *data, int x, int y, int color);
void	ft_draw_background(t_data *data);
void	ft_draw_rect(t_data *data, int x, int y, int l, int w, int col);
void	ft_draw_circle(t_data *d, int or_x, int or_y, float r, int col);
void	ft_draw_line(t_data *data, int x, int y, int a, int b);
void	ft_draw_angeled(t_data *data, int x, int y, float alpha, int len);
// common: hooks.c
int		ft_loop_hook(t_data *img);
int		ft_key_hook(int code, t_data *data);
int		ft_mouse_hook(int button, int x, int y, t_data *data);
// common: load_map.c
void	ft_initMap(t_data *data, char *path);
// common: load_map_utils.c
void	ft_initialize_player(t_data *d, size_t x, size_t y, char dir);
void	ft_getPlayerPos(t_data *d, size_t *x, size_t *y);
// common: map2d.c
void	ft_draw2dmap(t_data *data);
void	ft_showPlayer(t_data *data);
void	ft_movePlayer(t_data *data,int flag);
// common: math.c
float	ft_deg2rad(float deg);
float	ft_rad2deg(float rad);
void	ft_rotatePlayer(t_data *data, int flag);
void	ft_leftright(t_data *data, float *newx, float *newy, int flag);
void	ft_forbac(t_data *data, float *newx, float *newy, int flag);
// common: load_map.c
void	ft_initMap(t_data *data, char *path);
// common: map2d.c
void	ft_draw2dmap(t_data *data);
// common: raycast.c
void	ft_castRay(t_data *d, size_t x, size_t y);
// main
t_data	*ft_blank(t_data *data);
int		the_end(t_data *data);
// error.c
void	fehlt_map(t_data *data, char *path, int type);
//void	ft_init_window(t_data *data, int x, int y, int i);

#endif
