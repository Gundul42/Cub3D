/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:05:12 by graja             #+#    #+#             */
/*   Updated: 2022/01/14 20:21:25 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"


static
float	ft_rayCorrect(t_data *data, t_ray ray)
{
	float	diff;

	if (!data->correct)
		return (ray.dist);
	diff = (data->dir - ray.dir);
	return (ray.dist * cosf(ft_deg2rad(diff)));
}

void	ft_draw3D(t_data *data, t_ray ray, int i)
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
	ft_drawTex(data, p1, p2, ray);
}
