/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:09:49 by flormich          #+#    #+#             */
/*   Updated: 2022/01/05 19:48:26 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cube3d.h"

// 1 = no map, 2 = wrong path
void	fehlt_map(t_data *data, char *path, int type)
{
	if (!path && type == 0)
	{
		write(1, "To load your own map, restart with the path to .cub map\n", 57);
		write(1, "=> For example: ./cub3d ./maps/test.cub\n\n", 43);
	}
	else if (type == 1)
	{
		write(1, path, ft_strlen(path));
		write(1, " is not a valid map.\n\n", 23);
		the_end (data);
	}
	else if (type == 2)
	{
		write(1, "Default map is not valid\n\n", 27);
		the_end (data);
	}
}
