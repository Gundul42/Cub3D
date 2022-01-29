/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadsprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:47:37 by graja             #+#    #+#             */
/*   Updated: 2022/01/29 14:00:00 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_drawSpritePixel(t_data *data, int x, int y)
{
	char	*dst;
	int	bpp;
	int	ll;
	int	i;
	int	j;


	dst = mlx_get_data_addr(data->sprite, &bpp,
			&ll, &i);
	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			if (*(unsigned int *)(dst + (i * ll + j * (bpp / 8))))
				ft_draw_pixel(data, x + j, y + i, *(unsigned int *)
					(dst + (i * ll + j * (bpp / 8))));
			j++;
		}
		i++;
	}
}

void	ft_destroy_sprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->sprite)
			mlx_destroy_image(data->mlx, data->sprite);
		i++;
	}
}

void	ft_loadSprites(t_data *data)
{
	int	x;
	int	y;
	char	*path;

	path = ft_strdup("./sprites/256gate.xpm");
	data->sprite = mlx_xpm_file_to_image(data->mlx, path, &x, &y);
	if (!data->sprite)
	{
		write(2, "Sprite texture file not found: ", 31);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		free(path);
		the_end(data, "Fix the problem and run the program again\n", 1);
	}
	if ((unsigned int)x != data->tilesize)
	{
		write(2, "Wrong sprite texture size ", 26);
		ft_putnbr_fd(x, 2);
		write(2, "px in file, ",12);
		ft_putnbr_fd(data->tilesize, 2);
		write(2, "px needed\n", 10);
		free(path);
		the_end(data, "Fix the problem and run the program again\n", 1);
	}
	free(path);
}
