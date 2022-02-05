/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 09:34:11 by graja             #+#    #+#             */
/*   Updated: 2022/02/04 12:24:51 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

//distance between two points
float	ft_point_dist(t_point a, t_point b)
{
	return (ft_get_dist(a.x, a.y, b.x, b.y));
}

//get player position as a point
t_point	ft_get_player_point(t_data *data)
{
	t_point	plyr;
	size_t	x;
	size_t	y;

	ft_get_player_pos(data, &x, &y);
	plyr.x = x;
	plyr.y = y;
	return (plyr);
}

//translates from pixel to point on the 2D map
void	ft_get_map_point(t_data *data, t_point p, size_t *x, size_t *y)
{
	*x = (size_t)(p.x) / (data->tilesize);
	*y = (size_t)(p.y) / (data->tilesize);
	if (*x > data->mapx - 1)
		*x = data->mapx - 1;
	if (*y > data->mapy - 1)
		*y = data->mapy - 1;
}

//check if coordinate is a wall, if exceeding map it is always true
int	ft_is_wall(t_data *data, size_t x, size_t y)
{
	if (x > data->mapx - 1 || y > data->mapy - 1)
		return (0);
	else
		return (data->map[y][x]);
	return (1);
}

//everything outside windowsize is forbidden !
t_point	ft_val_point(t_data *data, t_point p)
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
