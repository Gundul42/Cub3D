/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:44:07 by graja             #+#    #+#             */
/*   Updated: 2022/01/21 14:08:53 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

int	ft_loop_hook(t_data *img)
{
	mlx_do_sync(img->mlx); //documentation says this is auto sync of frames -- tests needed
	ft_draw_background(img);
	ft_draw2dmap(img);
	if (img->run)
		ft_drawFov(img);
	mlx_put_image_to_window(img->mlx, img->win2, img->img2, 0, 0);
	if (img->mMap)
		mlx_put_image_to_window(img->mlx, img->win2, img->img1,
			img->win_x - (img->win_x / img->minimap * 1.5), img->minimap / 2);
	ft_mouseRotPlayer(img);
	return (0);
}

int	ft_key_hook(int code, t_data *data)
{
	printf("Key: %d)\n", code);
	if (code == 65307)
		the_end(data, NULL, 0);
	if (code == 99)
		data->correct = !data->correct;
	if (code == 109)
		data->mMap = !data->mMap;
	if (code == 43)
		ft_MapZoom(data, 1);
	if (code == 35)
		ft_MapZoom(data, 0);
	if (code == 119 || code == 65362)
		ft_movePlayer(data, 1);		// W
	if (code == 115 || code == 65364)
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

int	ft_test_hook(int x, int y, t_data *img)
{
	if (x > 20 && x < (int)img->mapx - 20 && y > 20 && y < (int)img->mapy - 20 )
		img->rotmouse = (float) ((int)(img->win_x / 2) - x) / (int)(img->win_x / 3);
	else
		img->rotmouse = 0;
	//printf("MouseMove : %f  \n", img->rotmouse);
	return (0);
}
