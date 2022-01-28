/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:45:22 by graja             #+#    #+#             */
/*   Updated: 2022/01/28 19:47:02 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

static
float	ft_checktime(struct timeb start, struct timeb end)
{

	return((end.time - start.time) + (end.millitm - start.millitm));
}

static
void	ft_dynopen(t_data *data, int rev)
{
	if (!rev)
	{
		if ((float)data->dopen < (float)data->tilesize * 1.5)
			data->dopen += 6;
		else
			data->dopen *= 2;
	}
	else
	{
		if (data->dopen < (int)data->tilesize * 2)
			data->dopen -=6;
		else
			data->dopen /= 2;
	}
	printf("%d\n", data->dopen);
}


int	ft_opendoor(t_data *data)
{
	static struct timeb	start;
	static struct timeb	end;
	static			int	chk = 0;
	static			int	rev = 0;

	if (!chk)
		ftime(&start);
	chk = 1;
	ftime(&end);
	if (ft_checktime(start, end) < 0.8)
		return (0);
	ft_dynopen(data, rev);
	chk = 0;
	if (data->dopen > (int)data->tilesize * 5)
	{
		rev = 1;
		data->chkdoor = 0;
	}
	if (rev && data->dopen == 0)
	{
		rev = 0;
		data->chkdoor = 0;
	}
	return (0);
}

