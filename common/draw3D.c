/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:05:12 by graja             #+#    #+#             */
/*   Updated: 2022/01/24 14:28:18 by graja            ###   ########.fr       */
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
	wop = (float)data->dtpp / ft_rayCorrect(data, ray) * height;
	if (wop > 8500.0)
		wop = 8500.0;
	p1.y = (float)(data->win_y / 2) + wop / 2.0;
	p2.y = (float)(data->win_y / 2) - wop / 2.0;
//	printf("%5.4f) p1.y %5.2f - p2.y %5.2f     == %5.2f\n", wop, p1.y, p2.y, p1.y - p2.y);
	p1.x = i;
	p2.x = i;
	ft_drawTex(data, p1, p2, ray);
}

