/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 10:07:37 by graja             #+#    #+#             */
/*   Updated: 2022/02/03 20:36:05 by graja            ###   ########.fr       */
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

int	ft_player_in_door(t_data *data, int *chk)
{
	*chk = 0;
	if (data->doorx == (size_t)floorf(data->px) && (data->doory
			== (size_t)floorf(data->py)))
		return (1);
	*chk = 1;
	return (0);
}

void	the_doors(t_data *data)
{
	size_t	x;
	size_t	y;

	ft_get_next_door(data, &x, &y);
	if (data->chkdoor || data->map[y][x] != 4 || data->doors[y][x])
		return ;
	data->doorx = x;
	data->doory = y;
	data->chkdoor = 1;
	data->doors[y][x] = 2;
}

int	ft_check_door_time(struct timeb start, struct timeb end)
{
	int	diff;

	diff = (int) 1000 * (end.time - start.time)
		+ (end.millitm - start.millitm);
	return (diff);
}
