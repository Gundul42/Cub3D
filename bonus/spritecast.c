/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:44:48 by graja             #+#    #+#             */
/*   Updated: 2022/02/02 19:25:50 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

/* allowed sprites start with number 2 and go until 9, to get the
 * right array index ray.sprite must be code - 2.
 */
static
t_ray	ft_sprite2ray(t_sprite s)
{
	t_ray	ray;

	ray.p = s.p;
	ray.dir = s.dir;
	ray.dist = s.dist;
	ray.flag = s.code - 2;
	ray.offset = 0;
	return (ray);
}

t_point	ft_spriteCenter(t_data *data, t_point inp, float alpha, int flag)
{
	size_t	x;
	size_t	y;

	ft_get_map_point(data, inp, &x, &y);
	if (!flag && alpha < 270.0 && alpha > 90.0)
		x--;
	if (flag && alpha >= 180.0 && alpha < 360.0)
		y--;
	inp.x = (float)((x * data->tilesize) + data->tilesize / 2);
	inp.y = (float)((y * data->tilesize) + data->tilesize / 2);
	return (inp);
}

void	ft_showSprites(t_data *data)
{
	int	i;
	t_ray	ray;

	i = 0;
	while (i < data->snbr)
	{
		ray = ft_sprite2ray(data->slist[i]);
		ft_drawOneSprite(data, ray);
		i++;
	}
}
