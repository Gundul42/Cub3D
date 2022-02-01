/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:13:55 by graja             #+#    #+#             */
/*   Updated: 2022/02/01 19:06:01 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

//clean up all allocated memory for the loaded map
static
void	ft_cleanupMap(t_data *data)
{
	size_t	y;

	y = 0;

	while (y < data->mapy)
	{
		if (data->map && data->map[y])
			free(data->map[y]);
		if (data->doors && data->doors[y])
			free(data->doors[y]);
		if (data->dopen && data->dopen[y])
			free(data->dopen[y]);
		y++;
	}
	free(data->map);
	free(data->doors);
	free(data->dopen);
}

//to be called at program termination for cleanup.
int	the_end(t_data *data, char *txt, int err)
{
	if (err == 1)
		write(2, "Error\n", 6);
	if (txt && *txt)
		write(2, txt, ft_strlen(txt));
	if (err != 2)
	{
		if (data && data->zbuf)
			free(data->zbuf);
		if (data->slist)
			free(data->slist);
		if (data->sprite[0])
			ft_destroy_sprites(data);
		ft_cleanupMap(data);
		mlx_destroy_image(data->mlx, data->img1);
		mlx_destroy_image(data->mlx, data->img2);
		ft_destroy_textures(data);
		mlx_destroy_window(data->mlx, data->win2);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		free(data);
	}
	exit (0);
	return (1);
}

//alloc memory for datatype and set everything to 0
//define window size with x and y
t_data	*ft_blank(t_data *data)
{
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit (1);
	data->map = NULL;
	data->win_x = 800;
	data->win_y = 600;
	data->fov = 60;
	data->minimap = 8;
	data->miniZ = 16;
	data->rotspeed = 2.5;
	data->correct = 1;
	data->dtpp = ((data->win_x / 2) / (tanf(ft_deg2rad((float)(data->fov / 2)))));
	data->precision = (float)data->fov / (float)data->win_x;
	data->part = 2;
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
	data->zbuf = ft_calloc(data->win_x, sizeof(float));
	if (!data->zbuf)
		the_end(data, "Out of Memory\n", 1);
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
	ft_initSprites(img);
	ft_draw_background(img);
	mlx_hook(img->win2, 17, 1L << 2, the_end_hook, img);
	mlx_hook(img->win2, 2, 1L << 0, ft_key_hook_bonus, img);
	mlx_hook(img->win2, 6, 1L << 6, ft_mouse_in_hook, img);
	mlx_hook(img->win2, 8, 1L << 5, ft_mouse_out_hook, img);
	mlx_mouse_hook(img->win2, ft_mouse_hook, img);
	mlx_loop_hook(img->mlx, ft_sprite_hook, img);
	mlx_loop(img->mlx);
	return (0);
}

