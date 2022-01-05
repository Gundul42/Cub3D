/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:19:13 by graja             #+#    #+#             */
/*   Updated: 2022/01/05 16:34:07 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_draw2dmap(t_data *data)
{
	size_t	xstep;
	size_t	ystep;
	size_t	x;
	size_t	y;
	int	col;

	col = ft_make_trgb(0, 255, 217, 102);
	xstep = data->win_x / data->mapx;
	ystep = data->win_y / data->mapy;
	y = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			if (data->map[y][x])
				ft_draw_rect(data, x * xstep, y * ystep, xstep, ystep, col);
			x++;
		}
		y++;
	}
	ft_showPlayer(data);
}

void	ft_showPlayer(t_data *data)
{
	size_t	xstep;
	size_t	ystep;
	size_t	x;
	size_t	y;
	int	col;

	col = ft_make_trgb(0, 237, 142, 83);
	xstep = data->win_x / data->mapx;
	ystep = data->win_y / data->mapy;
	x = data->px * xstep - xstep / 8;
	y = data->py * ystep - ystep / 8;
	ft_draw_rect(data, x, y, xstep / 4, ystep / 4, col);
}
