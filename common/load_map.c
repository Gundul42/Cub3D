/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:00:21 by graja             #+#    #+#             */
/*   Updated: 2022/01/04 22:44:42 by graja            ###   ########.fr       */
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
			perror(path);
		else
			perror("./maps/test.cub");
		the_end(data);
	}
	return (fd);
}

static
void	ft_openMap(t_data *data, char *path, size_t *maxx, size_t *maxy)
{
	int	fd;
	char	*line;

	line = NULL;
	fd = ft_openFile(data, path);
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

static
void	ft_dumpMap(t_data *data, size_t x, size_t y)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	while (b < y)
	{
		a = 0;
		while (a < x)
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
	size_t	x;
	size_t	y;
	size_t	i;
	size_t	j;
	int	fd;
	char	*line;
	char	*bck;

	line = NULL;
	ft_openMap(data, path, &x, &y);
	if (x < 3 || y < 3)
		the_end(data);
	fd = ft_openFile(data, path);
	data->map = ft_calloc(y, sizeof(int *));
	j = 0;
	while (j < y)
	{
		i = 0;
		data->map[j] = ft_calloc(x, sizeof(int));
		get_next_line(fd, &line);
		bck = line;
		while (*bck)
		{
			if (*bck == '1')
				data->map[j][i] = 1;
			if (*bck != 32)
				i++;
			bck++;
		}
		j++;
		free(line);
	}
	ft_dumpMap(data, x, y);
}
