/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:44:48 by graja             #+#    #+#             */
/*   Updated: 2022/01/22 15:15:17 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

static
t_ray	ft_sprite2ray(t_sprite s)
{
	t_ray	ray;

	ray.p = s.p;
	ray.dir = s.dir;
	ray.dist = s.dist;
	ray.offset = 0;
	ray.flag = 0;
	return (ray);
}

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
	
void	ft_showSprites(t_data *data)
{
	int	i;
	t_ray	ray;

	i = 0;
	while ((data->slist[i]).init)
	{
		ray = ft_sprite2ray(data->slist[i]);
		ft_drawOneSprite(data, ray);
		i++;
	}
	printf("%d\n", i);
}

/*
t_ray	*ft_spriteRay(t_data *d, float alpha, t_ray *ray)
{
	t_point	plyr;
	t_point	hor;
	t_point	vet;
	static float	lastx = 0.0;
	static float	lasty = 0.0;

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
	printf("x%5.2f   y%5.2f\n", ray->p.x, ray->p.y);
	lastx = ray->p.x;
	lasty = ray->p.y;
	ray->dist = ft_PointDist(plyr, ray->p);
	return (ray);
}*/
