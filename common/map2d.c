/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:19:13 by graja             #+#    #+#             */
/*   Updated: 2022/01/05 17:51:26 by graja            ###   ########.fr       */
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

/* Flags:
 * 		1 = up
 * 		2 = down
 * 		3 = right
 * 		4 = left
*/
void	ft_movePlayer(t_data *data,int flag)
{
	float	newx;
	float	newy;

	newx = data->px;
	newy = data->py;	
	if (flag == 1)
		newy -= 0.25;
	if (flag == 2)
		newy += 0.25;
	if (flag == 3)
		newx -= 0.25;
	if (flag == 4)
		newx += 0.25;
	if (!data->map[(size_t)(newy - 0.25)][(size_t)(newx)])
	{
		data->px = newx;
		data->py = newy;
	}
	ft_showPlayer(data);
}
