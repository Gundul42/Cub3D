/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 10:07:37 by graja             #+#    #+#             */
/*   Updated: 2022/02/01 11:06:37 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

//draw field of view bonus style
//
void	ft_drawFovBonus(t_data *data)
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
		ray = ft_castRay(data, start); 
		data->zbuf[i] = ray.dist;
		ft_draw3D(data, ray, i);
		start += data->precision;
		i++;
	}
}

int	ft_player_in_door(t_data *data)
{
	if (data->doorx == (size_t)floorf(data->px) && (data->doory ==
				(size_t)floorf(data->py)))
		return (1);
	return (0);
}
