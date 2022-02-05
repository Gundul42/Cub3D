/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:00:21 by graja             #+#    #+#             */
/*   Updated: 2022/02/05 19:26:28 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
void	ft_initdoors(t_data *data)
{
	size_t	y;

	data->doors = ft_calloc(data->mapy, sizeof(int *));
	data->dopen = ft_calloc(data->mapy, sizeof(int *));
	if (!data->doors || !data->dopen)
		the_end(data, "Out of memory !\n", 1);
	y = 0;
	while (y < data->mapy)
	{
		data->doors[y] = ft_calloc(data->mapx, sizeof(int));
		data->dopen[y] = ft_calloc(data->mapx, sizeof(int));
		if (!data->doors[y] || !data->dopen[y])
			the_end(data, "Out of memory !\n", 1);
		y++;
	}
}

static
void	ft_open_map(t_data *data, char *path, int i)
{
	int		fd;
	char	*line;
	int		skip;

	line = NULL;
	skip = 0;
	fd = ft_open_file(data, path);
	while (get_next_line(fd, &line))
	{
		if (!skip && (*line || *line == 32))
		{
			i = ft_skip_space(line);
			if (ft_isdigit(line[i]) == 1)
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
void	ft_dump_map(t_data *data)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < data->mapy)
	{
		x = 0;
		while (x < data->mapx)
		{
			if (data->map[y][x] == -1)
				printf(RED"@"D);
			else if (data->map[y][x] == 0)
				printf(BLACK"%d"D, data->map[y][x]);
			else if (data->map[y][x] != 1)
				printf(YE"%d"D, data->map[y][x]);
			else
				printf("%d", data->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

int	ft_open_file(t_data *data, char *path)
{
	int	fd;

	if (path)
		fd = open(path, O_RDONLY);
	else if (data->part == 1)
		fd = open("./maps/mandatory.cub", O_RDONLY);
	else if (data->part == 2)
		fd = open("./maps/bonus.cub", O_RDONLY);
	else
		fd = -1;
	if (fd == -1)
		ft_file_nf(data, path);
	return (fd);
}

void	ft_init_map(t_data *data, char *path)
{
	int	fd;

	fd = ft_open_file(data, path);
	ft_check_head(data, fd, 0, 0);
	ft_read_head(data, path, 0, 0);
	ft_open_map(data, path, 0);
	ft_map2_mem(data, path, 0, 0);
	ft_dump_map(data);
	ft_initdoors(data);
	ft_check_closed_map(data);
}
