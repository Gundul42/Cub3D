/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 09:18:45 by graja             #+#    #+#             */
/*   Updated: 2022/01/03 13:30:29 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

int	ft_make_trgb(int t, int r, int g, int b)
{
	int	col;

	col = (t << 24 | r << 16 | g << 8 | b);
	return (col);
}

int	ft_make_color(t_color src)
{
	int	col;

	col = src.a << 24 | src.r << 16 | src.g << 8 | src.b;
	return (col);
}

t_color	ft_rgb2col(int t, int r, int g, int b)
{
	t_color	new;

	new.a = t;
	new.r = r;
	new.g = g;
	new.b = b;
	return (new);
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
