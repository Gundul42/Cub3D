/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 13:49:55 by graja             #+#    #+#             */
/*   Updated: 2022/01/18 12:18:10 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

/*
 * File Not Found
 */
void	ft_fileNf(t_data *data, char *path)
{
	if (!path)
		path = "./maps/test.cub";
	write (2, "ERROR: ", 7);
	write (2, path, ft_strlen(path));
	write (2, " not found.\n", 12);
	the_end(data);
}
