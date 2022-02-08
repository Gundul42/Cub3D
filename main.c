/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:43:51 by graja             #+#    #+#             */
/*   Updated: 2022/02/08 16:22:12 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cube3d.h"

static void	ft_display_rules(void)
{
	printf(GR"Welcome to the CreepyCastel:\n");
	printf("- use W, A, S, D or arrow up & down to move\n");
	printf("- use arrow right & left to rotate\n");
	printf("- hit R to turn mouse move on/off\n");
	printf("- hit M to turn minimap on/off\n");
	printf("- hit + to zoom in the minimap\n");
	printf("- hit # to zoom out the minimap\n");
	printf("- hit ESC to end the program\n");
	printf(D"\n"D);
}

//alloc memory for datatype and set everything to 0
//define window size with x and y
t_data	*ft_blank(t_data *d)
{
	d = ft_calloc(1, sizeof(t_data));
	if (!d)
		exit (1);
	d->map = NULL;
	d->win_x = 800;
	d->win_y = 600;
	d->fov = 60;
	d->minimap = 8;
	d->mini_z = 16;
	d->rotspeed = 2.5;
	d->correct = 1;
	d->dtpp = ((d->win_x / 2) / (tanf(ft_deg2rad((float)(d->fov / 2)))));
	d->precision = (float)d->fov / (float)d->win_x;
	d->part = 1;
	d->sprite_max = 0;
	return (d);
}

static
void	ft_get_ready(t_data *data)
{
	data->img1 = mlx_new_image(data->mlx, data->win_x
			/ data->minimap, data->win_x / data->minimap);
	data->addr1 = mlx_get_data_addr(data->img1, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->win2 = mlx_new_window(data->mlx, data->win_x, data->win_y,
			"Cube3D");
	data->img2 = mlx_new_image(data->mlx, data->win_x, data->win_y);
	data->addr2 = mlx_get_data_addr(data->img2, &data->bits_per_pixel2,
			&data->line_length2, &data->endian2);
	data->addr = data->addr1;
}

static
void	ft_check_cub(int argc, char **argv)
{
	int		len;

	if (argc > 2)
		exit(1);
	else if (argc == 1)
		return ;
	len = ft_strlen(argv[1]);
	if (len < 5)
		exit(1);
	if (ft_strnstr(argv[1] + len - 4, ".cub", 4) == NULL)
	{
		write(2, "Error: .cub expected\n", 21);
		exit (1);
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_data	*img;

	ft_check_cub(argc, argv);
	img = ft_blank(NULL);
	img->mlx = mlx_init();
	if (!img->mlx)
		return (1);
	ft_get_ready(img);
	ft_init_map(img, argv[1]);
	ft_display_rules();
	ft_val_player_pos(img);
	ft_draw_background(img);
	mlx_hook(img->win2, 17, 1L << 2, the_end_hook, img);
	mlx_hook(img->win2, 2, 1L << 0, ft_key_hook, img);
	mlx_hook(img->win2, 6, 1L << 6, ft_mouse_in_hook, img);
	mlx_hook(img->win2, 8, 1L << 5, ft_mouse_out_hook, img);
	mlx_mouse_hook(img->win2, ft_mouse_hook, img);
	mlx_loop_hook(img->mlx, ft_loop_hook, img);
	mlx_loop(img->mlx);
	return (0);
}
