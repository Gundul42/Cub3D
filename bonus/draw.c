/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:57:21 by graja             #+#    #+#             */
/*   Updated: 2022/01/18 15:56:13 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

void	ft_drawSpriteFov(t_data *data)
{
	float	start;
	int		max;
	int		i;
	int		c;
	t_ray	ray;

	max = (float)data->fov / data->precision;
	i = 0;
	c = 0;
	start = data->dir - (float)(data->fov / 2);
	while (i < max)
	{
		ray = ft_castRay(data, start); 
		//ft_dumpRay(data, ray);
		ft_draw3D(data, ray, i);
		if (ft_spriteRay(data, start, &ray))
			c++;
		start += data->precision;
		i++;
	}
	printf("%d Sprites found\n", c);
}
