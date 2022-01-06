/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 10:12:54 by graja             #+#    #+#             */
/*   Updated: 2022/01/07 00:08:28 by flormich         ###   ########.fr       */
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

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_background(t_data *data)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < data->win_y / 3)
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

void	ft_draw_line(t_data *data, int x, int y, int a, int b)
{
	float	dist;
	int	i;
	float	xstep;
	float	ystep;
	int	col;

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
	ft_draw_line(data, x, y, x2, y2);
}
