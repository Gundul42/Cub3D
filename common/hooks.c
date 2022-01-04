/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:44:07 by graja             #+#    #+#             */
/*   Updated: 2022/01/04 12:05:01 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

int	ft_loop_hook(t_data *img)
{
	mlx_do_sync(img->mlx);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (0);
}

int	ft_key_hook(int code, t_data *data)
{
	if (code == 65307)
		the_end(data);
	/*
	if (code == 65362)
		//ft_mmove(data, data->x / 2, data->y / 2 + data->y / 16, 0.1);
	if (code == 65364)
		//ft_mmove(data, data->x / 2, data->y / 2 - data->y / 16, 0.1);
	if (code == 65361)
		//ft_mmove(data, data->x / 2 + data->x / 16, data->y / 2, 0.1);
	if (code == 65363)
		//ft_mmove(data, data->x / 2 - data->x / 16, data->y / 2, 0.1);*/
	return (code);
}

int	ft_mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 1)
		ft_draw_line(data, 600, 400, x, y);
	return (0);
}
