/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadsprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:47:37 by graja             #+#    #+#             */
/*   Updated: 2022/02/05 17:57:51 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_draw_sprite_pixel(t_data *data, int x, int y)
{
	char	*dst;
	int		bpp;
	int		ll;
	int		i;
	int		j;

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

static
void	ft_load_sprite(t_data *data, char *path, int i)
{
	int	x;
	int	y;

	data->sprite[i] = mlx_xpm_file_to_image(data->mlx, path, &x, &y);
	if (!data->sprite[i])
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
		write(2, "px in file, ", 12);
		ft_putnbr_fd(data->tilesize, 2);
		write(2, "px needed\n", 10);
		free(path);
		the_end(data, "Fix the problem and run the program again\n", 0);
	}
	free(path);
}

void	ft_load_sprites(t_data *data)
{
	char	*path1;
	char	*path2;
	char	*path3;
	char	*path4;

	path1 = ft_strdup("./sprites/256fern.xpm");
	path2 = ft_strdup("./sprites/256mushroom.xpm");
	path3 = ft_strdup("./sprites/256gate.xpm");
	path4 = ft_strdup("./sprites/256torch.xpm");
	ft_load_sprite(data, path1, 0);
	ft_load_sprite(data, path2, 1);
	ft_load_sprite(data, path3, 2);
	ft_load_sprite(data, path4, 3);
	path2 = ft_strdup("./sprites/256freddy.xpm");
	path1 = ft_strdup("./sprites/256monk.xpm");
	ft_load_sprite(data, path1, 4);
	ft_load_sprite(data, path2, 5);
}
