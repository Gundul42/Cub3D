/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:13:55 by graja             #+#    #+#             */
/*   Updated: 2022/01/25 12:20:03 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

/* experimental Sprite def
 * assign different sprite abilities
 * depending on sprite code
 * on map
 */
static
void	ft_defSprite(t_data *data, int count)
{
	if (data->slist[count].code == 3)
		data->slist[count].walkable = 1;
	if (data->slist[count].code == 4)
		data->slist[count].collectable = 1;
	if (data->slist[count].code == 5)
		data->slist[count].canmove = 1;
}

static
int	ft_writeSpriteData(t_data *data, size_t x, size_t y, int count)
{
	t_point	cen;

	cen.x = (float)((x * data->tilesize) + data->tilesize / 2); 
	cen.y = (float)((y * data->tilesize) + data->tilesize / 2);
	data->slist[count].p = cen;
	data->slist[count].code = data->map[y][x];
	ft_defSprite(data, count);
	count++;
	return (count);
}

static
float	ft_findAlpha(t_data *data, int i)
{
	t_point	plyr;
	float	alpha;

	plyr = ft_getPlayerPoint(data);
        alpha =	ft_rad2deg(acosf((data->slist[i].p.x - plyr.x) /
				data->slist[i].dist));
	if (data->dir >= 180.0 || data->dir <= 360.0)
		alpha = 360.0 - alpha;
	if (plyr.y < data->slist[i].p.y)
		alpha = 360.0 - alpha;
	if (data->dir >= 270.0 && data->dir <= 90.0 && plyr.y > data->slist[i].p.y)
		alpha = 360.0 + alpha;
	return(alpha);
}

void	ft_updateSpriteData(t_data *data)
{
	t_point	plyr;
	int		i;

	i = 0;
	plyr = ft_getPlayerPoint(data);
	while (i < data->snbr)
	{
		data->slist[i].dist = ft_PointDist(plyr, data->slist[i].p);
		data->slist[i].dir = ft_findAlpha(data, i);
		//printf("DIR %5.2f Pposx %5.2f  --  Pposy %5.2f\n", data->dir, plyr.x, plyr.y);
		//ft_dumpSprite(data->slist[i]);
		i++;
	}
}

void	ft_initSprites(t_data *data)
{
	size_t	x;
	size_t	y;
	int	count;
	
	if (!data->snbr)
		the_end(data, "You need at least one Sprite on the map.\n", 1);
	data->slist = ft_calloc(data->snbr, sizeof(t_sprite));
	if (!data->slist)
		the_end(data, "Out of Memory", 1);
	printf("! %d Sprites found on map\n", data->snbr);
	count = 0;
	y = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			if (data->map[y][x] > 1)
				count = ft_writeSpriteData(data, x, y, count);
			x++;
		}
		y++;
	}
}
