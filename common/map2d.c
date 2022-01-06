/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:19:13 by graja             #+#    #+#             */
/*   Updated: 2022/01/05 15:45:30 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_draw2dmap(t_data *data)
{
	size_t	xstep;
	size_t	ystep;
	size_t	x;
	size_t	y;

	xstep = data->win_x / data->mapx;
	ystep = data->win_y / data->mapy;
	y = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			if (data->map[y][x])
				ft_draw_rect(data, x * xstep, y * ystep, xstep, ystep);
			x++;
		}
		y++;
	}
}
