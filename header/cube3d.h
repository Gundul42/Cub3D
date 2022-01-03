/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:43:25 by graja             #+#    #+#             */
/*   Updated: 2022/01/03 14:24:26 by graja            ###   ########.fr       */
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

// a color typedef for HSV colors
typedef struct s_hsv {
	double	h;
	double	s;
	double	v;
}		t_hsv;

// a color typedef for ARGB colors like in MiniLibX
typedef struct s_color {
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}			t_color;

// the basic data type for handling the minilibx
// x and y controlling window size
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
}				t_data;

int		ft_make_trgb(int t, int r, int g, int b);
int		ft_make_color(t_color src);
int		the_end(t_data *data);
t_color	ft_rgb2col(int t, int r, int g, int b);
void	ft_init_window(t_data *data, int x, int y, int i);
void	ft_draw_pixel(t_data *data, int x, int y, int color);
t_data	*ft_blank(t_data *data);

//HSV2RGB  vv and interpolation
t_color	hsv2rgb(t_hsv in);
t_hsv	ft_interpolate_hsv(t_hsv col1, t_hsv col2, int i, int maxi);
t_hsv	rgb2hsv(t_color in);


#endif
