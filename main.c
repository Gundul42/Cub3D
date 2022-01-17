/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:43:51 by graja             #+#    #+#             */
/*   Updated: 2022/01/17 12:44:40 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cube3d.h"

//clean up all allocated memory for the loaded map
static
void	ft_cleanupMap(t_data *data)
{
	size_t	y;

	y = 0;

	while (y < data->mapy)
	{
		free(data->map[y]);
		y++;
	}
	free(data->map);
}

//to be called at program termination for cleanup.
int	the_end(t_data *data)
{
	if (data->map)
		ft_cleanupMap(data);
	mlx_destroy_image(data->mlx, data->img1);
	mlx_destroy_image(data->mlx, data->img2);
	ft_destroy_textures(data);
	mlx_destroy_window(data->mlx, data->win2);
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
	data->tilesize = 64;
	data->map = NULL;
	data->win_x = 800;
	data->win_y = 600;
	data->fov = 60;
	data->speed = 8;
	data->minimap = 8;
	data->miniZ = 16;
	data->rotspeed = 2.5;
	data->correct = 1;
	data->dtpp = ((data->win_x / 2) / (tanf(ft_deg2rad((float)(data->fov / 2)))));
	data->precision = (float)data->fov / (float)data->win_x;
//	data->cfloor_near = ft_rgb2col(0, 102, 0, 0);
//	data->csky = ft_make_trgb(0, 135, 206, 235);
	return (data);
}

static
void	ft_getReady(t_data *data)
{
	data->img1 = mlx_new_image(data->mlx, data->win_x / 
			data->minimap, data->win_x / data->minimap);
	data->addr1 = mlx_get_data_addr(data->img1, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->win2 = mlx_new_window(data->mlx, data->win_x, data->win_y,
			"Cube3D");
	data->img2 = mlx_new_image(data->mlx, data->win_x, data->win_y);
	data->addr2 = mlx_get_data_addr(data->img2, &data->bits_per_pixel2,
			&data->line_length2, &data->endian2);
	data->addr = data->addr1;
}

int	main(int argc, char **argv)
{
	t_data	*img;

	img = ft_blank(NULL);
	img->mlx = mlx_init();
	if (!img->mlx || argc > 2)
		return (1);
	ft_getReady(img);
	ft_initMap(img, argv[1]);
	ft_loadSprites(img);
	ft_draw_background(img);
	mlx_hook(img->win2, 17, 1L << 2, the_end, img);
	mlx_hook(img->win2, 2, 1L << 0, ft_key_hook, img);
	mlx_hook(img->win2, 6, 1L << 6, ft_test_hook, img);
	mlx_mouse_hook(img->win2, ft_mouse_hook, img);
	mlx_loop_hook(img->mlx, ft_loop_hook, img);
	mlx_loop(img->mlx);
	return (0);
}
