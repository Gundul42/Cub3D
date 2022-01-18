/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:19:13 by graja             #+#    #+#             */
/*   Updated: 2022/01/18 13:52:16 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_map2Mem(t_data *data, char *path, int fd, int skip)
{
	char	*line;

	line = NULL;
	fd = ft_openFile(data, path);
	data->map = ft_calloc(data->mapy, sizeof(int *));
	if (!data->map)
		the_end(data, "Couldn't malloc map array\n", 1);
	while (get_next_line(fd, &line))
	{
		if (!skip)
		{
			if (*line && (ft_isdigit(*line) || *line == 32))
				skip = 1;
		}
		if (skip > 0)
				skip = ft_parseMapLine(data, line);
		free(line);
	}
	free(line);
	close(fd);
	if (skip < 0 || data->px == 0 || data->py == 0)
		the_end(data, "Map NOK\n", 1);
}

int	ft_checkMapNS(t_data *data, t_point p, float alpha)
{
	size_t	x;
	size_t	y;

	if (p.x >= data->mapx * data->tilesize || p.y >= data->mapy * data->tilesize)
		return (0);
	ft_getMapPoint(data, p, &x, &y);
	if (alpha >= 270 || alpha < 90)
	{
		if (ft_isWall(data, x, y))
			return (0);
		else
			return (1);
	}
	else if (alpha < 270 && alpha >= 90)
	{
		if (ft_isWall(data, x - 1, y))
			return (0);
		else
			return (1);
	}
	return (0);
}

int	ft_checkMapWE(t_data *data, t_point p, float alpha)
{
	size_t	x;
	size_t	y;

	if (p.x  >= data->mapx * data->tilesize || p.y >= data->mapy * data->tilesize)
		return (0);
	ft_getMapPoint(data, p, &x, &y);
	if (alpha >= 180 && alpha < 360)
	{
		if (ft_isWall(data, x, y - 1))
			return (0);
		else
			return (1);
	}
	else if (alpha < 180 && alpha >= 0)
	{
		if (ft_isWall(data, x, y))
			return (0);
		else
			return (1);
	}
	return (0);
}
