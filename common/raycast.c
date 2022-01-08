/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:15:47 by graja             #+#    #+#             */
/*   Updated: 2022/01/08 08:44:53 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
void	ft_firstHitHoricental(t_data *d, float alpha)
{
	float	diffY;
	float	diffX;

	if (alpha >= 270.0 || alpha <= 90.0)
	{
		diffY = d->py - floorf(d->py);
		diffX = diffY / tanf(ft_deg2rad(alpha));
		diffX = (d->px - diffX) * (float)(d->win_x / d->mapx);
		diffY = (d->py - diffY) * (float)(d->win_y / d->mapy);
		ft_draw_hit(d, diffX, diffY, 3.0, ft_make_trgb(0, 51, 0, 255));
	}
	else
	{
		diffY = d->py - ceilf(d->py);
		diffX = diffY / tanf(ft_deg2rad(alpha));
		diffX = (d->px - diffX) * (float)(d->win_x / d->mapx);
		diffY = (d->py - diffY) * (float)(d->win_y / d->mapy);
		ft_draw_hit(d, diffX, diffY, 3.0, ft_make_trgb(0, 51, 0, 255));
	}
}

void	ft_castRay(t_data *d, size_t x, size_t y)
{
	float	alpha;
	float	len;
	size_t	px;
	size_t	py;

	ft_getPlayerPos(d, &px, &py);
	alpha = atan2f(((float)y - (float)py), ((float)x - (float)px));
	alpha = ft_rad2deg(alpha);
	len = sqrtf(powf(((float)px - (float)x), 2) + powf(((float)py - (float)y), 2));
	ft_draw_angeled(d, px, py, alpha, len);
	printf("%7f \n", alpha);
	ft_firstHitHoricental(d, alpha);
}
