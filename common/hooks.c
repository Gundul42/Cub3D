/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:39:01 by flormich          #+#    #+#             */
/*   Updated: 2022/02/04 12:11:20 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

int	ft_loop_hook(t_data *img)
{
	mlx_do_sync(img->mlx);
	ft_draw_background(img);
	ft_draw_map_bck(img);
	ft_draw2dmap(img);
	ft_map_heading(img);
	ft_draw_fov(img);
	mlx_put_image_to_window(img->mlx, img->win2, img->img2, 0, 0);
	if (img->m_map)
		mlx_put_image_to_window(img->mlx, img->win2, img->img1,
			img->win_x - (img->win_x / img->minimap * 1.5), img->minimap / 2);
	if (img->mouse)
		ft_mouse_rot_player(img);
	return (0);
}

int	ft_key_hook(int code, t_data *data)
{
	if (code == 65307)
		the_end(data, "See you soon :-)", 0);
	if (code == 99)
		data->correct = !data->correct;
	if (code == 109)
		data->m_map = !data->m_map;
	if (code == 114)
		data->mouse = !data->mouse;
	if (code == 43)
		ft_map_zoom(data, 0);
	if (code == 35)
		ft_map_zoom(data, 1);
	if (code == 119 || code == 65362)
		ft_move_player(data, 1);
	if (code == 115 || code == 65364)
		ft_move_player(data, 2);
	if (code == 100)
		ft_move_player(data, 3);
	if (code == 97)
		ft_move_player(data, 4);
	if (code == 65361)
		ft_rotate_player(data, 0);
	if (code == 65363)
		ft_rotate_player(data, 1);
	return (code);
}

int	ft_mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 1)
		ft_cast_ray(data, x / y);
	return (0);
}

int	ft_mouse_in_hook(int x, int y, t_data *d)
{
	if (y || !y)
		d->rotmouse = (float)((int)(d->win_x / 2) - x) / (int)(d->win_x / 3);
	return (0);
}

int	ft_mouse_out_hook(t_data *img)
{
	img->rotmouse = 0;
	return (0);
}
