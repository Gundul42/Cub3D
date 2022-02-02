/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 22:00:20 by flormich          #+#    #+#             */
/*   Updated: 2022/02/02 22:00:48 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_map_heading(t_data *data)
{
	int		x;
	float	alpha;
	int		len;
	int		i;

	alpha = data->dir - (float)(data->fov / 2);
	i = 0;
	while (i <= data->fov)
	{
		x = data->win_x / data->minimap / 2;
		len = data->win_x / data->minimap / data->mini_z;
		x += len / 2;
		len *= 2;
		while (len)
		{
			ft_draw_map_pixel(data, x + cos(ft_deg2rad(alpha)) * len,
				x + sin(ft_deg2rad(alpha)) * len, 0);
			len--;
		}
		alpha += 8.0;
		i += 8;
	}
}
