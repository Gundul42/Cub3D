/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 10:23:57 by graja             #+#    #+#             */
/*   Updated: 2022/01/22 17:24:53 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static	
int	ft_playerOrient(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	       return (c);
	else 
		return (0);
}

static
void	ft_writeCell(t_data *data, int x, int y, char c)
{

	data->map[y][x] = c - '0';
	if (c - '0' > 1)
		data->snbr++;
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
			c = ft_playerOrient(*line);
			if (*line != 32 && (!c || (c && plyr)))
				return (-1);
			if (c && !plyr)
			{
				ft_initialize_player(data, x, y, c);
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
