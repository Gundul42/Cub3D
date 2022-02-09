/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:57:21 by graja             #+#    #+#             */
/*   Updated: 2022/02/09 17:01:00 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

static
int	ft_arraycheck(t_data *data, int x, int i)
{
	if (x + i > 0 && x + i < (int)data->win_x)
		return (1);
	return (0);
}

static
int	ft_no_ok(t_data *data, t_ray *ray, float *x, float dirmax)
{
	if (data->dir >= dirmax && (data->dir - ray->dir <= dirmax))
		return (1);
	if (data->dir <= (float)data->fov && ray->dir
		<= (data->dir + (float)data->fov * 0.95))
		return (1);
	if (data->dir >= dirmax && ray->dir >= 0.0
		&& ray->dir <= (float)data->fov * 1.9)
	{
		*x = (float)data->fov / 2.0;
		*x += (360.0 - data->dir) + ray->dir;
		if (*x <= (float)data->fov * 1.9)
			return (1);
		return (0);
	}
	if (ray->dir >= dirmax && data->dir >= 0.0 && data->dir
		<= (float)data->fov * 1.9)
	{
		*x = (float)data->fov / 2.0;
		*x -= (360.0 - ray->dir) + data->dir;
		return (1);
	}
	return (0);
}

int	ft_check_ray_dir(t_data *data, t_ray *ray, float *x)
{
	float	dirmax;
	float	hfov;
	int		ok;

	ok = 0;
	hfov = (float)data->fov / 2.0;
	hfov += atanf((float)(data->tilesize) / (ray->dist));
	dirmax = 360.0 - (float)data->fov * 1.9;
	*x = hfov;
	*x -= data->dir - ray->dir;
	if (data->dir <= dirmax && data->dir > (float)data->fov)
		ok = 1;
	if (ok && fabsf(data->dir - ray->dir) <= hfov * 1.9)
		return (1);
	if (!ok && ft_no_ok(data, ray, x, dirmax))
		return (1);
	return (0);
}

static
void	ft_draw_now(t_data *data, t_ray ray, float x, float wop)
{
	int	i;
	int	sav;

	i = 0;
	sav = 0;
	if (ray.flag == 2 && data->doors[(size_t)ray.p.y / data->tilesize]
		[(size_t)ray.p.x / data->tilesize] > 0)
	{
		sav = data->dopen[(size_t)ray.p.y / data->tilesize]
		[(size_t)ray.p.x / data->tilesize];
		sav = (float)(sav * data->dtpp) / ray.dist;
	}
	while (i < wop - sav)
	{
		ray.offset = (float)data->tilesize / wop * (float)i;
		if (ft_arraycheck(data, x, i) && data->zbuf[(int)x + i] > ray.dist)
		{
			if (ray.flag != 2 || ray.dist > (float)data->tilesize / 2)
				ft_draw_3d_sprite(data, ray, x + i + sav);
		}
		i++;
	}
}

void	ft_draw_one_sprite(t_data *data, t_ray ray)
{
	float	faktor;
	float	wop;
	float	x;

	faktor = (float)(data->win_x) * 0.5 / 64.0 * (float)(data->tilesize / 64);
	faktor *= data->tilesize / 64;
	faktor *= (float)data->win_y / (float)data->tilesize;
	wop = (float)data->dtpp / ft_ray_correct(data, ray) * faktor;
	if (!ft_check_ray_dir(data, &ray, &x))
		return ;
	x /= data->precision;
	x -= wop / 2;
	ft_draw_now(data, ray, x, wop);
}
