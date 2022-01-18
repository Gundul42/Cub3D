/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:44:48 by graja             #+#    #+#             */
/*   Updated: 2022/01/18 16:53:24 by graja            ###   ########.fr       */
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

	deltaY = ((float)(data->tilesize)) * tanf(ft_deg2rad(alpha));
	while (!ft_checkSpriteNS(data, v, alpha))
	{
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
	}
	if (ft_checkSpriteNS(data, v, alpha) < 2)
		v.x = -666.6;
	return (v);
}

static
t_point	ft_findCollHorizontal(t_data *data, t_point h, float alpha)
{
	float	deltaX;
	int	t;

	t = 0;
	deltaX = ((float)(data->tilesize)) / tanf(ft_deg2rad(alpha));
	while (!ft_checkSpriteWE(data, h, alpha))
	{
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
		t++;
	}
	if (ft_checkSpriteWE(data, h, alpha) < 2)
		h.x = -666.6;
	return (h);
}

t_ray	*ft_spriteRay(t_data *d, float alpha, t_ray *ray)
{
	t_point	plyr;
	t_point	hor;
	t_point	vet;

	alpha = ft_valAlpha(alpha);
	plyr = ft_getPlayerPoint(d);
	hor = ft_firstHitHorizontal(d, alpha);
	vet = ft_firstHitVertical(d, alpha);
	vet = ft_findCollVertical(d, vet, alpha);
	hor = ft_findCollHorizontal(d, hor, alpha);
	ray->dir = alpha;
	if (hor.x < 0 || vet.x < 0)
		return (NULL);
	if (ft_PointDist(plyr, vet) < ft_PointDist(plyr, hor))
	{
		ray->p = vet;
		ray->dist = ft_PointDist(plyr, vet);
		ray->offset = (int)(ray->p.y) % d->tilesize;
		ray->flag = ft_getSide(0, alpha);
	}
	else
	{
		ray->p = hor;
		ray->dist = ft_PointDist(plyr, hor);
		ray->offset = (int)(ray->p.x) % d->tilesize;
		ray->flag = ft_getSide(1, alpha);
	}
	return (ray);
}

int	ft_checkSpriteNS(t_data *data, t_point p, float alpha)
{
	size_t	x;
	size_t	y;

	if (p.x >= data->mapx * data->tilesize || p.y >= data->mapy * data->tilesize)
		return (-1);
	ft_getMapPoint(data, p, &x, &y);
	if (alpha >= 270 || alpha < 90)
	{
		if (ft_isSprite(data, x, y))
			return (ft_isSprite(data, x, y));
		else
			return (0);
	}
	else if (alpha < 270 && alpha >= 90)
	{
		if (ft_isSprite(data, x - 1, y))
			return (ft_isSprite(data, x - 1, y));
		else
			return (0);
	}
	return (-1);
}

int	ft_checkSpriteWE(t_data *data, t_point p, float alpha)
{
	size_t	x;
	size_t	y;

	if (p.x  >= data->mapx * data->tilesize || p.y >= data->mapy * data->tilesize)
		return (-1);
	ft_getMapPoint(data, p, &x, &y);
	if (alpha >= 180 && alpha < 360)
	{
		if (ft_isSprite(data, x, y - 1))
			return (ft_isSprite(data, x, y - 1));
		else
			return (0);
	}
	else if (alpha < 180 && alpha >= 0)
	{
		if (ft_isSprite(data, x, y))
			return (ft_isSprite(data, x, y));
		else
			return (0);
	}
	return (-1);
}

//check if coordinate is a wall, if exceeding map it is always true
int	ft_isSprite(t_data *data, size_t x, size_t y)
{
	if (x >= data->mapx - 1 || y >= data->mapy - 1)
		return (-1);
	else if (data->map[y][x] > 0)
		return (data->map[y][x]);
	return (0);
}
