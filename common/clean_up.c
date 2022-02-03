/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 22:08:48 by flormich          #+#    #+#             */
/*   Updated: 2022/02/03 15:59:15 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

/*
 * this is only temp used for loading textures
 * can be freed after use or in case of file not found
 */
void	ft_free_tex(char **tex)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (tex[i])
			free(tex[i]);
		i++;
	}
	free(tex);
}

void	ft_destroy_sprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->sprite_max - 1)
	{
		if (data->sprite[i])
			mlx_destroy_image(data->mlx, data->sprite[i]);
		i++;
	}
}

//clean up all allocated memory for the loaded map
void	ft_cleanup_map(t_data *data)
{
	size_t	y;

	y = 0;

	while (y < data->mapy)
	{
		if (data->map && data->map[y])
			free(data->map[y]);
		if (data->doors && data->doors[y])
			free(data->doors[y]);
		if (data->dopen && data->dopen[y])
			free(data->dopen[y]);
		y++;
	}
	free(data->map);
	free(data->doors);
	free(data->dopen);
}

//to be called at program termination for cleanup.
int	the_end(t_data *data, char *txt, int err)
{
	if (err == 1)
		write(2, "Error\n", 6);
	if (txt && *txt)
		write(2, txt, ft_strlen(txt));
	if (err != 2)
	{
		if (data && data->zbuf)
			free(data->zbuf);
		if (data->slist)
			free(data->slist);
		if (data->sprite[0])
			ft_destroy_sprites(data);
		ft_cleanup_map(data);
		mlx_destroy_image(data->mlx, data->img1);
		mlx_destroy_image(data->mlx, data->img2);
		ft_destroy_textures(data);
		mlx_destroy_window(data->mlx, data->win2);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		free(data);
	}
	exit (0);
	return (1);
}
