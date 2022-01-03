/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 09:18:45 by graja             #+#    #+#             */
/*   Updated: 2021/09/12 13:06:16 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

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

int	ft_calc_color(t_numbr new, int i, t_data *f)
{
	int		index;

	index = ft_smooth_color(new, i, f);
	if (i == f->i)
		return (0);
	return (f->palette[index]);
}

int	ft_smooth_color(t_numbr new, int i, t_data *data)
{
	double	smoothed;
	int		col;

	smoothed = log2(log2(new.real * new.real + new.img * new.img) / 2.0);
	col = (int)(sqrt((double)(i) + 10.0 - smoothed) * 255.0) % data->i;
	return (col);
}
