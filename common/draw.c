/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 10:12:54 by graja             #+#    #+#             */
/*   Updated: 2021/09/12 13:20:29 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

void	ft_draw_fractal(t_data *data)
{
	if (data->type == 1)
		mandelbrot(data);
	else if (data->type == 2)
		julia(data);
	else if (data->type == 3)
		ship(data);
}

void	ft_draw_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_zoom(t_data *data, double faktor)
{
	double	x;
	double	y;

	x = ((fabs(data->minreal) + fabs(data->maxreal)) / (float)(data->x));
	x *= faktor;
	y = ((fabs(data->minimg) + fabs(data->maximg)) / (float)(data->y));
	y *= faktor * (float)(data->y) / (float)(data->x);
	data->minreal += x;
	data->maxreal -= x;
	data->minimg += y;
	data->maximg -= y;
}

void	ft_mmove(t_data *data, int mousex, int mousey, double faktor)
{
	double	x;
	double	y;
	double	centerx;
	double	centery;

	centerx = ft_getreal(data->x / 2, data);
	centery = ft_getimg(data->y / 2, data);
	x = ft_getreal(mousex, data);
	y = ft_getimg(mousey, data);
	data->movex += (x - centerx) * faktor;
	data->movey += (y - centery) * faktor;
}
