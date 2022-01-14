/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 09:34:11 by graja             #+#    #+#             */
/*   Updated: 2022/01/14 15:33:42 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

//distance between two points
float	ft_PointDist(t_point a, t_point b)
{
	return (ft_getDist(a.x, a.y, b.x, b.y));
}

//get player position as a point
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

//translates from pixel to point on the 2D map
void	ft_getMapPoint(t_data *data, t_point p, size_t *x, size_t *y)
{
	*x = (size_t)(p.x) / (data->tilesize);
	*y = (size_t)(p.y) / (data->tilesize);
	if (*x > data->mapx - 1)
		*x = data->mapx - 1;
	if (*y > data->mapy - 1)
		*y = data->mapy - 1;
}

//check if coordinate is a wall, if exceeding map it is always true
int	ft_isWall(t_data *data, size_t x, size_t y)
{
	if (x >= data->mapx - 1 || y >= data->mapy - 1)
		return (1);
	else
		return (data->map[y][x]);
	return (1);
}

//everything outside windowsize is forbidden !
t_point	ft_valPoint(t_data *data, t_point p)
{
	if (p.y < 0)
		p.y = 0;
	if (p.y > (data->win_y))
		p.y = (data->win_y - 1);
	if (p.x < 0)
		p.x = 0;
	if (p.x > (data->win_x))
		p.x = (data->win_x - 1);
	return (p);
}

