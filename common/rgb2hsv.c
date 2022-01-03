/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb2hsv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:18:27 by graja             #+#    #+#             */
/*   Updated: 2022/01/03 13:31:24 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

/* color conversion see formulae on:
 * https://en.wikipedia.org/wiki/HSL_and_HSV#Color_conversion_formulae
 * in each direction */
static
double	ft_calc_hue(t_color in, double max, double diff)
{
	double	h;

	if (in.r >= max)
		h = (in.g - in.b) / diff;
	else if (in.g >= max)
		h = 2.0 + (in.b - in.r) / diff;
	else
		h = 4.0 + (in.r - in.g) / diff;
	h *= 60.0;
	if (h < 0.0)
		h += 360.0;
	return (h);
}

t_hsv	rgb2hsv(t_color in)
{
	t_hsv	out;
	double	max;
	double	diff;

	max = fmax(in.r, fmax(in.g, in.b));
	out.v = max;
	diff = max - fmin(in.r, fmin(in.g, in.b));
	if (diff < 0.00001)
	{
		out.s = 0;
		out.h = 0;
		return (out);
	}
	if (max > 0.0)
		out.s = (diff / max);
	else
	{
		out.s = 0.0;
		out.h = NAN;
		return (out);
	}
	out.h = ft_calc_hue(in, max, diff);
	return (out);
}
