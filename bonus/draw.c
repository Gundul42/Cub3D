/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:57:21 by graja             #+#    #+#             */
/*   Updated: 2022/01/19 17:53:55 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

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
	int	i;
	float	max;
	float	start;
	float	step;

	max = (float)data->fov / data->precision;
	i = 0;
	start = data->dir - (float)(data->fov / 2);
	step = ft_rad2deg(atanf((float)(data->tilesize / 2) / ray.dist));
	while (i < max)
	{

		ray.offset = i % 64;
		if (start > ray.dir - step && start < ray.dir + step)
			ft_draw3DSprite(data, ray, i);
		start += data->precision;
		i++;
	}
}

void	ft_drawSpriteFov(t_data *data)
{
	float	start;
	int		max;
	int		i;
	int		s;
	t_ray	ray_w;
	t_ray	ray_s[100];

	max = (float)data->fov / data->precision;
	i = 0;
	s = 0;
	start = data->dir - (float)(data->fov / 2);
	while (i < max)
	{
		ray_w = ft_castRay(data, start); 
		ft_draw3D(data, ray_w, i);
		if (ft_spriteRay(data, start, &ray_s[s]) && (ray_s[s].dist < ray_w.dist))
			s++;
		start += data->precision;
		i++;
	}
	s--;
	while (s > 0)
	{
		ft_drawOneSprite(data, ray_s[s]);
		s--;
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
	height *= (float)(data->win_x / data->win_y);
	wop = (float)data->dtpp / ft_rayCorrect(data, ray) * height;
	p1.y = (float)(data->win_y / 2) + wop / 2.0;
	p2.y = (float)(data->win_y / 2) - wop / 2.0;
	p1.x = i;
	p2.x = i;
	ft_drawSprite(data, p1, p2, ray);
}
