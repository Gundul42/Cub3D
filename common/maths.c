/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:20:08 by graja             #+#    #+#             */
/*   Updated: 2022/01/06 17:07:48 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"


/* M_PI is a macro of math.h lib for the value of pi.
 * deg2rad converting from degree to radians
 * and rad2deg vice verca */

float	ft_deg2rad(float deg)
{
	return (deg * M_PI /180);
}

float	ft_rad2deg(float rad)
{
	return (rad / M_PI * 180);
}

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

void	ft_rotatePlayer(t_data *data, int flag)
{
	if (flag)
		data->dir += data->rotspeed;
	else
		data->dir -= data->rotspeed;
	if (data->dir > 360.0)
		data->dir -= 360.0;
	if (data->dir < 0)
		data->dir += 360.0;
	printf("DIR= %10f -- RAD=%10f \n", data->dir, ft_deg2rad(data->dir));
	ft_showPlayer(data);
}
