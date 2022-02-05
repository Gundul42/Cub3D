/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:53:42 by flormich          #+#    #+#             */
/*   Updated: 2022/02/05 17:51:38 by graja            ###   ########.fr       */
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

# ifndef CUBEBONUS
#  define CUBEBONUS 0
# endif

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GR "\033[0;32m"
# define YE "\033[0;33m"
# define BL "\033[0;34m"
# define PU "\033[0;35m"
# define CY "\033[0;36m"
# define WH "\033[0;37m"
# define D "\033[0m"

// a typedef for points
typedef struct s_point {
	float	x;
	float	y;
}	t_point;

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

typedef struct s_ray {
	t_point	p;
	float	dir;
	float	dist;
	int		offset;
	int		flag;
}	t_ray;

typedef struct s_test
{
	int		*first;
	int		*last;
}	t_test;

typedef struct s_sprite
{
	t_point	p;
	float	dir;
	float	dist;
	int		code;
	int		walkable;
	int		collectable;
	int		canmove;
	int		isdoor;
}	t_sprite;

typedef struct s_data {
	void			*mlx;
	void			*win2;
	void			*img1;
	void			*img2;
	char			*addr;
	char			*addr1;
	char			*addr2;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				type;
	int				bits_per_pixel2;
	int				line_length2;
	int				endian2;
	int				type2;
	size_t			win_x;
	size_t			win_y;
	size_t			minimap;
	size_t			mini_z;
	unsigned int	tilesize;
	unsigned char	fov;
	unsigned int	dtpp;
	unsigned int	speed;
	float			precision;
	float			rotspeed;
	float			dir;
	float			px;
	float			py;
	float			rotmouse;
	t_color			cfloor_far;
	t_color			cfloor_near;
	int				csky;
	int				run;
	int				correct;
	int				m_map;
	int				mouse;
	int				**map;
	int				**doors;
	int				**dopen;
	size_t			mapx;
	size_t			mapy;
	void			*txt[4];
	void			*sprite[6];
	t_sprite		*slist;
	int				snbr;
	int				chkdoor;
	size_t			doorx;
	size_t			doory;
	float			*zbuf;
	int				part;
	int				sprite_max;
}	t_data;

int		ft_loop_hook(t_data *img);
int		the_end(t_data *data, char *txt, int err);
int		ft_open_file(t_data *data, char *path);
int		ft_get_tex_pixel(t_data *data, int x, int y, int n);
int		ft_check_map_ns(t_data *data, t_point p, float alpha);
int		ft_check_map_we(t_data *data, t_point p, float alpha);
int		ft_make_trgb(int t, int r, int g, int b);
int		ft_make_color(t_color src);
int		ft_str2col(char *str, t_color *mycol);
int		ft_key_hook(int code, t_data *data);
int		ft_get_side(int flag, float alpha);
int		ft_mouse_hook(int button, int x, int y, t_data *data);
int		ft_is_wall(t_data *data, size_t x, size_t y);
int		ft_mouse_in_hook(int x, int y, t_data *data);
int		ft_mouse_out_hook(t_data *data);
int		ft_parse_map_line(t_data *data, char *line);
int		the_end_hook(int code, t_data *d);
int		ft_quad(t_data *data);
int		ft_whatishere(t_data *data, size_t x, size_t y);
float	ft_deg2rad(float deg);
float	ft_rad2deg(float rad);
float	ft_point_dist(t_point a, t_point b);
float	ft_val_alpha(float alpha);
float	ft_get_dist(float x1, float y1, float x2, float y2);
void	ft_mouse_rot_player(t_data *data);
void	ft_map2_mem(t_data *data, char *path, int fd, int skip);
void	ft_load_textures(t_data *data, char **path, int i);
void	ft_get_map_point(t_data *data, t_point p, size_t *x, size_t *y);
void	ft_draw_3d(t_data *data, t_ray ray, int i);
void	ft_destroy_textures(t_data *data);
void	ft_tex_default(t_data *data);
void	ft_init_map(t_data *data, char *path);
void	ft_initialize_player(t_data *d, size_t x, size_t y, char dir);
void	ft_get_player_pos(t_data *d, size_t *x, size_t *y);
void	ft_draw2dmap(t_data *data);
void	ft_map_zoom(t_data *data, int flag);
void	ft_move_player(t_data *data, int flag);
void	ft_load_sprites(t_data *data);
void	ft_destroy_sprites(t_data *data);
void	ft_rotate_player(t_data *data, int flag);
void	ft_leftright(t_data *data, float *newx, float *newy, int flag);
void	ft_forbac(t_data *data, float *newx, float *newy, int flag);
void	ft_init_map(t_data *data, char *path);
void	ft_draw_sprite_pixel(t_data *data, int x, int y);
void	ft_file_nf(t_data *data, char *path);
void	ft_check_head(t_data *data, int fd, int err, int chk);
void	ft_free_tex(char **tex);
void	ft_read_head(t_data *data, char *path, int fd, int err);
void	ft_dump_map(t_data *data);
void	ft_draw_pixel(t_data *data, int x, int y, int color);
void	ft_draw_map_pixel(t_data *data, int x, int y, int color);
void	ft_draw_dot(t_data *data, int i, int j, int color);
void	ft_draw_background(t_data *data);
void	ft_draw_map_bck(t_data *data);
void	ft_draw_fov(t_data *data);
void	ft_dump_ray(t_data *data, t_ray ray);
void	ft_draw_tex(t_data *data, t_point p1, t_point p2, t_ray ray);
void	ft_check_closed_map(t_data *data);
void	ft_map_heading(t_data *data);
void	ft_cleanup_map(t_data *data);
t_data	*ft_blank(t_data *data);
t_color	hsv2rgb(t_hsv in);
t_color	ft_rgb2col(int t, int r, int g, int b);
t_hsv	rgb2hsv(t_color in);
t_hsv	ft_interpolate_hsv(t_hsv col1, t_hsv col2, int i, int maxi);
t_point	ft_get_player_point(t_data *data);
t_point	ft_val_point(t_data *data, t_point p);
t_ray	ft_cast_ray(t_data *d, float alpha);

#endif
