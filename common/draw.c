/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 10:12:54 by graja             #+#    #+#             */
/*   Updated: 2022/02/02 21:45:29 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_draw_pixel(t_data *d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > (int)d->win_x || y < 0 || y > (int)d->win_y)
		return ;
	dst = d->addr2 + (y * d->line_length2 + x * (d->bits_per_pixel2 / 8));
	*(unsigned int *)dst = color;
}

//draw field of view
void	ft_draw_fov(t_data *data)
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
		ray = ft_cast_ray(data, start);
		ft_draw_3d(data, ray, i);
		start += data->precision;
		i++;
	}
}

/* calculates the different colors, the more far away the darker
 * and as nearer you get the brighter*/
static
int	interpol_color(t_data *data, int now, int max)
{
	t_hsv	res;

	res = ft_interpolate_hsv(rgb2hsv(data->cfloor_near),
			rgb2hsv(data->cfloor_far), now, max);
	return (ft_make_color(hsv2rgb(res)));
}

void	ft_draw_background(t_data *d)
{
	size_t	x;
	size_t	y;
	int		col;

	d->addr = d->addr2;
	y = 0;
	while (y < d->win_y)
	{
		x = 0;
		while (x < d->win_x)
		{
			if (y < d->win_y / 2)
				col = d->csky;
			else
				col = interpol_color(d, y - (d->win_y / 2), (d->win_y) / 2);
			ft_draw_pixel(d, x, y, col);
			x++;
		}
		y++;
	}
	d->addr = d->addr1;
}

//draw one colom of the texture or only a part of it depending on distance
void	ft_draw_tex(t_data *data, t_point p1, t_point p2, t_ray ray)
{
	float	y;
	int		i;

	y = (float)(data->tilesize) / (p1.y - p2.y);
	i = 0;
	while ((int)p1.y > (int)p2.y)
	{
		ft_draw_pixel(data, p1.x, p2.y + i,
			ft_get_tex_pixel(data, ray.offset, i * y, ray.flag));
		i++;
		p1.y -= 1.0;
	}
}
