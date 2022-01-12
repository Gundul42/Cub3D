/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:19:13 by graja             #+#    #+#             */
/*   Updated: 2022/01/12 18:43:51 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_draw2dmap(t_data *data)
{
	size_t	x;
	size_t	y;
	size_t	step;
	int	col;

	col = ft_make_trgb(0, 255, 217, 102);
	y = (size_t)data->py - 5;
	step = data->tilesize;
	while (y < (size_t)data->py + 5)
	{
		x = (size_t)data->px - 5;
		while (x < (size_t)data->px + 5)
		{
			if (data->map[y][x])
				ft_draw_rect(data, (x * step), (y * step), step - 1, step - 1, col);
			x++;
		}
		y++;
	}
	//ft_showPlayer(data);
}

/* calculates the player position (which is in maptiles) and shows it in the map
 * now including view direction of the player
 * color is hardcoded because only temp solution
 */
void	ft_showPlayer(t_data *data)
{
	size_t	x;
	size_t	y;
	int	col;

	col = ft_make_trgb(0, 255, 51, 51);
	ft_getPlayerPos(data, &x, &y);
	ft_draw_circle(data, x, y, 4, col);
	ft_draw_angeled(data, x, y, data->dir, data->tilesize / 4);
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
	if (!data->map[(size_t)(newy - 0.25)][(size_t)(newx)])
	{
		data->px = newx;
		data->py = newy;
	}
	//ft_showPlayer(data);
}

int	ft_checkMapNS(t_data *data, t_point p, float alpha)
{
	size_t	x;
	size_t	y;

	printf("NS\n");
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

	printf("WE\n");
	if (p.x  >= data->mapx * data->tilesize || p.y >= data->mapy * data->tilesize)
		return (0);
	ft_getMapPoint(data, p, &x, &y);
	printf("%ld - %ld :: %ld - %ld\n", x, y, data->mapx, data->mapy);
	printf("%f\n\n", alpha);
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
