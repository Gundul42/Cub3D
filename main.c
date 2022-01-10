/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:43:51 by graja             #+#    #+#             */
/*   Updated: 2022/01/10 17:54:06 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cube3d.h"

//./cub3d ./maps/test.cub


//clean up all allocated memory for the loaded map
static
void	ft_cleanupMap(t_data *data)
{
	size_t	y;

	y = 0;

	printf("%ld - %ld\n", data->mapx, data->mapy);
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
	if (data->mapx)
		ft_cleanupMap(data);
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
	data->win_x = 1200;
	data->win_y = 800;
	data->tilesize = 64;
	data->fov = 90;
	data->speed = 16;
	data->rotspeed = 1.5;
	data->precision = 0.05;		// ray scan precision smaller slower but more accurate
	data->cfloor_far = ft_rgb2col(0, 252, 193, 255);
	data->cfloor_near = ft_rgb2col(0, 132, 43, 135);
	data->csky = ft_make_trgb(0, 135, 206, 235);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*img;

	if (argc == 1)
		fehlt_map(NULL, NULL, 0);
	img = ft_blank(NULL);
	img->mlx = mlx_init();
	if (!img->mlx)
		return (1);
	img->win = mlx_new_window(img->mlx, img->win_x, img->win_y,
			"Cube3D");
	img->img = mlx_new_image(img->mlx, img->win_x, img->win_y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	ft_initMap(img, argv[1]);
	img->dir = 283.0;
	ft_draw_background(img);
	ft_draw2dmap(img);
	mlx_hook(img->win, 17, 1L << 2, the_end, img);
	mlx_hook(img->win, 2, 1L << 0, ft_key_hook, img);
//	mlx_key_hook(img->win, ft_key_hook, img);
	mlx_mouse_hook(img->win, ft_mouse_hook, img);
	mlx_loop_hook(img->mlx, ft_loop_hook, img);
	mlx_loop(img->mlx);
	return (0);
}
