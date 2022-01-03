/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:43:51 by graja             #+#    #+#             */
/*   Updated: 2022/01/03 14:01:47 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cube3d.h"

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

t_data	*ft_blank(t_data *data)
{
	data = malloc(sizeof(t_data));
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
	data->type = 0;
	data->x = 600;
	data->y = 400;
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
	mlx_hook(img->win, 17, 1L << 2, the_end, img);
	mlx_loop(img->mlx);
	return (0);
}
