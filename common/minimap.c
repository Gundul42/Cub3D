/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 10:12:21 by graja             #+#    #+#             */
/*   Updated: 2022/01/16 11:47:43 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
void	ft_mapHeading(t_data *data)
{
	int	x;
	float	alpha;
	int	len;
	int	i;

	alpha = data->dir - (float)(data->fov / 2);
	i = 0;
	while (i <= data->fov)
	{
		x = data->win_x / data->minimap / 2;
		len = data->win_x / data->minimap / data->miniZ;
		x += len / 2;
		len *= 2;
		while (len)
		{
			ft_drawMapPixel(data, x + cos(ft_deg2rad(alpha)) * len, 
					x + sin(ft_deg2rad(alpha)) * len, 0);
			len--;
		}
		alpha += 8.0;
		i += 8;
	}
}

void	ft_drawMapPixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > (int)(data->win_x / data->minimap) || y < 0 || 
			y > (int)(data->win_x / data->minimap))
		return ;
	dst = data->addr1 + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_drawMapBck(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)(data->win_x / data->minimap))
	{
		x = 0;
		while (x < (int)(data->win_x / data->minimap))
		{
			ft_drawMapPixel(data, x, y, data->csky);
			x++;
		}
		y++;
	}
}

void	ft_drawDot(t_data *data, int i, int j)
{
	int	x;
	int	y;
	int	len;

	len = data->win_x / data->minimap / data->miniZ;
	y = j * len;
	while (y < (j + 1) * len)
	{
		x = i * len;
		while (x < (i + 1) * len)
		{
			ft_drawMapPixel(data, x, y, ft_make_trgb(128, 0, 0, 255));
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
	ft_drawMapBck(data);
	while (j < (int)data->miniZ)
	{
		i = 0;
		while (i < (int)data->miniZ)
		{
			if (ft_isWall(data, data->px - (int)data->miniZ / 2 + i, 
						data->py - (int)data->miniZ / 2 + j))
				ft_drawDot(data, i, j);
			i++;
		}
		j++;
	}
	ft_mapHeading(data);
}

void	ft_MapZoom(t_data *data, int flag)
{
	if (flag)
	{
		data->miniZ += 8;
		if (data->miniZ > 32)
		       data->miniZ = 32;
	}
	else
	{
		data->miniZ -= 8;
		if (data->miniZ < 8)
			data->miniZ = 8;
	}
}

