/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 16:37:54 by graja             #+#    #+#             */
/*   Updated: 2021/09/17 13:13:28 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

int	ft_key_hook(int code, t_data *data)
{
	if (code == 65307)
		the_end(data);
	if (code == 65362)
		ft_mmove(data, data->x / 2, data->y / 2 + data->y / 16, 0.1);
	if (code == 65364)
		ft_mmove(data, data->x / 2, data->y / 2 - data->y / 16, 0.1);
	if (code == 65361)
		ft_mmove(data, data->x / 2 + data->x / 16, data->y / 2, 0.1);
	if (code == 65363)
		ft_mmove(data, data->x / 2 - data->x / 16, data->y / 2, 0.1);
	ft_draw_fractal(data);
	return (code);
}

int	ft_mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 4)
	{
		ft_mmove(data, x, y, 0.3);
		data->zoom *= 1.1;
		ft_draw_fractal(data);
	}
	if (button == 5)
	{
		ft_mmove(data, x, y, 0.3);
		data->zoom /= 1.1;
		if (data->zoom < 0.3)
			data->zoom = 0.3;
		ft_draw_fractal(data);
	}
	if (button == 8)
		ft_reset_mandelbrot(data);
	if (button == 2)
		ft_goto_julia(data, x, y);
	return (0);
}

int	ft_loop_hook(t_data *img)
{
	mlx_do_sync(img->mlx);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (0);
}
