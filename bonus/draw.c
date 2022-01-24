/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:57:21 by graja             #+#    #+#             */
/*   Updated: 2022/01/23 19:14:48 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

int	ft_checkRayDir(t_data *data, t_ray ray, float *x)
{
	float	dirmax;
	int	ok;

	ok = 0;
	dirmax = 360.0 - (float)data->fov / 2.0;
	*x = (float)data->fov / 2;
	*x -= data->dir - ray.dir; 
	if (dirmax - data->dir > 0 && data->dir > (float)data->fov / 2)
		ok = 1;
	if (ok && fabsf(data->dir - ray.dir) <= (float)(data->fov / 2.0))
		return (1);
	else if (!ok && data->dir >= dirmax && fabsf(data->dir - ray.dir) <= (float)(data->fov / 2.0))
		return (1);
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
	faktor = (float)(data->tilesize * 80) / (float)(data->win_x);
	height = faktor * (float)data->win_y / (float)data->tilesize;
	wop = (float)data->dtpp / ft_rayCorrect(data, ray) * height;
	if (!ft_checkRayDir(data, ray, &x))
		return ;
	//printf("ray %5.2f   dir %5.2f\n", ray.dir, data->dir);
	x /= data->precision;
	x -= wop / 2;
	//printf("x = %5.2f wop = %5.2f\n\n", x, wop);
	while (i < wop)
	{
		ray.offset = (float)data->tilesize / wop * (float)i;
		if (data->zbuf[(int)x+i] > ray.dist)
			ft_draw3DSprite(data, ray, x + i);
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

	faktor = (float)(data->tilesize * 80) / (float)(data->win_x);
	height = faktor * (float)data->win_y / (float)data->tilesize;
	wop = (float)data->dtpp / ft_rayCorrect(data, ray) * height;
	p1.y = (float)(data->win_y / 2) + wop / 2.0;
	p2.y = (float)(data->win_y / 2) - wop / 2.0;
	p1.x = i;
	p2.x = i;
	ft_drawSprite(data, p1, p2, ray);
}
