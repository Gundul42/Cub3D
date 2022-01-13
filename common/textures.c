/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:02:30 by graja             #+#    #+#             */
/*   Updated: 2022/01/13 18:47:55 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_loadTextures(t_data *data)
{
	data->txtnorth = mlx_xpm_file_to_image(data->mlx, "./textures/brick.xpm",
			&(data->n_txtx), &(data->n_txty));
	if (!data->txtnorth)
	{
		perror("File not found");
		the_end(data);
	}
}
