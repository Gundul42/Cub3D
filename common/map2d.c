/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:42:31 by flormich          #+#    #+#             */
/*   Updated: 2022/02/08 15:17:46 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

int	ft_skip_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] == 32)
		i++;
	return (i);
}

void	ft_map2_mem(t_data *data, char *path, int fd, int skip)
{
	char	*line;
	int		i;

	skip = 0;
	line = NULL;
	fd = ft_open_file(data, path);
	data->map = ft_calloc(data->mapy, sizeof(int *));
	if (!data->map)
		the_end(data, "Couldn't malloc map array\n", 1);
	while (get_next_line(fd, &line))
	{
		if (!skip && (*line || *line == 32))
		{
			i = ft_skip_space(line);
			if (ft_isdigit(line[i]) == 1)
				skip = 1;
		}
		if (skip > 0)
			skip = ft_parse_map_line(data, line);
		free(line);
	}
	free(line);
	close(fd);
	if (skip < 0 || data->px == 0 || data->py == 0 || data->over_sprite == 1)
		the_end(data, "Map NOK\n", 1);
}

int	ft_check_map_ns(t_data *d, t_point p, float alpha)
{
	size_t	x;
	size_t	y;

	if (p.x >= d->mapx * d->tilesize || p.y >= d->mapy * d->tilesize)
		return (0);
	if (p.x < 0.0 || p.y < 0.0)
		return (0);
	ft_get_map_point(d, p, &x, &y);
	if (alpha >= 270 || alpha < 90)
		return (ft_is_wall(d, x, y) - 1);
	else if (alpha < 270 && alpha >= 90)
		return (ft_is_wall(d, x - 1, y) - 1);
	return (0);
}

int	ft_check_map_we(t_data *d, t_point p, float alpha)
{
	size_t	x;
	size_t	y;

	if (p.x >= d->mapx * d->tilesize || p.y >= d->mapy * d->tilesize)
		return (0);
	if (p.x < 0.0 || p.y < 0.0)
		return (0);
	ft_get_map_point(d, p, &x, &y);
	if (alpha >= 180 && alpha < 360)
		return (ft_is_wall(d, x, y - 1) - 1);
	else if (alpha < 180 && alpha >= 0)
		return (ft_is_wall(d, x, y) - 1);
	return (0);
}
