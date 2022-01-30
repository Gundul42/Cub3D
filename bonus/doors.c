/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:45:22 by graja             #+#    #+#             */
/*   Updated: 2022/01/30 18:50:35 by graja            ###   ########.fr       */
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
	ft_dynopen(data, rev, x, y);
	chk = 0;
	if (data->dopen[y][x] > (int)data->tilesize * 5)
	{
		rev = 1;
		data->chkdoor = 0;
	}
	if (rev && data->dopen[y][x] == 0)
	{
		rev = 0;
		data->chkdoor = 0;
	}
	return (0);
}

