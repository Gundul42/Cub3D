/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 09:43:46 by graja             #+#    #+#             */
/*   Updated: 2022/02/03 19:07:24 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

void	ft_dump_sprite(t_sprite s)
{
	printf("****************************************************\n");
	printf("Position            : x%5.2f -- y%5.2f\n", s.p.x, s.p.y);
	printf("angle to player     : %5.2f degrees\n", s.dir);
	printf("distance to player  : %5.2f pixels\n", s.dist);
	printf("code                : %d\n", s.code);
	printf("is walkable         : %d\n", s.walkable);
	printf("is collectable      : %d\n", s.collectable);
	printf("can move            : %d\n", s.canmove);
	printf("****************************************************\n\n");
}

float	ft_ray_correct(t_data *data, t_ray ray)
{
	float	diff;

	if (data->correct)
		return (ray.dist);
	diff = (data->dir - ray.dir);
	return (ray.dist * cosf(ft_deg2rad(diff)));
}

void	ft_move_bonus_player(t_data *data, int flag)
{
	float	newx;
	float	newy;

	newx = data->px;
	newy = data->py;
	data->run = 1;
	if (flag == 1 || flag == 2)
		ft_forbac(data, &newx, &newy, flag);
	if (flag == 3 || flag == 4)
		ft_leftright(data, &newx, &newy, flag);
	newx += data->px;
	newy += data->py;
	if (data->map[(size_t)(newy)][(size_t)(newx)] == 0
			|| data->map[(size_t)(newy)][(size_t)(newx)] == 2
			|| data->map[(size_t)(newy)][(size_t)(newx)] == 3
			|| data->doors[(size_t)(newy)][(size_t)(newx)] == 1)
	{
		data->px = newx;
		data->py = newy;
	}
}

void	ft_update_sprite_data(t_data *data)
{
	t_point	plyr;
	int		i;

	i = 0;
	plyr = ft_get_player_point(data);
	while (i < data->snbr)
	{
		data->slist[i].dist = ft_point_dist(plyr, data->slist[i].p);
		data->slist[i].dir = ft_find_alpha(data, i);
		i++;
	}
	ft_sort_sprites(data);
}

int	ft_get_sprite_pixel(t_data *data, int x, int y, int i)
{
	char	*dst;
	int		bpp;
	int		ll;
	int		endian;

	if (x < 0 || x > (int)(data->tilesize) || y < 0 ||
			y > (int)(data->tilesize))
		return (0);
	dst = mlx_get_data_addr(data->sprite[i], &bpp,
			&ll, &endian);
	dst += (y * ll + x * (bpp / 8));
	return (*(unsigned int *)dst);
}
