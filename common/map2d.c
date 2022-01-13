/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:19:13 by graja             #+#    #+#             */
/*   Updated: 2022/01/13 13:19:47 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
void	ft_mapDot(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;
	
	j = 0;
	while (j < (int)data->miniZ)
	{
		i = 0;
		while (i < (int)data->miniZ)
		{
			if (ft_isWall(data, x - (int)data->miniZ / 2 + i, 
						y - (int)data->miniZ / 2 + j))
				printf("*");
			else
				printf(" ");
			i++;
		}
		printf("\n");
		j++;
	}
	printf("\n\n");
	color++;
}

//	ft_drawMapPixel(t_data *data, int x, int y, int color)
void	ft_draw2dmap(t_data *data)
{
	
	printf("\n*******************************\n");
	printf("**** Px = %5.2f\n", data->px);
	printf("**** Py = %5.2f\n", data->py);
	printf("*******************************\n");
	ft_mapDot(data, data->px, data->py, 0);
}

/* Flags:
 * 		1 = up
 * 		2 = down
 * 		3 = right
 * 		4 = left
 *
 * 		first save player position, then calculate the new positions
 * 		then check data->map[xyz] == 0 ? Only if true, save the new
 * 		player position.
*/
void	ft_movePlayer(t_data *data,int flag)
{
	float	newx;
	float	newy;

	newx = data->px;
	newy = data->py;
	data->run = 1;
	if (flag == 1 || flag == 2)
		ft_forbac(data, &newx, &newy, flag);
	if (flag == 3 || flag == 4)
		ft_leftright(data, &newx, &newy, flag);
	newx += data->px;
	newy += data->py;
	if (!data->map[(size_t)(newy)][(size_t)(newx)])
	{
		data->px = newx;
		data->py = newy;
	}
}

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
