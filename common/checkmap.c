/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:18:25 by graja             #+#    #+#             */
/*   Updated: 2022/01/16 16:08:39 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
int	ft_isAllowed(char *c)
{
	int	len;

	len = ft_strlen(c);
	if (len > 2)
	{
		if (!ft_strncmp(c ,"NO ", 3) || !ft_strncmp(c, "SO ", 3))
			return (1);
		else if (!ft_strncmp(c ,"WE ", 3) || !ft_strncmp(c, "EA ", 3))
			return (1);
	}
	if (len)
	{
		if (!ft_strncmp(c ,"F ", 2) || !ft_strncmp(c, "C ", 2))
			return (1);
	}
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
	if (ft_isAllowed(bck) && !alpha[(int)(*bck)])
	{
		alpha[(int)(*bck)] = 1;
		return (1);
	}
	else 
		return (-2);
	return (0);
}

static
char	*ft_checkInit(t_data *data, char **line, int *valid)
{
	char	*alpha;

	alpha = ft_calloc(256, sizeof(char));
	if (!alpha)
		the_end(data);
	*valid = 0;
	*line = NULL;
	return (alpha);
}

void	ft_checkHead(t_data *data, int fd, int err, int chk)
{
	char	*line;
	char	*alpha;
	int	valid;

	alpha =	ft_checkInit(data, &line, &valid);
	while (get_next_line(fd, &line))
	{
		if (!err)
		{
			chk = ft_doChecks(alpha, line);
			if (chk == 1)
				valid++;
			else if (chk == 1 && valid > 6 )
				err = 1;
			else if (chk == -2)
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
