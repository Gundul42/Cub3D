/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 08:47:25 by graja             #+#    #+#             */
/*   Updated: 2021/09/12 14:26:05 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

t_color	ft_rgb2col(int t, int r, int g, int b)
{
	t_color	new;

	new.a = t;
	new.r = r;
	new.g = g;
	new.b = b;
	return (new);
}

t_color	*ft_init_colors(void)
{
	t_color	*ptr;

	ptr = malloc(sizeof(t_color) * 5);
	if (!ptr)
		return (NULL);
	ptr[0] = ft_rgb2col(0, 0, 7, 100);
	ptr[1] = ft_rgb2col(0, 32, 107, 203);
	ptr[2] = ft_rgb2col(0, 237, 255, 255);
	ptr[3] = ft_rgb2col(0, 255, 170, 0);
	ptr[4] = ft_rgb2col(0, 0, 2, 0);
	return (ptr);
}

int	*ft_init_palette(t_data *data)
{
	int		i;
	int		j;
	t_hsv	color1;
	t_hsv	color2;
	t_hsv	final;

	data->palette = malloc(sizeof(int) * data->i + 1);
	if (!data->palette)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		color1 = rgb2hsv(data->breakpts[i]);
		color2 = rgb2hsv(data->breakpts[i + 1]);
		j = 0;
		while (j <= (data->i / 4) - 1)
		{
			final = ft_interpolate_hsv(color1, color2, j, data->i / 4);
			data->palette[i * data->i / 4 + j] = ft_make_color(hsv2rgb(final));
			j++;
		}
		i++;
	}
	return (data->palette);
}
