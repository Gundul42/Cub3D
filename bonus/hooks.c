/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:16:10 by graja             #+#    #+#             */
/*   Updated: 2022/01/18 15:35:16 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

int	ft_sprite_hook(t_data *img)
{
	mlx_do_sync(img->mlx);
	ft_draw_background(img);
	ft_draw2dmap(img);
	if (img->run)
		ft_drawSpriteFov(img);
	mlx_put_image_to_window(img->mlx, img->win2, img->img2, 0, 0);
	if (img->mMap)
		mlx_put_image_to_window(img->mlx, img->win2, img->img1, 
			img->win_x - (img->win_x / img->minimap * 1.5), img->minimap / 2);
	if (img->mouse)
		ft_mouseRotPlayer(img);
	return (0);
}

