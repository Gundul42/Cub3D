/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:18:25 by graja             #+#    #+#             */
/*   Updated: 2022/01/16 14:36:30 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
int	ft_isAllowed(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	       return (1);
	else if (c == 'F' || c == 'C')
		return (1);
	return (0);
}

static
void	ft_noHead(t_data *data)
{
	write(2, "Invalid head of .cub map file\n", 30);
	the_end(data);
}

static
int	ft_doChecks(char *alpha, char *line)
{
	char	*bck;

	bck = line;
	while (*bck == 32)
		bck++;
	if (*bck == '\n' || !*bck)
		return (0);
	if (ft_isdigit(*bck))
		return (-1);
	if (ft_isAllowed(*bck) && !alpha[(int)(*bck)])
	{
		alpha[(int)(*bck)] = 1;
		return (1);
	}
	else 
		return (-2);
	return (0);
}

void	ft_checkHead(t_data *data, int fd)
{
	char	*line;
	char	*alpha;
	int	valid;
	int	err;

	err = 0;
	alpha = ft_calloc(256, sizeof(char));
	if (!alpha)
		the_end(data);
	valid = 0;
	line = NULL;
	while (get_next_line(fd, &line))
	{
		if (!err)
		{
			if (ft_doChecks(alpha, line) == 1)
				valid++;
			else if (valid != 6 && ft_doChecks(alpha, line) == -1)
				err = 1;
			else if (ft_doChecks(alpha, line) == -2)
				err = 1;
		}
		free(line);
	}
	free(line);
	free(alpha);
	close(fd);
	if (err)
		ft_noHead(data);
}
