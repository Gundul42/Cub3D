/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 10:12:54 by graja             #+#    #+#             */
/*   Updated: 2022/01/05 12:34:23 by graja            ###   ########.fr       */
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
	int	x;
	int	y;

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
