/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:02:30 by graja             #+#    #+#             */
/*   Updated: 2022/01/15 09:53:47 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_texDefault(t_data *data)
{
	char	**path;
	int		i;

	i = 0;
	path = malloc(sizeof(char *) * 4);
	while (i < 4)
	{
		path[i] = ft_calloc(255, sizeof(char));
		i++;
	}
	path[0] = "./textures/cobble.xpm";
	path[1] = "./textures/stone_macadam.xpm";
	path[2] = "./textures/mossycobble.xpm";
	path[3] = "./textures/stone_brick.xpm";
	ft_loadTextures(data, path);
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
			write(2, "ERROR: Texture file not found: ",31);
			write(2, path[i], ft_strlen(path[i]));
			write(2, "\n", 1);
			the_end(data);
		}
		if (x != data->tilesize || y != data->tilesize)
		{
			write(2, "ERROR: Wrong texture bitmap size ", 33);
			ft_putnbr_fd(data->tilesize, 2);
			write(2, "px only\n", 8);
			the_end(data);
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
