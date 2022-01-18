/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 13:49:55 by graja             #+#    #+#             */
/*   Updated: 2022/01/18 12:56:32 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

/*
 * File Not Found
 */
void	ft_fileNf(t_data *data, char *path)
{
	if (path)
		write (2, path, ft_strlen(path));
	write (2, " not found.\n", 12);
	the_end(data, "Path not found (ft_file_nf)\n", 1);
}

