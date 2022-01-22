/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:12:57 by graja             #+#    #+#             */
/*   Updated: 2022/01/22 13:14:23 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

static
t_point	ft_firstHitHorizontal(t_data *d, float alpha)
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
t_point	ft_firstHitVertical(t_data *d, float alpha)
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
t_point	ft_findCollVertical(t_data *data, t_point v, float alpha)
{
	float	deltaY;
	int		val;

	deltaY = ((float)(data->tilesize)) * tanf(ft_deg2rad(alpha));
	val = ft_checkMapNS(data, v, alpha);
	while (val)
	{
		ft_insertSprite(data, v, val);
		if (alpha >= 270 || alpha <= 90)
		{
			v.x += (float)(data->tilesize);
			v.y += deltaY;
		}
		else	
		{
			v.x -= (float)(data->tilesize);
			v.y -= deltaY;
		}
		val = ft_checkMapNS(data, v, alpha);
	}
	return (v);
}

static
t_point	ft_findCollHorizontal(t_data *data, t_point h, float alpha)
{
	float	deltaX;
	int		val;

	deltaX = ((float)(data->tilesize)) / tanf(ft_deg2rad(alpha));
	val = ft_checkMapWE(data, h, alpha);
	while (val)
	{
		ft_insertSprite(data, h, val);
		if (alpha >= 180 && alpha <= 360)
		{
			h.x -= deltaX;
			h.y -= (float)(data->tilesize);
		}
		else
		{
			h.x += deltaX;
			h.y += (float)(data->tilesize);
		}
		val = ft_checkMapWE(data, h, alpha);
	}
	return (h);
}

t_ray	ft_SpriteRay(t_data *d, float alpha)
{
	t_point	plyr;
	t_point	hor;
	t_point	vet;
	t_ray	ray;

	alpha = ft_valAlpha(alpha);
	plyr = ft_getPlayerPoint(d);
	hor = ft_firstHitHorizontal(d, alpha);
	vet = ft_firstHitVertical(d, alpha);
	vet = ft_findCollVertical(d, vet, alpha);
	hor = ft_findCollHorizontal(d, hor, alpha);
	ray.dir = alpha;
	if (ft_PointDist(plyr, vet) < ft_PointDist(plyr, hor))
	{
		ray.p = vet;
		ray.dist = ft_PointDist(plyr, vet);
		ray.offset = (int)(ray.p.y) % d->tilesize;
		ray.flag = ft_getSide(0, alpha);
	}
	else
	{
		ray.p = hor;
		ray.dist = ft_PointDist(plyr, hor);
		ray.offset = (int)(ray.p.x) % d->tilesize;
		ray.flag = ft_getSide(1, alpha);
	}
	return (ray);
}
