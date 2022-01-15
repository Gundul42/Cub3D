/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:47:37 by graja             #+#    #+#             */
/*   Updated: 2022/01/15 13:15:05 by graja            ###   ########.fr       */
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

	path = "./textures/ferns_fern.xpm";
	data->sprite = mlx_xpm_file_to_image(data->mlx, 
			path, &x, &y);
	if (!data->sprite)
	{
		write(2, "ERROR: Texture file not found: ",31);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		the_end(data);
	}
	if (x != data->tilesize)
	{
		write(2, "ERROR: Wrong texture bitmap size ", 33);
		ft_putnbr_fd(data->tilesize, 2);
		write(2, "px in x direction only\n", 8);
		the_end(data);
	}
}
