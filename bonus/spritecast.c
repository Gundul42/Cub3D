/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:44:48 by graja             #+#    #+#             */
/*   Updated: 2022/01/20 17:58:47 by graja            ###   ########.fr       */
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

static
t_point	ft_spriteCenter(t_data *data, t_point inp, float alpha, int flag)
{
	size_t	x;
	size_t	y;

	ft_getMapPoint(data, inp, &x, &y);
	if (!flag && alpha < 270.0 && alpha > 90.0)
		x--;
	if (flag && alpha >= 180.0 && alpha < 360.0)
		y--;
	inp.x = (float)((x * data->tilesize) + data->tilesize / 2); 
	inp.y = (float)((y * data->tilesize) + data->tilesize / 2);
	return (inp);
}

t_ray	*ft_spriteRay(t_data *d, float alpha, t_ray *ray)
{
	t_point	plyr;
	t_point	hor;
	t_point	vet;
	static int	lastx = 0;
	static int	lasty = 0;

	alpha = ft_valAlpha(alpha);
	plyr = ft_getPlayerPoint(d);
	hor = ft_firstHitHorizontal(d, alpha);
	vet = ft_firstHitVertical(d, alpha);
	vet = ft_findCollVertical(d, vet, alpha);
	hor = ft_findCollHorizontal(d, hor, alpha);
	if (hor.x < 0 && vet.x < 0)
		return (NULL);
	if (hor.x < 0)
		ray->p = ft_spriteCenter(d, vet, alpha, 0);
	else
		ray->p = ft_spriteCenter(d, hor, alpha, 1);
	if (ray->p.x == lastx && ray->p.y == lasty)
		return (NULL);
	ray->dir = ft_valAlpha(ft_rad2deg(atanf((ray->p.y - plyr.y) / (ray->p.x - plyr.x))));
	if (d->dir > 90.0 && d->dir < 270.0)
		ray->dir += 180.0;
	printf("%5.2f)   %5.2f  --  %f5.2\n", d->dir, alpha, ray->dir);
	lastx = ray->p.x;
	lasty = ray->p.y;
	ray->dist = ft_PointDist(plyr, ray->p);
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
		return (1);
	return (data->map[y][x]);
}