/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:13:55 by graja             #+#    #+#             */
/*   Updated: 2022/02/05 17:53:06 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

static
void	ft_def_sprite(t_data *data, int count)
{
	if (data->slist[count].code == 3)
		data->slist[count].walkable = 1;
	if (data->slist[count].code == 4)
		data->slist[count].isdoor = 1;
	if (data->slist[count].code == 2)
		data->slist[count].walkable = 1;
}

static
int	ft_write_sprite_data(t_data *data, size_t x, size_t y, int count)
{
	t_point	cen;

	cen.x = (float)((x * data->tilesize) + data->tilesize / 2);
	cen.y = (float)((y * data->tilesize) + data->tilesize / 2);
	data->slist[count].p = cen;
	data->slist[count].code = data->map[y][x];
	ft_def_sprite(data, count);
	count++;
	return (count);
}

float	ft_find_alpha(t_data *data, int i)
{
	t_point	plyr;
	float	alpha;

	plyr = ft_get_player_point(data);
	alpha = ft_rad2deg(acosf((data->slist[i].p.x - plyr.x)
				/ data->slist[i].dist));
	if (data->dir >= 180.0 || data->dir <= 360.0)
		alpha = 360.0 - alpha;
	if (plyr.y < data->slist[i].p.y)
		alpha = 360.0 - alpha;
	if (data->dir >= 270.0 && data->dir <= 90.0 && plyr.y > data->slist[i].p.y)
		alpha = 360.0 + alpha;
	return (alpha);
}

//BubbleSort Sprites, long distances will be drawn first !
void	ft_sort_sprites(t_data *data)
{
	t_sprite	s;
	int			moved;
	int			i;

	if (data->snbr < 2)
		return ;
	moved = 1;
	while (moved)
	{
		i = 0;
		moved = 0;
		while (i < data->snbr - 1)
		{
			if (data->slist[i].dist < data->slist[i + 1].dist)
			{
				s = data->slist[i];
				data->slist[i] = data->slist[i + 1];
				data->slist[i + 1] = s;
				moved = 1;
			}
			i++;
		}
	}
}

void	ft_init_sprites(t_data *data)
{
	size_t	x;
	size_t	y;
	int		count;

	if (!data->snbr)
		the_end(data, "You need at least one Sprite on the map.\n", 1);
	data->slist = ft_calloc(data->snbr, sizeof(t_sprite));
	if (!data->slist)
		the_end(data, "Sprite out of Memory", 1);
	printf("! %d Sprites found on map\n", data->snbr);
	count = 0;
	y = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			if (data->map[y][x] > 1 && data->map[y][x] <= data->sprite_max)
				count = ft_write_sprite_data(data, x, y, count);
			x++;
		}
		y++;
	}
}
