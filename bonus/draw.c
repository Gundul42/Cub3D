/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:57:21 by graja             #+#    #+#             */
/*   Updated: 2022/01/28 18:39:06 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

int	ft_checkRayDir(t_data *data, t_ray *ray, float *x)
{
	float	dirmax;
	float	hfov;
	int	ok;

	ok = 0;
	hfov = (float)data->fov / 2.0;
	hfov +=  atanf((float)(data->tilesize) / ( ray->dist));
	dirmax = 360.0 - (float)data->fov * 1.5;
	*x = hfov;
	*x -= data->dir - ray->dir;
	//out of problem scope dirmax <= alpha <= 360
	if (data->dir <= dirmax && data->dir > (float)data->fov)
		ok = 1;
	if (ok && fabsf(data->dir - ray->dir) <= hfov * 1.5)
	{
//		printf(" OK\n");
		return (1);
	}
	// PROBLEM ZONE both angles between dirmax and 360
	if (!ok && data->dir >= dirmax && (data->dir - ray->dir <= dirmax))
	{
//		printf("Match 1\n");
		return (1);
	}
	// PROBLEM ZONE both angles between 0 and fov
	if (!ok && data->dir <= (float)data->fov && ray->dir <= (float)data->fov * 1.5)
	{
//		printf("Match 2\n");
		return (1);
	}
	// BIG PROBLEM ZONE maxdir <= dir <= 360 BUT 0 <= ray.dir <= fov
	if (!ok && data->dir >= dirmax && ray->dir >= 0.0 && ray->dir <= (float)data->fov * 1.5)
	{
		*x = hfov;
		*x += (360.0 - data->dir) + ray->dir; 
//		printf("Match 3\n");
		if (*x <= (float)data->fov * 1.5)
			return (1);
		return (0);
	}
	// BIG PROBLEM ZONE maxdir <= dir <= 360 BUT 0 <= ray.dir <= fov
	if (!ok && ray->dir >= dirmax && data->dir >= 0.0 && data->dir <= (float)data->fov * 1.5)
	{
		*x = hfov;
		*x -= (360.0 - ray->dir) + data->dir; 
//		printf("Match 4\n");
		return (1);
	}
//	printf("NoMatch\n");
	return (0);
}

float	ft_rayCorrect(t_data *data, t_ray ray)
{
	float	diff;

	if (data->correct)
		return (ray.dist);
	diff = (data->dir - ray.dir);
	return (ray.dist * cosf(ft_deg2rad(diff)));
}

void	ft_drawOneSprite(t_data *data, t_ray ray)
{
	float	height;
	float	faktor;
	float	wop;
	float	x;
	int	i;

	i = 0;
	//faktor = (float)(data->tilesize * 80) / (float)(data->win_x);
	faktor = (float)(data->win_x) * 0.5 / 64.0 * (float)(data->tilesize / 64);
	faktor *= data->tilesize / 64;
	height = faktor * (float)data->win_y / (float)data->tilesize;
	wop = (float)data->dtpp / ft_rayCorrect(data, ray) * height;
	if (!ft_checkRayDir(data, &ray, &x))
		return ;
//	printf("x = %5.2f, ray %5.2f   dir %5.2f\n", x, ray.dir, data->dir);
	x /= data->precision;
	x -= wop / 2;
//	printf("x = %5.2f wop = %5.2f\n\n", x, wop);
	while (i < wop - data->dopen)
	{
		ray.offset = (float)data->tilesize / wop * (float)i;
		if (data->zbuf[(int)x+i] > ray.dist)
			ft_draw3DSprite(data, ray, x + i + data->dopen);
		i++;
		ray.flag = 0;
	}
}

//draw one colom of the texture or only a part of it depending on distance
void	ft_drawSprite(t_data *data, t_point p1, t_point p2, t_ray ray)
{
	float	y;
	int	i;
	int	col;

	y = (float)(data->tilesize) / (p1.y - p2.y);
	i = 0;
	while ((int)p1.y > (int)p2.y)
	{
		col = ft_getSpritePixel(data, ray.offset, i * y);
		if (col)
			ft_draw_pixel(data, p1.x, p2.y + i, col);
		i++;
		p1.y -= 1.0;
	}
}

int	ft_getSpritePixel(t_data *data, int x, int y)
{
	char	*dst;
	int	bpp;
	int	ll;
	int	endian;

	if (x < 0 || x > (int)(data->tilesize) || y < 0 || 
			y > (int)(data->tilesize))
		return (0);
	dst = mlx_get_data_addr(data->sprite, &bpp,
			&ll, &endian);
	dst += (y * ll + x * (bpp / 8));
	return (*(unsigned int *)dst);
}

void	ft_draw3DSprite(t_data *data, t_ray ray, int i)
{
	float	wop;
	float	height;
	float	faktor;
	t_point	p1;
	t_point	p2;

	//faktor = (float)(data->tilesize * 80) / (float)(data->win_x);
	faktor = (float)(data->win_x) * 0.5 / 64.0 * (float)(data->tilesize / 64);
	faktor *= data->tilesize / 64;
	height = faktor * (float)data->win_y / (float)data->tilesize;
	wop = (float)data->dtpp / ft_rayCorrect(data, ray) * height;
	p1.y = (float)(data->win_y / 2) + wop / 2.0;
	p2.y = (float)(data->win_y / 2) - wop / 2.0;
	p1.x = i;
	p2.x = i;
	ft_drawSprite(data, p1, p2, ray);
}
