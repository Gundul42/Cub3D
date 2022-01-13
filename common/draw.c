/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 10:12:54 by graja             #+#    #+#             */
/*   Updated: 2022/01/13 14:48:02 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

/* calculates the different colors, the more far away the darker
 * and as nearer you get the brighter*/
static
int	interpol_color(t_data *data, int now, int max)
{
	t_hsv	res;

	res = ft_interpolate_hsv(rgb2hsv(data->cfloor_far),
			rgb2hsv(data->cfloor_near), now, max);
	return (ft_make_color(hsv2rgb(res)));
}

void	ft_drawMapPixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > (int)(data->win_x / data->minimap) || y < 0 || 
			y > (int)(data->win_x / data->minimap))
		return ;
	dst = data->addr1 + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_drawMapBck(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)(data->win_x / data->minimap))
	{
		x = 0;
		while (x < (int)(data->win_x / data->minimap))
		{
			ft_drawMapPixel(data, x, y, data->csky);
			x++;
		}
		y++;
	}
}

void	ft_drawDot(t_data *data, int i, int j)
{
	int	x;
	int	y;
	int	len;

	len = data->win_x / data->minimap / data->miniZ;
	y = j * len;
	while (y < (j + 1) * len)
	{
		x = i * len;
		while (x < (i + 1) * len)
		{
			ft_drawMapPixel(data, x, y, ft_make_trgb(128, 0, 0, 255));
			x++;
		}
		y++;
	}
}

void	ft_draw_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > (int)data->win_x || y < 0 || y > (int)data->win_y)
		return ;
	dst = data->addr + (y * data->line_length2 + x * (data->bits_per_pixel2 / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_background(t_data *data)
{
	size_t	x;
	size_t	y;

	data->addr = data->addr2;
	y = 0;
	while (y < data->win_y / 2)
	{
		x = 0;
		while (x < data->win_x)
		{
			ft_draw_pixel(data, x, y, data->csky);
			x++;
		}
		y++;
	}
	while (y < data->win_y)
	{
		x = 0;
		while (x < data->win_x)
		{
			ft_draw_pixel(data, x, y, interpol_color(data, y, data->win_y));
			x++;
		}
		y++;
	}
	data->addr = data->addr1;

}

void	ft_draw_line(t_data *data, int x, int y, int a, int b, int col)
{
	float	dist;
	int	i;
	float	xstep;
	float	ystep;

	if (col == -1)
		col = ft_make_trgb(0, 51, 0, 255);
	dist = sqrt(pow((a - x), 2) + pow((b - y), 2));
	xstep = (float)(a - x) / dist;
	ystep = (float)(b - y) / dist;
	i = 0;
	while (i <= dist)
	{
		ft_draw_pixel(data, x + xstep * i, y + ystep * i, col);
		i++;
	}
}

// dumps all info from a Ray, including drawing line in 2D from player 
// to collison point
void	ft_dumpRay(t_data *data, t_ray ray)
{
	t_point	plyr;
	char	*d[4] = {"North", "South", "East", "West"};

	plyr = ft_getPlayerPoint(data);
	printf("\n************************************\n");
	printf("*** Angle           : %f\n", ray.dir);
	printf("*** Distance to wall: %f\n", ray.dist);
	printf("*** Hit wall from   : %s\n", d[ray.flag]);
	printf("************************************\n");
	printf("*** Pposx           : %f\n", plyr.x);
	printf("*** Pposy           : %f\n", plyr.y);
	printf("************************************\n\n");
}

//draw field of view
void	ft_drawFov(t_data *data)
{
	float	start;
	int		max;
	int		i;
	t_ray	ray;

	max = (float)data->fov / data->precision;
	i = 0;
	start = data->dir - (float)(data->fov / 2);
	while (i < max)
	{
		ray = ft_castRay(data, start); 
		//ft_dumpRay(data, ray);
		ft_draw3D(data, ray, i);
		start += data->precision;
		i++;
	}
}
