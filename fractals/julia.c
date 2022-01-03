/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:23:54 by graja             #+#    #+#             */
/*   Updated: 2021/09/12 13:15:32 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

/* calculate the julia set :
 * Zn+1 = Zn²+Kc
 * x axis is real, y axis is imginary
 * K is a konstant taken from mandelbrot set
 * Z is not starting with 0 like mandelbrot but with the corresponding
 * values found at x and y on the screen, while c is konstant */
static
void	ft_julia_iterate(t_data *data, int x, int y)
{
	t_numbr	old;
	t_numbr	new;
	t_numbr	poi;
	int		i;

	i = 0;
	new.real = ft_getreal(x, data);
	new.img = ft_getimg(y, data);
	poi.real = data->juliareal;
	poi.img = data->juliaimg;
	while (i < data->i)
	{
		old.real = new.real;
		old.img = new.img;
		new.real = old.real * old.real - old.img * old.img + poi.real;
		new.img = 2 * old.real * old.img + poi.img;
		if (new.real * new.real + new.img * new.img > 4)
			break ;
		i++;
	}
	ft_draw_pixel(data, x, y, ft_calc_color(new, i, data));
}

int	julia(t_data *data)
{
	int	x;
	int	y;	

	y = 0;
	while (y < data->y)
	{
		x = 0;
		while (x < data->x)
		{
			ft_julia_iterate(data, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
