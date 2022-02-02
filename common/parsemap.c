/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 10:23:57 by graja             #+#    #+#             */
/*   Updated: 2022/02/02 13:06:53 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
int	ft_playerOrient(t_data *d, char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (c);
	else if (ft_isalpha(c) == 1)
		the_end(d,"Player must be W, E, S or N.\n", 1);
	return (0);
}

static
void	ft_writeCell(t_data *data, int x, int y, char c)
{

	if (ft_isalpha(c) == 1)
		data->map[y][x] = -1;
	else
	{
		data->map[y][x] = c - '0';
		if (c - '0' > 1 && c - '0' < 5)
			data->snbr++;
		if (c - '0' > data->sprite_max + 1)
			the_end(data, "Unexpected number on the map - check sprite_max\n", 1);
	}
}

static
int	ft_readline(t_data *data, char *line, int y, int plyr)
{
	int	x;
	int	c;

	x = 0;
	while (*line)
	{
		if (!ft_isdigit(*line))
		{
			c = ft_playerOrient(data, *line);
			if (*line != 32 && (!c || (c && plyr)))
				return (-1);
			if (c && !plyr)
			{
				ft_initialize_player(data, x, y, c);
				ft_writeCell(data, x, y, *line);
				plyr = 1;
			}
		}
		else
			ft_writeCell(data, x, y, *line);
		x++;
		line++;
	}
	return (plyr);
}

int	ft_parseMapLine(t_data *data, char *line)
{
	static int	y = 0;
	static int	plyr = 0;

	if (!*line || ft_strlen(line) < 3 || ft_isalpha(*line))
		return (-1);
	data->map[y] = ft_calloc(data->mapx, sizeof(int));
	if (!data->map[y])
		return (-1);
	plyr = ft_readline(data, line, y, plyr);
	y++;
	if (plyr < 0)
		return (-1);
	return (1);
}
