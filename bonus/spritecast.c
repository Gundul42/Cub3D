/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:44:48 by graja             #+#    #+#             */
/*   Updated: 2022/02/03 15:18:33 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

/* allowed sprites start with number 2 and go until 9, to get the
 * right array index ray.sprite must be code - 2.
 */
static
t_ray	ft_sprite2ray(t_sprite s)
{
	t_ray	ray;

	ray.p = s.p;
	ray.dir = s.dir;
	ray.dist = s.dist;
	ray.flag = s.code - 2;
	ray.offset = 0;
	return (ray);
}

t_point	ft_sprite_center(t_data *data, t_point inp, float alpha, int flag)
{
	size_t	x;
	size_t	y;

	ft_get_map_point(data, inp, &x, &y);
	if (!flag && alpha < 270.0 && alpha > 90.0)
		x--;
	if (flag && alpha >= 180.0 && alpha < 360.0)
		y--;
	inp.x = (float)((x * data->tilesize) + data->tilesize / 2);
	inp.y = (float)((y * data->tilesize) + data->tilesize / 2);
	return (inp);
}

void	ft_show_sprites(t_data *data)
{
	int		i;
	t_ray	ray;

	i = 0;
	while (i < data->snbr)
	{
		ray = ft_sprite2ray(data->slist[i]);
		ft_draw_one_sprite(data, ray);
		i++;
	}
}

//draw one colom of the texture or only a part of it depending on distance
void	ft_draw_sprite(t_data *data, t_point p1, t_point p2, t_ray ray)
{
	float	y;
	int		i;
	int		col;

	y = (float)(data->tilesize) / (p1.y - p2.y);
	i = 0;
	while ((int)p1.y > (int)p2.y)
	{
		col = ft_get_sprite_pixel(data, ray.offset, i * y, ray.flag);
		if (col)
			ft_draw_pixel(data, p1.x, p2.y + i, col);
		i++;
		p1.y -= 1.0;
	}
}

void	ft_draw_3d_sprite(t_data *data, t_ray ray, int i)
{
	float	wop;
	float	height;
	float	faktor;
	t_point	p1;
	t_point	p2;

	faktor = (float)(data->win_x) * 0.5 / 64.0 * (float)(data->tilesize / 64);
	faktor *= data->tilesize / 64;
	height = faktor * (float)data->win_y / (float)data->tilesize;
	wop = (float)data->dtpp / ft_ray_correct(data, ray) * height;
	p1.y = (float)(data->win_y / 2) + wop / 2.0;
	p2.y = (float)(data->win_y / 2) - wop / 2.0;
	p1.x = i;
	p2.x = i;
	ft_draw_sprite(data, p1, p2, ray);
}
