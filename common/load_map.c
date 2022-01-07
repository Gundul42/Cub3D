/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:00:21 by graja             #+#    #+#             */
/*   Updated: 2022/01/07 10:38:24 by graja            ###   ########.fr       */
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
int	ft_openFile(t_data *data, char *path)
{
	int	fd;

	if (path)
		fd = open(path, O_RDONLY);
	else
		fd = open("./maps/test.cub", O_RDONLY);
	if (fd == -1)
	{
		if (path)
			fehlt_map(data, path, 1);
		else
			fehlt_map(data, path, 2);
	}
	return (fd);
}

static
void	ft_openMap(t_data *data, char *path)
{
	int	fd;
	char	*line;

	line = NULL;
	fd = ft_openFile(data, path);
	while (get_next_line(fd, &line))
	{
		if (data->mapx < ft_getll(line))
			data->mapx = ft_getll(line);
		(data->mapy)++;
		free(line);
	}
	free(line);
	close(fd);
}

// Display map in the terminal
static
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
			printf("%d ",data->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	ft_initMap(t_data *data, char *path)
{
	size_t	x;
	size_t	y;
	int	fd;
	char	*line;
	char	*bck;

	line = NULL;
	ft_openMap(data, path);
	if (data->mapx < 3 || data->mapy < 3)
		the_end(data);
	fd = ft_openFile(data, path);
	data->map = ft_calloc(data->mapy, sizeof(int *));
	y = 0;
	while (get_next_line(fd, &line))
	{
		x = 0;
		bck = line;
		data->map[y] = ft_calloc(data->mapx, sizeof(int));
		while (*bck)
		{
			if (*bck == '1')
				data->map[y][x] = 1;
			else if (*bck == 'N' || *bck == 'S' || *bck == 'E'
				|| *bck == 'W')
				ft_initialize_player(data, x, y, *bck);
			if (*bck != 32)
				x++;
			bck++;
		}
		y++;
		free(line);
	}
	free(line);
	close(fd);
	ft_dumpMap(data);
}
