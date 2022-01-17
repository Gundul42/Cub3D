/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:19:13 by graja             #+#    #+#             */
/*   Updated: 2022/01/17 08:48:33 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

int	ft_checkMapNS(t_data *data, t_point p, float alpha)
{
	size_t	x;
	size_t	y;

	if (p.x >= data->mapx * data->tilesize || p.y >= data->mapy * data->tilesize)
		return (0);
	ft_getMapPoint(data, p, &x, &y);
	if (alpha > 270 || alpha < 90)
	{
		if (ft_isWall(data, x, y))
			return (0);
		else
			return (1);
	}
	else if (alpha < 270 && alpha > 90)
	{
		if (ft_isWall(data, x - 1, y))
			return (0);
		else
			return (1);
	}
	return (0);
}

int	ft_checkMapWE(t_data *data, t_point p, float alpha)
{
	size_t	x;
	size_t	y;

	if (p.x  >= data->mapx * data->tilesize || p.y >= data->mapy * data->tilesize)
		return (0);
	ft_getMapPoint(data, p, &x, &y);
	if (alpha > 180 && alpha < 360)
	{
		if (ft_isWall(data, x, y - 1))
			return (0);
		else
			return (1);
	}
	else if (alpha < 180 && alpha > 0)
	{
		if (ft_isWall(data, x, y))
			return (0);
		else
			return (1);
	}
	return (0);
}
