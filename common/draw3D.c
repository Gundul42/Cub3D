/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:05:12 by graja             #+#    #+#             */
/*   Updated: 2022/02/02 19:37:45 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
float	ft_ray_correct(t_data *data, t_ray ray)
{
	float	diff;

	if (!data->correct)
		return (ray.dist);
	diff = (data->dir - ray.dir);
	return (ray.dist * cosf(ft_deg2rad(diff)));
}

void	ft_draw_3d(t_data *data, t_ray ray, int i)
{
	float	wop;
	float	height;
	float	faktor;
	t_point	p1;
	t_point	p2;

	faktor = (float)(data->win_x) * 0.5 / 64.0 * (float)(data->tilesize / 64);
	faktor *= data->tilesize / 64;
	height = faktor * (float)data->win_y / (float)data->tilesize;
	wop = (float)data->dtpp / ft_ray_correct(data, ray) * height;
	if (wop > 2500.0)
		wop = 2500.0;
	p1.y = (float)(data->win_y / 2) + wop / 2.0;
	p2.y = (float)(data->win_y / 2) - wop / 2.0;
	p1.x = i;
	p2.x = i;
	ft_draw_tex(data, p1, p2, ray);
}
