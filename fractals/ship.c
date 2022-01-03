/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:51:21 by graja             #+#    #+#             */
/*   Updated: 2021/09/12 13:18:41 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

/* calculate the burnin ship set :
 * Zn+1 = (|Re(Zn)| + |Im(Zn)|)²+ c1   Z0 = 0
 * x axis is real, y axis is imginary */
static
void	ft_iterate_ship(t_data *data, int x, int y)
{
	t_numbr	old;
	t_numbr	new;
	t_numbr	poi;
	int		i;

	i = 0;
	new.real = 0;
	new.img = 0;
	poi.real = ft_getreal(x, data);
	poi.img = ft_getimg(y, data);
	while (i < data->i)
	{
		old.real = new.real;
		old.img = new.img;
		new.real = old.real * old.real - old.img * old.img - poi.real;
		new.img = 2 * fabs(old.real * old.img) - poi.img;
		if (new.real * new.real + new.img * new.img > 4)
			break ;
		i++;
	}
	ft_draw_pixel(data, x, y, ft_calc_color(new, i, data));
}

int	ship(t_data *data)
{
	int	x;
	int	y;	

	y = 0;
	while (y < data->y)
	{
		x = 0;
		while (x < data->x)
		{
			ft_iterate_ship(data, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
