/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 08:38:30 by graja             #+#    #+#             */
/*   Updated: 2022/02/05 11:51:56 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_initialize_player(t_data *d, size_t x, size_t y, char dir)
{
	d->px = x + 0.4;
	d->py = y + 0.4;
	if (dir == 'N')
		d->dir = 270.0;
	else if (dir == 'S')
		d->dir = 90.0;
	else if (dir == 'E')
		d->dir = 0.0;
	else if (dir == 'W')
		d->dir = 180.0;
}

void	ft_get_player_pos(t_data *d, size_t *x, size_t *y)
{
	*x = d->px * d->tilesize;
	*y = d->py * d->tilesize;
}

static
int	ft_whatishere(t_data *data, size_t x, size_t y)
{
	int	diag;
	int	dir;

	dir = ft_quad(data);
	diag = abs((int)data->px - x) + abs((int)data->py -y);
	if (!x || !y || data->map[y][x] == 1 || data->map[y][x] == 5)
		return (1);
	if (diag != 2)
		return (0);
	if (dir == 0 && data->map[y + 1][x] == 1 && data->map[y][x - 1] == 1)
		return (1);
	if (dir == 1 && data->map[y - 1][x] == 1 && data->map[y][x - 1] == 1)
		return (1);
	if (dir == 2 && data->map[y - 1][x] == 1 && data->map[y][x + 1] == 1)
		return (1);
	if (dir == 3 && data->map[y + 1][x] == 1 && data->map[y][x + 1] == 1)
		return (1);
	return (0);
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
void	ft_move_player(t_data *data, int flag)
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
	if (!ft_whatishere(data, newx, newy))
	{
		data->px = newx;
		data->py = newy;
	}
}

void	ft_mouse_rot_player(t_data *data)
{
	if (fabsf(data->rotmouse) < 0.06)
		data->rotmouse = 0.0;
	data->dir += data->rotspeed * data->rotmouse * -1.0;
	if (data->dir > 360.0)
		data->dir -= 360.0;
	if (data->dir < 0)
		data->dir += 360.0;
}
