/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:02:30 by graja             #+#    #+#             */
/*   Updated: 2022/01/18 13:07:50 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

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
			if (path && path[0] != NULL)
			{
				write(2, path[i], ft_strlen(path[i]));
				write(2, "\n", 1);
				ft_freeTex(path);
			}
			the_end(data, "Fix the textures files and run the program again\n", 1);
		}
		if (x != data->tilesize || y != data->tilesize)
		{
			write(2, "Wrong texture bitmap size ", 33);
			ft_putnbr_fd(data->tilesize, 2);
			write(2, " px only\n", 8);
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
