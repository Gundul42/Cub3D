/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:57:21 by graja             #+#    #+#             */
/*   Updated: 2022/02/03 15:12:00 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

static
float	ft_get_faktor(t_data *data, t_ray ray, int *i, int *sav)
{
	float	faktor;

	*i = 0;
	*sav = 0;
	faktor = (float)(data->win_x) * 0.5 / 64.0 * (float)(data->tilesize / 64);
	faktor *= data->tilesize / 64;
	faktor *= (float)data->win_y / (float)data->tilesize;
	faktor = (float)data->dtpp / ft_ray_correct(data, ray) * faktor;
	return (faktor);
}

static
int	ft_check_deeper(t_data *data, t_ray *ray, float dirmax)
{
	if (data->dir >= dirmax && (data->dir - ray->dir <= dirmax))
		return (1);
	if (data->dir <= (float)data->fov && ray->dir <= (float)
		data->fov * 1.5)
		return (1);
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
	dirmax = 360.0 - (float)data->fov * 1.5;
	*x = hfov - data->dir - ray->dir;
	if (data->dir <= dirmax && data->dir > (float)data->fov)
		ok = 1;
	if (ok && fabsf(data->dir - ray->dir) <= hfov * 1.5)
		return (1);
	if (!ok && ft_check_deeper(data, ray, dirmax))
		return (1);
	if (!ok && data->dir >= dirmax && ray->dir >= 0.0
		&& ray->dir <= (float)data->fov * 1.5)
	{
		*x = hfov;
		*x += (360.0 - data->dir) + ray->dir;
		if (*x <= (float)data->fov * 1.5)
			return (1);
		return (0);
	}
	return (0);
}

void	ft_draw_one_sprite(t_data *data, t_ray ray)
{
	float	wop;
	float	x;
	int		i;
	int		sav;

	wop = ft_get_faktor(data, ray, &i, &sav);
	if (!ft_check_ray_dir(data, &ray, &x))
		return ;
	x /= data->precision;
	x -= wop / 2;
	if (ray.flag == 2 && data->doors[(size_t)ray.p.y / data->tilesize]
		[(size_t)ray.p.x / data->tilesize] > 0)
		sav = data->dopen[(size_t)ray.p.y / data->tilesize]
		[(size_t)ray.p.x / data->tilesize];
	while (i < wop - sav)
	{
		ray.offset = (float)data->tilesize / wop * (float)i;
		if (data->zbuf[(int)x + i] > ray.dist)
		{
			if (ray.flag != 2 || ray.dist > (float)data->tilesize / 2)
				ft_draw_3d_sprite(data, ray, x + i + sav);
		}
		i++;
	}
}

int	ft_get_sprite_pixel(t_data *data, int x, int y, int i)
{
	char	*dst;
	int		bpp;
	int		ll;
	int		endian;

	if (x < 0 || x > (int)(data->tilesize) || y < 0 ||
			y > (int)(data->tilesize))
		return (0);
	dst = mlx_get_data_addr(data->sprite[i], &bpp,
			&ll, &endian);
	dst += (y * ll + x * (bpp / 8));
	return (*(unsigned int *)dst);
}
