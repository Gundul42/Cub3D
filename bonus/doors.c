/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:45:22 by graja             #+#    #+#             */
/*   Updated: 2022/02/01 11:54:17 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

static
int	ft_checktime(struct timeb start, struct timeb end)
{
	int	diff;

        diff = (int) 1000 * (end.time - start.time) + 
		(end.millitm - start.millitm);
	return(diff);
}

static
void	ft_dynopen(t_data *data, int rev, size_t x, size_t y)
{
	if (!rev)
	{
		if ((float)data->dopen[y][x] < (float)data->tilesize * 1.5)
			data->dopen[y][x] += 6;
		else
			data->dopen[y][x] *= 2;
	}
	else
	{
		if (data->dopen[y][x] < (int)data->tilesize * 2)
			data->dopen[y][x] -=6;
		else
			data->dopen[y][x] /= 2;
	}
}

static
void	ft_get_next_door(t_data *data, size_t *x, size_t *y)
{
	*x = (size_t)floorf(data->px);
	*y = (size_t)floorf(data->py);
	if (data->dir >= 225.0 && data->dir <= 315.0)
		*y = *y - 1;
	else if (data->dir < 225.0 && data->dir >= 135.0)
		*x = *x - 1;
	else if (data->dir < 135.0 && data->dir >= 45.0)
		*y = *y + 1;
	else
		*x = *x + 1;
}

int	ft_opendoor(t_data *data, size_t x, size_t y)
{
	static struct timeb	start;
	static struct timeb	end;
	static			int	chk = 0;
	static			int	rev = 0;

	if (!chk)
		ftime(&start);
	chk = 1;
	ftime(&end);
	if (ft_checktime(start, end) < 25)
		return (0);
	if (ft_player_in_door(data))
	{
		chk = 0;
		return (0);
	}
	if (rev < 0 && ft_checktime(start, end) < 1500)
		return (0);
	else if (rev < 0)
	{
		rev = 1;
		chk = 0;
		data->doors[y][x] = 2;
		return (0);
	}
	ft_dynopen(data, rev, x, y);
	chk = 0;
	if (data->dopen[y][x] > (int)data->tilesize * 5)
	{
		rev = -1;
		data->doors[y][x] = 1;
	}
	if (rev && data->dopen[y][x] == 0)
	{
		rev = 0;
		data->chkdoor = 0;
		data->doors[y][x] = 0;
		data->doorx = 0;
		data->doory = 0;
	}
	return (0);
}

void	the_doors(t_data *data)
{
	size_t	x;
	size_t	y;

	ft_get_next_door(data, &x, &y);
	if (data->chkdoor || data->map[y][x] != 4 || data->doors[y][x])
	{
		printf("No door at %ld, %ld\n", x, y);
		return ;
	}
	printf("Door is %ld, %ld\n", x, y);
	data->doorx = x;
	data->doory = y;
	data->chkdoor = 1;
	data->doors[y][x] = 2;
}
