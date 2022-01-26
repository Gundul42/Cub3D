/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:02:30 by graja             #+#    #+#             */
/*   Updated: 2022/01/26 10:02:57 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_texAutodetect(t_data *data, unsigned int x, unsigned int y)
{
	printf("\n\nTexture size: %dpxs\n", x);
	if (x != y || x < 64 || y < 64 || x > 1024 || y > 1024)
	{
		write(2, "Allowed texture range from 64 - 1024px\n", 39);
		write(2, "asymmetric textures not allowed.\n", 33); 
		return ;
	}
	data->tilesize = x;
	data->speed = data->tilesize / 10;
}

void	ft_destroy_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->txt[i])
			mlx_destroy_image(data->mlx, data->txt[i]);
		i++;
	}
}

//modif flo lg 42 path[i] instead of path[0] to avoid seg fault if 1st texture NOK
void	ft_loadTextures(t_data *data, char **path)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	while (i < 4)
	{
		data->txt[i] = mlx_xpm_file_to_image(data->mlx,
				path[i], &x, &y);
		if (!data->txt[i])
		{
			if (path && path[i] != NULL)
			{
				write(2, path[i], ft_strlen(path[i]));
				write(2, "\n", 1);
				ft_freeTex(path);
			}
			the_end(data, "Fix the textures files and run the program again\n", 1);
		}
		if (!data->tilesize)
			ft_texAutodetect(data, x, y);
		if ((unsigned int)x != data->tilesize || (unsigned int)y != data->tilesize)
		{
			write(2, "Wrong texture bitmap size ", 26);
			ft_putnbr_fd(x, 2);
			write(2, "px found, ", 10);
			ft_putnbr_fd(data->tilesize, 2);
			write(2, "px needed.\n", 11);
			ft_freeTex(path);
			the_end(data, "Fix the problem and run the program again\n", 1);
		}
		i++;
	}
}

int	ft_getTexPixel(t_data *data, int x, int y, int n)
{
	char	*dst;
	int	bpp;
	int	ll;
	int	endian;

	if (x < 0 || x > (int)(data->tilesize) || y < 0 ||
			y > (int)(data->tilesize))
		return (0);
	dst = mlx_get_data_addr(data->txt[n], &bpp,
			&ll, &endian);
	dst += (y * ll + x * (bpp / 8));
	return (*(unsigned int *)dst);
}
