/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:13:07 by graja             #+#    #+#             */
/*   Updated: 2022/02/05 11:35:54 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

/* calculates the forward / backward movement of the player
 * newx and newy are pointers to be able to give the values back
 * flag == 2 means backwards, so * -1
 * movement now depending on player look direction
 */
void	ft_forbac(t_data *data, float *newx, float *newy, int flag)
{
	float	step;

	step = (float)(data->speed) / (float)(data->tilesize);
	*newx = step * cosf(ft_deg2rad(data->dir));
	*newy = step * sinf(ft_deg2rad(data->dir));
	if (flag == 2)
	{
		*newx *= -1.0;
		*newy *= -1.0;
	}
}

/* EasyPeasy, tmp add/substract 90 degrees to look direction
 * and move forward, then return the original view direction :D
 */
void	ft_leftright(t_data *data, float *newx, float *newy, int flag)
{
	float	tmpdir;

	tmpdir = data->dir;
	if (flag == 3)
		data->dir += 90.0;
	else
		data->dir -= 90.0;
	if (data->dir > 360.0)
		data->dir -= 360.0;
	if (data->dir < 0)
		data->dir += 360.0;
	ft_forbac(data, newx, newy, 1);
	data->dir = tmpdir;
}

/* rotate the player view with cursor right/left
 * by the rotspeed value
 * get sure angle is only between 0 and 360
 */
void	ft_rotate_player(t_data *data, int flag)
{
	if (flag)
		data->dir += data->rotspeed;
	else
		data->dir -= data->rotspeed;
	if (data->dir > 360.0)
		data->dir -= 360.0;
	if (data->dir < 0)
		data->dir += 360.0;
}

/* get player quadrant in which it is moving
 * 270 - 359	= 0
 * 0 - 89	= 1
 * 90 - 179	= 2
 * 180 - 269	= 3
 */
int	ft_quad(t_data *data)
{
	if (data->dir >= 270 && data->dir < 360)
		return (0);
	if (data->dir >= 0 && data->dir < 90)
		return (1);
	if (data->dir >= 90 && data->dir < 180)
		return (2);
	return (3);
}
