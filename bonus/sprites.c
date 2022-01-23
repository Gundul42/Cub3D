/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:13:55 by graja             #+#    #+#             */
/*   Updated: 2022/01/23 09:37:35 by graja            ###   ########.fr       */
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

	plyr = ft_getPlayerPoint(data);
	return(ft_rad2deg(acosf((plyr.x - data->slist[i].p.x) / data->slist[i].dist)));
}

void	ft_dumpSprite(t_sprite s)
{
	printf("****************************************************\n");
	printf("Position            : x%5.2f -- y%5.2f\n", s.p.x, s.p.y);
	printf("angle to player     : %5.2f degrees\n", s.dir);
	printf("distance to player  : %5.2f pixels\n",s.dist);
	printf("code                : %d\n", s.code);
	printf("is walkable         : %d\n", s.walkable);
	printf("is collectable      : %d\n", s.collectable);
	printf("can move            : %d\n", s.canmove);
	printf("****************************************************\n\n");
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
		ft_dumpSprite(data->slist[i]);
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
