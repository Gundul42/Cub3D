/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:02:30 by graja             #+#    #+#             */
/*   Updated: 2022/01/14 18:15:16 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_loadTextures(t_data *data)
{
	data->txtnorth = mlx_xpm_file_to_image(data->mlx, "./textures/cobble.xpm",
			&(data->n_txtx), &(data->n_txty));
	if (!data->txtnorth)
	{
		perror("File not found");
		the_end(data);
	}
}

int	ft_getTexPixel(t_data *data, int x, int y)
{
	char	*dst;
	int	bpp;
	int	ll;
	int	endian;

	if (x < 0 || x > (int)(data->tilesize) || y < 0 || 
			y > (int)(data->tilesize))
		return (0);
	dst = mlx_get_data_addr(data->txtnorth, &bpp,
			&ll, &endian);
	dst += (y * ll + x * (bpp / 8));
	return (*(unsigned int *)dst);
}
