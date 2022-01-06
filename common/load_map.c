/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:00:21 by graja             #+#    #+#             */
/*   Updated: 2022/01/06 18:54:11 by graja            ###   ########.fr       */
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

static
void	ft_dumpMap(t_data *data)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	while (b < data->mapy)
	{
		a = 0;
		while (a < data->mapx)
		{
			printf("%d ",data->map[b][a]);
			a++;
		}
		printf("\n");
		b++;
	}
}

void	ft_initMap(t_data *data, char *path)
{
	size_t	i;
	size_t	j;
	int	fd;
	char	*line;
	char	*bck;

	line = NULL;
	ft_openMap(data, path);
	if (data->mapx < 3 || data->mapy < 3)
		the_end(data);
	fd = ft_openFile(data, path);
	data->map = ft_calloc(data->mapy, sizeof(int *));
	j = 0;
	while (get_next_line(fd, &line))
	{
		i = 0;
		bck = line;
		data->map[j] = ft_calloc(data->mapx, sizeof(int));
		while (*bck)
		{
			if (ft_isdigit(*bck) == 1)
				data->map[j][i] = *bck - 48;
			if (*bck != 32)
				i++;
			bck++;
		}
		j++;
		free(line);
	}
	free(line);
	close(fd);
	ft_dumpMap(data);
}
