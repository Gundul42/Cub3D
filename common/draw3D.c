/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:05:12 by graja             #+#    #+#             */
/*   Updated: 2022/01/12 19:03:03 by graja            ###   ########.fr       */
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
	int	y1;
	int	y2;

	//printf("%3d %3.2f\n", data->dtpp, ray.dist);
	height = 4 * (float)data->win_y / (float)data->tilesize;
	height *= (float)(data->win_x / data->win_y);
	wop = (float)data->dtpp / ft_rayCorrect(data, ray) * height;
	data->addr = data->addr2;
	y1 = data->win_y / 2 + (int)wop / 2;
	y2 = data->win_y / 2 - (int)wop / 2;
	if (y1 > (int)(data->win_y))
		y1 = data->win_y - 1;
	if (y2 < 0)
		y2 = 0;
	ft_draw_line(data, i, y1, i, y2, data->wall[ray.flag]);
	data->addr = data->addr1;
}
