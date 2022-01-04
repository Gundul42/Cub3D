/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:43:51 by graja             #+#    #+#             */
/*   Updated: 2022/01/04 22:22:02 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cube3d.h"

//to be called at program termination for cleanup.
int	the_end(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	exit (0);
	return (0);
}

//alloc memory for datatype and set everything to 0
//define window size with x and y
t_data	*ft_blank(t_data *data)
{
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit (1);
	data->x = 1200;
	data->y = 800;
	data->tilesize = 64;
	data->fov = 120;
	data->speed = 32;
	data->dir = 0.0;
	data->px = 5.0 * 64.0;
	data->py = 5.0 * 64.0;
	data->cfloor_far = ft_rgb2col(0, 76, 0, 0);
	data->cfloor_near = ft_rgb2col(0, 128, 128, 128);
	data->csky = ft_make_trgb(0, 135, 206, 235);
	return (data);
}

int	main(void)
{
	t_data	*img;

	img = ft_blank(NULL);
	img->mlx = mlx_init();
	if (!img->mlx)
		return (1);
	img->win = mlx_new_window(img->mlx, img->x, img->y,
			"Cube3D");
	img->img = mlx_new_image(img->mlx, img->x, img->y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	ft_initMap(img, NULL);
	ft_draw_background(img);
	mlx_hook(img->win, 17, 1L << 2, the_end, img);
	mlx_key_hook(img->win, ft_key_hook, img);
	mlx_mouse_hook(img->win, ft_mouse_hook, img);
	mlx_loop_hook(img->mlx, ft_loop_hook, img);
	mlx_loop(img->mlx);
	return (0);
}
