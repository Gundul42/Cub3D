/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:20:08 by graja             #+#    #+#             */
/*   Updated: 2022/01/08 14:27:30 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"


/* M_PI is a macro of math.h lib for the value of pi.
 * deg2rad converting from degree to radians
 * and rad2deg vice verca
 *
 * IMPORTANT CHANGE !!!
 * we assume that North == 0.0 is the top of our screen !
 * no more gap between logical and tecnical north position
 * (technical it is the right side of our screen)
*/
float	ft_deg2rad(float deg)
{
	deg -= 90.0;
	return (deg * M_PI /180);
}

float	ft_rad2deg(float rad)
{
	float	deg;
	deg = 90.0 + rad / M_PI * 180;
	if (deg < 0)
		return (360.0 + deg);
	return (deg);
}

/* get distance between two points in float
*/
float	ft_getDist(float x1, float y1, float x2, float y2)
{
	return (sqrtf(powf((x1 - x2), 2) + powf((y1 - y2), 2)));
}

float	ft_PointDist(t_point a, t_point b)
{
	return (ft_getDist(a.x, a.y, b.x, b.y));
}
