/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:13:55 by graja             #+#    #+#             */
/*   Updated: 2022/01/22 15:19:30 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

static
int	ft_checkMapPoint(t_data *data, t_point p, size_t x, size_t y)
{
	size_t	a;
	size_t	b;


	ft_getMapPoint(data, p, &a, &b);
	if (a == x && b == y)
	{
		//printf("x = %ld  y = %ld, a = %ld, b = %ld\n", x, y, a, b);
		return (1);
	}
	return (0);
}

static
float	 ft_getDir(t_data *data, t_point plyr, t_point p)
{
	float	dir;
	
	if (data->dir != 99999999)
		dir = ft_rad2deg(atanf((p.y - plyr.y) / (p.x - plyr.x)));
	return (ft_valAlpha(dir));
}

static
void	ft_lstAddSprite(t_data *data, t_point p, int flag, int i)
{
	t_point	plyr;

	plyr = ft_getPlayerPoint(data);
	p = ft_spriteCenter(data, p, data->dir, flag);
	(data->slist[i]).dir = ft_getDir(data, plyr, p);
	(data->slist[i]).dist = ft_PointDist(plyr, p);
	(data->slist[i]).init = i + 1;
	(data->slist[i]).p = p;
}

void	ft_insertSprite(t_data *data, t_point p, int val, int flag)
{
	int	i;
	size_t	x;
	size_t	y;

	if (val < 1)
		return ;
	i = 0;
	ft_getMapPoint(data, p, &x, &y);
	while ((data->slist[i]).init)
	{
		if (ft_checkMapPoint(data, (data->slist[i]).p, x, y))
			return ;
		i++;
	}
	ft_lstAddSprite(data, p, flag, i);
	(data->slist[i]).val = val + 1;
}
