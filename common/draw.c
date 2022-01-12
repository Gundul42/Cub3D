/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 10:12:54 by graja             #+#    #+#             */
/*   Updated: 2022/01/12 17:58:06 by graja            ###   ########.fr       */
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

void	ft_draw_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > (int)data->win_x || y < 0 || y > (int)data->win_y)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// simple one color only background
void	ft_drawBackSimple(t_data *data)
{
	size_t	x;
	size_t	y;

	y = 0;
	data->addr = data->addr1;
	while (y < data->win_y)
	{
		x = 0;
		while (x < data->win_x)
		{
			ft_draw_pixel(data, x, y, 0);
			x++;
		}
		y++;
	}
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

void	ft_draw_rect(t_data *data, int x, int y, int l, int w, int col)
{
	int	a;
	int	b;

	b = 0;
	while (b < w)
	{
		a = 0;
		while (a < l)
		{
			ft_draw_pixel(data, x + a, y + b, col);
			a++;
		}
		b++;
	}
}

void	ft_draw_circle(t_data *d, int or_x, int or_y, float r, int col)
{
	int	x;
	int	y;
	
	if (or_x < 0 || or_x > (int)d->win_x || or_y < 0 || or_y > (int)d->win_y)
		return ;
	x = or_x - r;
	while (x <= or_x + r)
	{
		y = or_y - r;
		while (y <= or_y + r)
		{
			if (pow(pow(x - or_x, 2) + pow(y - or_y, 2), 0.5) <= r)
			{
				ft_draw_pixel(d, x, y, col);
			}
			y++;
		}
		x++;
	}
}

// draws an empty circle
void	ft_draw_hit(t_data *data, float x, float y, float r, int col)
{
	int	alpha;
	int	newx;
	int	newy;

	alpha = 0;
	while (alpha < 360)
	{
		newx = (x + r * cosf(ft_deg2rad((alpha))));
		newy = (y + r * sinf(ft_deg2rad((alpha)))); 
		ft_draw_pixel(data, newx, newy, col);  
		alpha++;
	}
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

/* newly added (06/01/22) draw a line beginning from x,y with the length
 * of len in direction of alpha */
void	ft_draw_angeled(t_data *data, int x, int y, float alpha, int len)
{
	int	x2;
	int	y2;

	x2 = x + (float)(len) * cosf(ft_deg2rad(alpha));
	y2 = y + (float)(len) * sinf(ft_deg2rad(alpha));
	ft_draw_line(data, x, y, x2, y2, -1);
}

//draw only one mapblocktile
void	ft_drawBox(t_data *data, size_t x, size_t y)
{
	size_t	xstep;
	size_t	ystep;

	xstep = data->win_x / data->mapx;
	ystep = data->win_y / data->mapy;
	ft_draw_rect(data, (x * xstep), (y * ystep), xstep - 1, ystep - 1, 0);
}

// dumps all info from a Ray, including drawing line in 2D from player 
// to collison point
void	ft_dumpRay(t_data *data, t_ray ray)
{
	t_point	plyr;
	char	*d[4] = {"North", "South", "East", "West"};

	plyr = ft_getPlayerPoint(data);
	ft_draw_line(data, plyr.x, plyr.y, ray.p.x, ray.p.y, -1);
	printf("\n************************************\n");
	printf("*** Angle           : %f\n", ray.dir);
	printf("*** Distance to wall: %f\n", ray.dist);
	printf("*** Hit wall from   : %s\n", d[ray.flag]);
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
