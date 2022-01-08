/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:15:47 by graja             #+#    #+#             */
/*   Updated: 2022/01/08 18:59:19 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
t_point	ft_firstHitHorizontal(t_data *d, float alpha)
{
	t_point	diff;

	if (alpha >= 270.0 || alpha <= 90.0)
		diff.y = d->py - floorf(d->py);
	else
		diff.y = d->py - ceilf(d->py);
	diff.x = diff.y / tanf(ft_deg2rad(alpha));
	diff.x = (d->px - diff.x) * (float)(d->win_x / d->mapx);
	diff.y = (d->py - diff.y) * (float)(d->win_y / d->mapy);
	ft_draw_circle(d, diff.x, diff.y, 3.0, ft_make_trgb(0, 39, 78, 19));
	return (diff);
}

/* 
 * alpha must be not equal to 0 or 180.
 * in this case diffY would be infinite and program segfaults
 */
static
t_point	ft_firstHitVertical(t_data *d, float alpha)
{
	t_point	diff;

	if (alpha >= 0.0 && alpha <= 180.0)
		diff.x = ceilf(d->px) - d->px;
	else
		diff.x = floorf(d->px) - d->px;
	diff.y = diff.x * tanf(ft_deg2rad(alpha));
	diff.x = (d->px + diff.x) * (float)(d->win_x / d->mapx);
	diff.y = (d->py + diff.y) * (float)(d->win_y / d->mapy);
	if (diff.x > 0.0 && diff.x < d->win_x && diff.y > 0.0 && diff.y < d->win_y)
		ft_draw_circle(d, diff.x, diff.y, 3.0, ft_make_trgb(0, 102, 0, 0));
	return (diff);
}

static
t_point	ft_find_collision(t_data *data, float alpha, t_point h, t_point v)
{
	t_point	hit;
	float	deltaX;
	float	deltaY;

	deltaX = ((float)(data->win_x / data->mapx)) / tanf(ft_deg2rad(alpha));
	deltaY = ((float)(data->win_y / data->mapy)) * tanf(ft_deg2rad(alpha));
	printf("DeltX %f   DeltaY%f\n", deltaX, deltaY);
	hit = ft_getPlayerPoint(data);
		if (ft_PointDist(hit, v) < ft_PointDist(hit, h))
		{
			hit = v;
			if (alpha >= 0 && alpha <= 180)
			{
				v.x += (float)tdata->win_x / data->mapx);
				v.y += deltaY;
			}
			else
			{
				v.x -= (float)(data->win_x / data->mapx);
				v.y -= deltaY;
			}
			ft_draw_circle(data, v.x, v.y, 3.0, ft_make_trgb(0, 102, 0, 0));
		}
		else
		{
			hit = h;
			if (alpha >= 270 && alpha <= 90)
			{
				h.x += deltaX;
				h.y += (float)(data->win_y / data->mapy);
			}
			else
			{
				h.x -= deltaX;
				h.y -= (float)(data->win_y / data->mapy);
			}
			ft_draw_circle(data, h.x, h.y, 3.0, ft_make_trgb(0, 39, 78, 19));
		}
		ft_printBox(data, hit);
	return (hit);
}

void	ft_castRay(t_data *d, size_t x, size_t y)
{
	float	alpha;
	float	len;
	t_point	plyr;
	t_point	hor;
	t_point	vet;

	plyr = ft_getPlayerPoint(d);
	alpha = atan2f(((float)y - (float)plyr.y), ((float)x - (float)plyr.x));
	alpha = ft_rad2deg(alpha);
	len = sqrtf(powf(((float)plyr.x - (float)x), 2) + powf(((float)plyr.y - (float)y), 2));
	ft_draw_angeled(d, plyr.x, plyr.y, alpha, len);
	hor = ft_firstHitHorizontal(d, alpha);
	vet = ft_firstHitVertical(d, alpha);
//	printf("%f :: %f\n\n", ft_PointDist(plyr, hor), ft_PointDist(plyr, vet));
	ft_find_collision(d, alpha, hor, vet);
}
