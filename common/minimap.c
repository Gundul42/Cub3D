/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 10:12:21 by graja             #+#    #+#             */
/*   Updated: 2022/01/15 10:14:03 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

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


