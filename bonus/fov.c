/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 10:07:37 by graja             #+#    #+#             */
/*   Updated: 2022/02/03 12:51:00 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

//draw field of view bonus style
//
void	ft_draw_fov_bonus(t_data *data)
{
	float	start;
	int		max;
	int		i;
	t_ray	ray;

	max = (float)data->fov / data->precision;
	i = 0;
	start = data->dir - (float)(data->fov / 2);
	while (i < max)
	{
		ray = ft_cast_ray(data, start);
		data->zbuf[i] = ray.dist;
		ft_draw_3d(data, ray, i);
		start += data->precision;
		i++;
	}
}

int	ft_player_in_door(t_data *data)
{
	if (data->doorx == (size_t)floorf(data->px) && (data->doory
			== (size_t)floorf(data->py)))
		return (1);
	return (0);
}
