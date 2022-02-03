/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 09:18:45 by graja             #+#    #+#             */
/*   Updated: 2022/02/02 19:18:11 by flormich         ###   ########.fr       */
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

int	ft_str2col(char *str, t_color *mycol)
{
	char	*bck;
	int		col[3];
	int		i;

	i = 0;
	while (i < 3)
	{
		bck = str;
		while (*bck && ft_isdigit(*bck))
			bck++;
		if (*bck && (ft_isalpha(*bck) || !(str - bck)))
			return (-1);
		if (i < 2 && !*bck)
			return (-1);
		if (*bck && *bck == ',')
			*bck = '\0';
		col[i] = ft_atoi(str);
		if (col[i] < 0 || col[i] > 255)
			return (-1);
		str = bck + 1;
		i++;
	}
	*mycol = ft_rgb2col(0, col[0], col[1], col[2]);
	return (ft_make_trgb(0, col[0], col[1], col[2]));
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
