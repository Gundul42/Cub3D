/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:00:21 by graja             #+#    #+#             */
/*   Updated: 2022/01/29 11:36:39 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"
/*
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
}*/

static
void	ft_openMap(t_data *data, char *path)
{
	int	fd;
	char	*line;
	int	skip;

	line = NULL;
	skip = 0;
	fd = ft_openFile(data, path);
	while (get_next_line(fd, &line))
	{
		if (!skip)
		{
			if (*line && (ft_isdigit(*line) || *line == 32))
				skip = 1;
		}
		if (skip)
		{
			if (data->mapx < ft_strlen(line))
				data->mapx = ft_strlen(line);
			(data->mapy)++;
		}
		free(line);
	}
	free(line);
	close(fd);
}

// Display map in the terminal
void	ft_dumpMap(t_data *data)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			printf("%d",data->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

int	ft_openFile(t_data *data, char *path)
{
	int	fd;

	if (path)
		fd = open(path, O_RDONLY);
	else
		fd = open("./maps/test.cub", O_RDONLY);
	if (fd == -1)
		ft_fileNf(data, path);
	return (fd);
}

void	ft_initMap(t_data *data, char *path)
{
	int	fd;

	fd = ft_openFile(data, path);
	ft_checkHead(data, fd, 0, 0);
	ft_readHead(data, path, 0, 0);
	ft_openMap(data, path);
	ft_map2Mem(data, path, 0, 0);
	ft_dumpMap(data);
	ft_check_closed_map(data);
}
