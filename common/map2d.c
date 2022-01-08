/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:19:13 by graja             #+#    #+#             */
/*   Updated: 2022/01/08 16:27:12 by graja            ###   ########.fr       */
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
				ft_draw_rect(data, (x * xstep), (y * ystep), xstep - 1, ystep - 1, col);
			x++;
		}
		y++;
	}
	ft_showPlayer(data);
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

	col = ft_make_trgb(0, 0, 0, 255);
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
	ft_showPlayer(data);
}

int	ft_checkMap(t_data *data, t_point hit)
{
	size_t	x;
	size_t	y;
	x = (size_t)(hit.x) / data->win_x / data->mapx;
	y = (size_t)(hit.y) / data->win_y / data->mapy;
	if (x >= data->mapx)
		return (1);
	if (y >= data->mapy)
		return (1);
	//printf("Tile no.: %ld, %ld\n\n", x, y);
	return (0);
}



