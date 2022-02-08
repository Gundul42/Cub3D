/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:13:55 by graja             #+#    #+#             */
/*   Updated: 2022/02/08 15:39:13 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

static
void	ft_display_rules(void)
{
	printf(GR"Welcome to the CreepyCastel:\n");
	printf("- use W, A, S, D or arrow up & down to move\n");
	printf("- use arrow right & left to rotate\n");
	printf("- hit R to turn mouse move on/off\n");
	printf("- hit M to turn minimap on/off\n");
	printf("- hit + to zoom in the minimap\n");
	printf("- hit # to zoom out the minimap\n");
	printf("- hit SPACE to open a door\n");
	printf("- hit ESC to end the program\n");
	printf(D"\n"D);
}

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
	data->mini_z = 16;
	data->rotspeed = 2.5;
	data->correct = 1;
	data->dtpp = ((data->win_x / 2) / (tanf(ft_deg2rad((float)
						(data->fov / 2)))));
	data->precision = (float)data->fov / (float)data->win_x;
	data->part = 2;
	data->sprite_max = 7;
	data->over_sprite = 0;
	return (data);
}

static
void	ft_get_ready(t_data *data)
{
	data->img1 = mlx_new_image(data->mlx, data->win_x / data->minimap,
			data->win_x / data->minimap);
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
		exit(1);
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
	ft_load_sprites(img);
	ft_init_sprites(img);
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
