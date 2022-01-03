/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 09:38:51 by graja             #+#    #+#             */
/*   Updated: 2021/09/17 13:15:07 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_hsv {
	double	h;
	double	s;
	double	v;
}		t_hsv;

typedef struct s_numbr {
	double	real;
	double	img;
}			t_numbr;

typedef struct s_color {
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}			t_color;

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		type;
	int		x;
	int		y;
	int		i;
	double	minreal;
	double	maxreal;
	double	minimg;
	double	maximg;
	double	juliareal;
	double	juliaimg;
	double	zoom;
	double	movex;
	double	movey;
	t_color	*breakpts;
	int		*palette;
}				t_data;

int		ft_make_trgb(int t, int r, int g, int b);
void	ft_draw_pixel(t_data *data, int x, int y, int color);
int		mandelbrot(t_data *data);
int		ship(t_data *data);
int		julia(t_data *data);
double	ft_getreal(int x, t_data *f);
double	ft_getimg(int y, t_data *f);
int		ft_calc_color(t_numbr new, int i, t_data *f);
void	ft_zoom(t_data *data, double faktor);
void	ft_mmove(t_data *data, int mousex, int mousey, double faktor);
void	ft_draw_fractal(t_data *data);
int		ft_smooth_color(t_numbr new, int i, t_data *data);
int		ft_make_color(t_color src);
int		*ft_init_palette(t_data *data);
t_color	*ft_init_colors(void);
t_color	ft_rgb2col(int t, int r, int g, int b);
t_hsv	rgb2hsv(t_color in);
t_color	hsv2rgb(t_hsv in);
t_hsv	ft_interpolate_hsv(t_hsv col1, t_hsv col2, int i, int maxi);
int		ft_mouse_hook(int button, int x, int y, t_data *data);
int		ft_key_hook(int code, t_data *data);
int		ft_loop_hook(t_data *img);
int		the_end(t_data *data);
void	ft_reset_mandelbrot(t_data *data);
void	ft_goto_julia(t_data *data, int x, int y);
void	ft_init_window(t_data *data, int x, int y, int i);
int		ft_cmd_fractal(char *str);
int		ft_cmd_resolution(t_data *data, char *str);
int		ft_cmd_julia(t_data *data, char *str);
t_data	*ft_blank(t_data *data);
void	ft_init_ship(t_data *data);
void	ft_init_julia(t_data *data);
void	ft_init_mandel(t_data *data);

#endif
