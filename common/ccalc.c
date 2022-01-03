/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ccalc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:25:40 by graja             #+#    #+#             */
/*   Updated: 2021/09/12 12:45:22 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

/* calculate the value on the x axis depending on x location
 * on the screen and returns it.  */
double	ft_getreal(int x, t_data *f)
{
	double	max;

	max = fabs(f->maxreal) + fabs(f->minreal);
	max = (double)x * max / ((double)(f->x)) + f->minreal;
	max = max / f->zoom + f->movex;
	return (max);
}

/* calculate the value on the y axis depending on y location
 * on the screen and returns it */
double	ft_getimg(int y, t_data *f)
{
	double	max;

	max = fabs(f->maximg) + fabs(f->minimg);
	max = -1.0 * ((double)(y) *max / ((double)(f->y)) + f->minimg);
	max = max / f->zoom + f->movey;
	return (max);
}

/* interpolates from color1 to color2 by step i of imax in
 * hsv color space and return the new color in hsv, too
 */
t_hsv	ft_interpolate_hsv(t_hsv col1, t_hsv col2, int i, int maxi)
{
	t_hsv		new;
	double		step;

	step = (double)(i) / (double)(maxi);
	new.h = (col2.h - col1.h) * step + col1.h;
	new.s = (col2.s - col1.s) * step + col1.s;
	new.v = (col2.v - col1.v) * step + col1.v;
	return (new);
}
