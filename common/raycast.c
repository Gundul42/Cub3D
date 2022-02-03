/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:15:47 by graja             #+#    #+#             */
/*   Updated: 2022/02/02 22:06:37 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
t_point	ft_first_hit_horizontal(t_data *d, float alpha)
{
	t_point	diff;

	if (alpha > 180.0 && alpha < 360.0)
		diff.y = d->py - floorf(d->py);
	else
		diff.y = d->py - ceilf(d->py);
	diff.x = diff.y / tanf(ft_deg2rad(alpha));
	diff.x = (d->px - diff.x) * (float)(d->tilesize);
	diff.y = (d->py - diff.y) * (float)(d->tilesize);
	return (diff);
}

static
t_point	ft_first_hit_vertical(t_data *d, float alpha)
{
	t_point	diff;

	if (alpha >= 270.0 || alpha <= 90.0)
		diff.x = ceilf(d->px) - d->px;
	else
		diff.x = floorf(d->px) - d->px;
	diff.y = diff.x * tanf(ft_deg2rad(alpha));
	diff.x = (d->px + diff.x) * (float)(d->tilesize);
	diff.y = (d->py + diff.y) * (float)(d->tilesize);
	return (diff);
}

static
t_point	ft_find_col_vertical(t_data *data, t_point v, float alpha)
{
	float	delta_y;

	delta_y = ((float)(data->tilesize)) * tanf(ft_deg2rad(alpha));
	while (ft_check_map_ns(data, v, alpha))
	{
		if (alpha >= 270 || alpha <= 90)
		{
			v.x += (float)(data->tilesize);
			v.y += delta_y;
		}
		else
		{
			v.x -= (float)(data->tilesize);
			v.y -= delta_y;
		}
	}
	return (v);
}

static
t_point	ft_find_col_horizontal(t_data *data, t_point h, float alpha)
{
	float	delta_x;

	delta_x = ((float)(data->tilesize)) / tanf(ft_deg2rad(alpha));
	while (ft_check_map_we(data, h, alpha))
	{
		if (alpha >= 180 && alpha <= 360)
		{
			h.x -= delta_x;
			h.y -= (float)(data->tilesize);
		}
		else
		{
			h.x += delta_x;
			h.y += (float)(data->tilesize);
		}
	}
	return (h);
}

t_ray	ft_cast_ray(t_data *d, float alpha)
{
	t_point	plyr;
	t_point	hor;
	t_point	vet;
	t_ray	ray;

	alpha = ft_val_alpha(alpha);
	plyr = ft_get_player_point(d);
	hor = ft_first_hit_horizontal(d, alpha);
	vet = ft_first_hit_vertical(d, alpha);
	vet = ft_find_col_vertical(d, vet, alpha);
	hor = ft_find_col_horizontal(d, hor, alpha);
	ray.dir = alpha;
	if (ft_point_dist(plyr, vet) < ft_point_dist(plyr, hor))
	{
		ray.p = vet;
		ray.dist = ft_point_dist(plyr, vet);
		ray.offset = (int)(ray.p.y) % d->tilesize;
		ray.flag = ft_get_side(0, alpha);
		return (ray);
	}
	ray.p = hor;
	ray.dist = ft_point_dist(plyr, hor);
	ray.offset = (int)(ray.p.x) % d->tilesize;
	ray.flag = ft_get_side(1, alpha);
	return (ray);
}
