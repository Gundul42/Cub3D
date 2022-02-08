/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:43:37 by flormich          #+#    #+#             */
/*   Updated: 2022/02/06 20:55:45 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
void	ft_check_cell(t_data *d, size_t x, size_t y)
{
	if (d->map[y][x] == 0 || d->map[y][x] > 1)
	{
		if (x == 0 || x == d->mapx -1)
			the_end(d, "Unclosed map\n", 1);
		if (d->map[y - 1][x] == -2 || d->map[y + 1][x] == -2
			|| d->map[y][x - 1] == -2 || d->map[y][x + 1] == -2)
			the_end(d, "Unclosed map\n", 1);
	}
}

void	ft_check_closed_map(t_data *d)
{
	size_t	x;
	size_t	y;

	y = 0;
	if (d->mapx < 3 || d->mapy < 3)
		the_end(d, "Map too small\n", 1);
	while (y < d->mapy)
	{
		x = 0;
		while (x < d->mapx)
		{
			if (y == 0 || y == d->mapy -1)
			{
				if (d->map[y][x] == 0 || d->map[y][x] > 1)
					the_end(d, "Unclosed map\n", 1);
			}
			else
				ft_check_cell(d, x, y);
			x++;
		}
		y++;
	}
}
