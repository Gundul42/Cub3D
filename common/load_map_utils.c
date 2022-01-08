/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:22:15 by flormich          #+#    #+#             */
/*   Updated: 2022/01/08 13:46:13 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_initialize_player(t_data *d, size_t x, size_t y, char dir)
{
	d->px = x;
	d->py = y;
	if (dir == 'W')
		d->dir = 270.0;
	else if (dir == 'E')
		d->dir = 90.0;
	else if (dir == 'N')
		d->dir = 0.0;
	else if (dir == 'S')
		d->dir = 180.0;
}

void	ft_getPlayerPos(t_data *d, size_t *x, size_t *y)
{
	size_t	xstep;
	size_t	ystep;

	xstep = d->win_x / d->mapx;
	ystep = d->win_y / d->mapy;
	*x = d->px * xstep;
	*y = d->py * ystep;
}

t_point	ft_getPlayerPoint(t_data *data)
{
	t_point	plyr;
	size_t	x;
	size_t	y;

	ft_getPlayerPos(data, &x, &y);
	plyr.x = x;
	plyr.y = y;
	return (plyr);
}
