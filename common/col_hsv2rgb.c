/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsv2rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:43:11 by graja             #+#    #+#             */
/*   Updated: 2022/01/03 13:30:57 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
t_color	ft_getrgb_a(t_hsv in, t_hsv pqt, long i)
{
	t_color	out;

	out.r = 0;
	out.g = 0;
	out.b = 0;
	if (i == 0)
	{
		out.r = in.v;
		out.g = pqt.v;
		out.b = pqt.h;
	}
	else if (i == 1)
	{
		out.r = pqt.s;
		out.g = in.v;
		out.b = pqt.h;
	}
	else if (i == 2)
	{
		out.r = pqt.h;
		out.g = in.v;
		out.b = pqt.v;
	}
	return (out);
}

static
t_color	ft_getrgb_b(t_hsv in, t_hsv pqt, long i)
{
	t_color	out;

	if (i == 3)
	{
		out.r = pqt.h;
		out.g = pqt.s;
		out.b = in.v;
	}
	else if (i == 4)
	{
		out.r = pqt.v;
		out.g = pqt.h;
		out.b = in.v;
	}
	else
	{
		out.r = in.v;
		out.g = pqt.h;
		out.b = pqt.s;
	}
	return (out);
}

t_color	hsv2rgb(t_hsv in)
{
	double	hue;
	double	ff;
	long	i;
	t_color	out;
	t_hsv	pqt;

	hue = in.h;
	if (hue >= 360.0)
		hue = 0.0;
	hue /= 60.0;
	i = (long)hue;
	ff = hue - i;
	pqt.h = in.v * (1.0 - in.s);
	pqt.s = in.v * (1.0 - (in.s * ff));
	pqt.v = in.v * (1.0 - (in.s * (1.0 - ff)));
	if (i < 3)
		out = ft_getrgb_a(in, pqt, i);
	else
		out = ft_getrgb_b(in, pqt, i);
	return (out);
}
