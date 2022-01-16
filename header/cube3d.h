/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:43:25 by graja             #+#    #+#             */
/*   Updated: 2022/01/16 13:53:31 by graja            ###   ########.fr       */
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

// a typedef for points
typedef	struct s_point {
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
	int	offset;
	int	flag;		// 0 = N, 1 = S, 2 = E, 3 = W
}	t_ray;

// the basic data type for handling the minilibx
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
	size_t			win_x;		//windowsize x
	size_t			win_y;		//windowsize y
	size_t			minimap;	//size of minimap
	size_t			miniZ;		//zoom faktor of minimap
	unsigned char	tilesize;		//size of a game tile == texture size in pixel 
	unsigned char	fov;			//field of view of player in degrees
	unsigned int	dtpp;			//distance to projection plane
	unsigned char	speed;			//player speed in pixel of gametile / movement unit
	float			precision;	//precision of ray scanning the smaller the accurate
	float			rotspeed;	//player rotation speed;
	float			dir;		//player look direction
	float			px;		//player x position
	float			py;		//player y position
	t_color			cfloor_far;	//floor color
	t_color			cfloor_near;	//floor color
	int			csky;		//sky color
	int			run;		//true after first key is pressed
	int			correct;	//cos wall correction, default off
	int			mMap;		//miniMap, default off
	int			**map;		//2d array, map representation from cub file
	size_t			mapx;
	size_t			mapy;		//dimension of loaded map
	void			*txt[4];	//texture bitmaps
	void			*sprite;	//sprite bitmaps
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
void	ft_drawMapPixel(t_data *data, int x, int y, int color);
void	ft_drawDot(t_data *data, int i, int j);
void	ft_draw_background(t_data *data);
void	ft_drawMapBck(t_data *data);
void	ft_draw_line(t_data *data, int x, int y, int a, int b, int col);
void	ft_drawFov(t_data *data);
void	ft_dumpRay(t_data *data, t_ray ray);
void	ft_drawTex(t_data *data, t_point p1, t_point p2, t_ray ray);
// common: hooks.c
int		ft_loop_hook(t_data *img);
int		ft_key_hook(int code, t_data *data);
int		ft_mouse_hook(int button, int x, int y, t_data *data);
int	ft_test_hook(int x, int y, t_data *data);
// common: load_map.c
void	ft_initMap(t_data *data, char *path);
// common: load_map_utils.c
void	ft_initialize_player(t_data *d, size_t x, size_t y, char dir);
void	ft_getPlayerPos(t_data *d, size_t *x, size_t *y);
// common: points.c
t_point	ft_getPlayerPoint(t_data *data);
float	ft_PointDist(t_point a, t_point b);
void	ft_getMapPoint(t_data *data, t_point p, size_t *x, size_t *y);
int	ft_isWall(t_data *data, size_t x, size_t y);
t_point	ft_valPoint(t_data *data, t_point p);
// common: map2d.c
void	ft_draw2dmap(t_data *data);
void	ft_MapZoom(t_data *data, int flag);
void	ft_movePlayer(t_data *data,int flag);
int	ft_checkMapNS(t_data *data, t_point p, float alpha);
int	ft_checkMapWE(t_data *data, t_point p, float alpha);
// common: math.c
float	ft_deg2rad(float deg);
float	ft_rad2deg(float rad);
float	ft_valAlpha(float alpha);
float	ft_getDist(float x1, float y1, float x2, float y2);
int	ft_getSide(int flag, float alpha);
// common: movePlayer.c
void	ft_rotatePlayer(t_data *data, int flag);
void	ft_leftright(t_data *data, float *newx, float *newy, int flag);
void	ft_forbac(t_data *data, float *newx, float *newy, int flag);
// common: load_map.c
void	ft_initMap(t_data *data, char *path);
// common: raycast.c
//void	ft_castRay(t_data *d, float alpha);
t_ray	ft_castRay(t_data *d, float alpha);
// common: draw3D.c
void	ft_draw3D(t_data *data, t_ray ray, int i);
// main
t_data	*ft_blank(t_data *data);
int		the_end(t_data *data);
void	ft_loadTextures(t_data *data, char **path);
void	ft_destroy_textures(t_data *data);
void	ft_texDefault(t_data *data);
int	ft_getTexPixel(t_data *data, int x, int y, int n);
void	ft_loadSprites(t_data *data);
void	ft_destroy_sprites(t_data *data);
void	ft_drawSpritePixel(t_data *data, int x, int y);
void	ft_checkHead(t_data *data, int fd);
void	ft_fileNf(t_data *data, char *path);

#endif
