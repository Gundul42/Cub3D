/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:02:30 by graja             #+#    #+#             */
/*   Updated: 2022/02/02 21:53:17 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_text_auto_detect(t_data *d, unsigned int x, unsigned int y)
{
	printf("\n\nTexture size: %dpxs\n", x);
	if (x != y || x < 64 || y < 64 || x > 1024 || y > 1024)
	{
		write(2, "Allowed texture range from 64 - 1024px\n", 39);
		write(2, "asymmetric textures not allowed.\n", 33);
		return ;
	}
	d->tilesize = x;
	d->speed = d->tilesize / 10;
}

void	ft_destroy_textures(t_data *d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (d->txt[i])
			mlx_destroy_image(d->mlx, d->txt[i]);
		i++;
	}
}

void	ft_load_textures(t_data *d, char **path, int i)
{
	int	x;
	int	y;

	while (i < 4)
	{
		d->txt[i] = mlx_xpm_file_to_image(d->mlx,
				path[i], &x, &y);
		if (!d->txt[i])
		{
			if (path && path[i] != NULL)
			{
				write(2, path[i], ft_strlen(path[i]));
				ft_free_tex(path);
			}
			the_end(d, "Fix the textures files and run the program again\n", 1);
		}
		if (!d->tilesize)
			ft_text_auto_detect(d, x, y);
		if ((unsigned int)x != d->tilesize || (unsigned int)y != d->tilesize)
		{
			ft_free_tex(path);
			the_end(d, "Wrong texture pixel size\n", 1);
		}
		i++;
	}
}

int	ft_get_tex_pixel(t_data *d, int x, int y, int n)
{
	char	*dst;
	int		bpp;
	int		ll;
	int		endian;

	if (x < 0 || x > (int)(d->tilesize) || y < 0 ||
			y > (int)(d->tilesize))
		return (0);
	dst = mlx_get_data_addr(d->txt[n], &bpp,
			&ll, &endian);
	dst += (y * ll + x * (bpp / 8));
	return (*(unsigned int *)dst);
}
