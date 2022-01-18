/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:43:37 by flormich          #+#    #+#             */
/*   Updated: 2022/01/18 13:58:16 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static	void	ft_test_ligne(t_data *d, size_t y)
{
	size_t	x;

	x = 0;
	while (d->map[y][x] == 0 && x < d->mapx)
		x++;
	if (d->map[y][x] != 1)
		the_end(d, "Unclosed map (1st or last line)\n", 1);
	else
	{
		while (d->map[y][x] == 1 && x < d->mapx)
			x++;
		while (d->map[y][x] == 0 && x < d->mapx)
			x++;
		if (x < d->mapx - 1)
			the_end(d, "Unclosed map (1st or last line)\n", 1);
	}
}

// NOK - Miss the fall where the first line begin later
static	void	ft_test_first_column(t_data *d, size_t y, size_t x, int x2)
{
	while (d->map[y][x] == 0 && x < d->mapx)
		x++;
	if (d->map[y][x] != 1)
		the_end(d, "Unclosed map (first column)\n", 1);
	else if (y < d->mapy - 1 && d->map[y + 1][x] != 1)
	{
		x2 = x - 1;
		while (x2 >= 0)
		{
			if (d->map[y + 1][x2] == 1)
				the_end(d, "Unclosed map (first column)\n", 1);
			x2--;
		}
		while (d->map[y][x] == 1 && x < d->mapx)
		{
			if (d->map[y + 1][x] == 1)
				break ;
			x++;
		}
		if (d->map[y][x] == 0 || x == d->mapx - 1)
			the_end(d, "Unclosed map (first column)\n", 1);
	}
}

static	void	ft_test_last_column(t_data *d, size_t y, size_t x, size_t x2)
{
	while (d->map[y][x] == 0 && x > 0)
		x--;
	if (d->map[y][x] != 1)
		the_end(d, "Unclosed map (last column)\n", 1);
	else if (y < d->mapy - 1 && d->map[y + 1][x] != 1)
	{
		x2 = x + 1;
		while (x2 < d->mapx)
		{
			if (d->map[y + 1][x2] == 1)
				the_end(d, "Unclosed map (last column)\n", 1);
			x2++;
		}
		while (d->map[y][x] == 1 && x > 0)
		{
			if (d->map[y + 1][x] == 1)
				break ;
			x--;
		}
		if (d->map[y][x] == 0 || x == 0)
			the_end(d, "Unclosed map (last column)\n", 1);
	}
}

void	ft_check_closed_map(t_data *d)
{
	size_t	y;

	y = 0;
	if (d->mapx < 3 || d->mapy < 3)
		the_end(d, "Map too small\n", 1);
	while (y < d->mapy)
	{
		if (y == 0 || y == d->mapy - 1)
		{
			ft_test_ligne(d, 0);
			ft_test_ligne(d, d->mapy - 1);
		}
		ft_test_first_column(d, y, 0, 0);
		ft_test_last_column(d, y, d->mapx - 1, 0);
		y++;
	}
}
