/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:00:21 by graja             #+#    #+#             */
/*   Updated: 2022/01/04 18:40:07 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
size_t	ft_getll(char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != 32)
			i++;
		s++;
	}
	return (i);
}

static
void	ft_readErr(t_data *data, char *path)
{
	{
		if (path)
			perror(path);
		else
			perror("./maps/test.cub");
		the_end(data);
	}
}

void	ft_openMap(t_data *data, char *path, size_t *maxx, size_t *maxy)
{
	int	fd;
	char	*line;

	line = NULL;
	if (path)
		fd = open(path, O_RDONLY);
	else
		fd = open("./maps/test.cub", O_RDONLY);
	if (fd == -1)
		ft_readErr(data, path);
	*maxy = 0;
	*maxx = 0;
	while (get_next_line(fd, &line))
	{
		if (*maxx < ft_getll(line))
			*maxx = ft_getll(line);
		(*maxy)++;
		free(line);
	}
	free(line);
	close(fd);
}
