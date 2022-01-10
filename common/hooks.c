/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:44:07 by graja             #+#    #+#             */
/*   Updated: 2022/01/10 13:59:41 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

int	ft_loop_hook(t_data *img)
{
	mlx_do_sync(img->mlx); //documentation says this is auto sync of frames -- tests needed 
	ft_draw_background(img);
	ft_draw2dmap(img);
	if (img->run)
	{
		ft_drawFov(img);
		ft_showPlayer(img);
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (0);
}

int	ft_key_hook(int code, t_data *data)
{
	//printf("Key: %d)\n", code);
	if (code == 65307)
		the_end(data);
	if (code == 119)
		ft_movePlayer(data, 1);		// W
	if (code == 115)
		ft_movePlayer(data, 2);		// S
	if (code == 100)
		ft_movePlayer(data, 3);		// A
	if (code == 97)
		ft_movePlayer(data, 4);		// D
	if (code == 65361)
		ft_rotatePlayer(data, 0);	// cursor right
	if (code == 65363)
		ft_rotatePlayer(data, 1);	// cursor left
	return (code);
}

int	ft_mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 1)
		ft_castRay(data, x/ y);
	return (0);
}
