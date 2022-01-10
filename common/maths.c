/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:20:08 by graja             #+#    #+#             */
/*   Updated: 2022/01/10 13:53:47 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"


/* M_PI is a macro of math.h lib for the value of pi.
 * deg2rad converting from degree to radians
 * and rad2deg vice verca
 */
float	ft_deg2rad(float deg)
{
	return (deg * M_PI /180.0);
}

float	ft_rad2deg(float rad)
{
	float	deg;
	deg = rad / M_PI * 180.0;
	if (deg < 0)
		return (360.0 + deg);
	return (deg);
}

/*
 * alpha can only be something between 0 >= alpha >= 360 !
 */
float	ft_valAlpha(float alpha)
{
	if (alpha < 0.0)
		alpha += 360.0;
	if (alpha > 360.0)
		alpha -= 360.0;
	return (alpha);
}

/* get distance between two points in float
*/
float	ft_getDist(float x1, float y1, float x2, float y2)
{
	return (sqrtf(powf((x1 - x2), 2) + powf((y1 - y2), 2)));
}
