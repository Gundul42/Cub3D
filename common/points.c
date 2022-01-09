/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 09:34:11 by graja             #+#    #+#             */
/*   Updated: 2022/01/09 09:36:57 by graja            ###   ########.fr       */
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
