/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:07:05 by graja             #+#    #+#             */
/*   Updated: 2021/09/17 12:57:22 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

void	ft_reset_mandelbrot(t_data *data)
{
	data->type = 1;
	data->maxreal = 1.0;
	data->minreal = -2.0;
	data->maximg = 1.0;
	data->minimg = -1.0;
	data->zoom = 1.0;
	data->movex = 0;
	data->movey = 0;
	ft_draw_fractal(data);
}

void	ft_goto_julia(t_data *data, int x, int y)
{
	data->type = 2;
	data->maxreal = 4.0;
	data->minreal = -4.0;
	data->maximg = 2.5;
	data->minimg = -2.5;
	data->juliaimg = ft_getimg(y, data);
	data->juliareal = ft_getreal(x, data);
	data->zoom = 0.68;
	data->movex = 0;
	data->movey = 0;
	ft_draw_fractal(data);
}

void	ft_init_window(t_data *data, int x, int y, int i)
{
	data->x = x;
	data->y = y;
	data->i = i;
	data->movex = 0;
	data->movey = 0;
	if (data->type == 1)
		ft_init_mandel(data);
	else if (data->type == 2)
		ft_init_julia(data);
	else if (data->type == 3)
		ft_init_ship(data);
}

t_data	*ft_blank(t_data *data)
{
	data = malloc(sizeof(t_data));
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
	data->type = 0;
	data->x = 900;
	data->y = 600;
	data->i = 500;
	data->minreal = .0;
	data->maxreal = .0;
	data->minimg = .0;
	data->maximg = .0;
	data->juliareal = .0;
	data->juliaimg = .0;
	data->zoom = 1.0;
	data->movex = .0;
	data->movey = .0;
	data->breakpts = NULL;
	data->palette = NULL;
	return (data);
}
