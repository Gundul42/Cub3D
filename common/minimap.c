/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 10:12:21 by graja             #+#    #+#             */
/*   Updated: 2022/02/02 22:00:40 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_draw_map_pixel(t_data *d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > (int)(d->win_x / d->minimap) || y < 0 ||
			y > (int)(d->win_x / d->minimap))
		return ;
	dst = d->addr1 + (y * d->line_length + x * (d->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_map_bck(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)(data->win_x / data->minimap))
	{
		x = 0;
		while (x < (int)(data->win_x / data->minimap))
		{
			ft_draw_map_pixel(data, x, y, data->csky);
			x++;
		}
		y++;
	}
}

void	ft_draw_dot(t_data *data, int i, int j, int color)
{
	int	x;
	int	y;
	int	len;

	len = data->win_x / data->minimap / data->mini_z;
	y = j * len;
	while (y < (j + 1) * len)
	{
		x = i * len;
		while (x < (i + 1) * len)
		{
			ft_draw_map_pixel(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	ft_draw2dmap(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < (int)data->mini_z)
	{
		i = 0;
		while (i < (int)data->mini_z)
		{
			if (ft_is_wall(data, data->px - (int)data->mini_z / 2 + i,
					data->py - (int)data->mini_z / 2 + j) == 1)
				ft_draw_dot(data, i, j, ft_make_trgb(128, 0, 0, 255));
			else if (ft_is_wall(data, data->px - (int)data->mini_z / 2 + i,
					data->py - (int)data->mini_z / 2 + j) == 2)
				ft_draw_dot(data, i, j, ft_make_trgb(0, 0, 255, 0));
			else if (ft_is_wall(data, data->px - (int)data->mini_z / 2 + i,
					data->py - (int)data->mini_z / 2 + j) == 3)
				ft_draw_dot(data, i, j, ft_make_trgb(0, 128, 64, 0));
			else if (ft_is_wall(data, data->px - (int)data->mini_z / 2 + i,
					data->py - (int)data->mini_z / 2 + j) == 4)
				ft_draw_dot(data, i, j, ft_make_trgb(0, 58, 157, 35));
			i++;
		}
		j++;
	}
}

void	ft_map_zoom(t_data *data, int flag)
{
	if (flag)
	{
		data->mini_z += 8;
		if (data->mini_z > 32)
			data->mini_z = 32;
	}
	else
	{
		data->mini_z -= 8;
		if (data->mini_z < 8)
			data->mini_z = 8;
	}
}
