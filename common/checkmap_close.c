/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:43:37 by flormich          #+#    #+#             */
/*   Updated: 2022/02/05 00:09:32 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static void	ft_test_ligne(t_data *d, size_t y)
{
	size_t	x;

	x = 0;
	while (x < d->mapx && d->map[y][x] == 0)
		x++;
	if (x < d->mapx && d->map[y][x] != 1)
		the_end(d, "Unclosed map\n", 1);
	else
	{
		while (x < d->mapx && d->map[y][x] == 1)
			x++;
		while (x < d->mapx && d->map[y][x] == 0)
			x++;
		if (x < d->mapx - 1)
			the_end(d, "Unclosed map\n", 1);
	}
}

static int	ft_easy_check(t_data *d, size_t y, size_t x, int first)
{
	if (first == 1)
	{
		if (x < d->mapx - 1 && d->map[y][x] != 1 && d->map[y][x] != 0)
			the_end(d, "Unclosed map\n", 1);
		if ((d->map[y][x] == 1 && d->map[y + 1][x] == 1)
			|| (d->map[y][x] == 1 && d->map[y + 1][x + 1] == 1)
			|| (d->map[y][x + 1] == 1 && d->map[y + 1][x] == 1))
			return (1);
	}
	else
	{
		if (x > 0 && x < d->mapx
			&& d->map[y][x] != 1 && d->map[y][x] != 0 && d->map[y][x] != ' ')
			the_end(d, "Unclosed map\n", 1);
		if ((d->map[y][x] == 1 && d->map[y + 1][x] == 1)
			|| (d->map[y][x] == 1 && d->map[y + 1][x - 1] == 1)
			|| (d->map[y][x - 1] == 1 && d->map[y + 1][x] == 1))
			return (1);
	}
	return (0);
}

static int	ft_test_first_column(t_data *d, size_t y, size_t x)
{
	while (d->map[y][x] == 0 && d->map[y + 1][x] == 0 && x < d->mapx)
		x++;
	if (ft_easy_check(d, y, x, 1) == 1)
		return (0);
	if (d->map[y][x] == 1)
	{
		while (d->map[y][x] == 1 && d->map[y + 1][x] == 0
			&& d->map[y + 1][x + 1] == 0 && x < d->mapx)
			x++;
		if (d->map[y][x] == 1
			&& (d->map[y + 1][x] == 1 || d->map[y + 1][x + 1] == 1))
			return (0);
		else
			the_end(d, "Unclosed map\n", 1);
	}
	while (d->map[y + 1][x] == 1 && d->map[y][x] == 0
		&& d->map[y][x + 1] == 0 && x < d->mapx)
		x++;
	if (d->map[y + 1][x] == 1 && (d->map[y][x] == 1 || d->map[y][x + 1] == 1))
		return (0);
	else
		the_end(d, "Unclosed map\n", 1);
	return (0);
}

static int	ft_test_last_column(t_data *d, size_t y, size_t x)
{
	while (d->map[y][x] == 0 && d->map[y + 1][x] == 0 && x > 0)
		x--;
	if (ft_easy_check(d, y, x, 0) == 1)
		return (0);
	if (d->map[y][x] == 1)
	{
		while (d->map[y][x] == 1 && d->map[y + 1][x] == 0
			&& d->map[y + 1][x - 1] == 0 && x < d->mapx)
			x--;
		if (d->map[y][x] == 1
			&& (d->map[y + 1][x] == 1 || d->map[y + 1][x - 1] == 1))
			return (0);
		else
			the_end(d, "Unclosed map\n", 1);
	}
	while (d->map[y + 1][x] == 1 && d->map[y][x] == 0
		&& d->map[y][x - 1] == 0 && x < d->mapx)
		x--;
	if (d->map[y + 1][x] == 1 && (d->map[y][x] == 1 || d->map[y][x - 1] == 1))
		return (0);
	else
		the_end(d, "Unclosed map\n", 1);
	return (0);
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
		if (y != d->mapy - 1)
		{
			ft_test_first_column(d, y, 0);
			ft_test_last_column(d, y, d->mapx - 1);
		}
		y++;
	}
}
