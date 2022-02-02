/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:18:25 by graja             #+#    #+#             */
/*   Updated: 2022/02/02 19:16:47 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
int	ft_isallowed(char *c)
{
	int	len;

	len = ft_strlen(c);
	if (len > 2)
	{
		if (!ft_strncmp(c, "NO ", 3) || !ft_strncmp(c, "SO ", 3))
			return (1);
		else if (!ft_strncmp(c, "WE ", 3) || !ft_strncmp(c, "EA ", 3))
			return (1);
	}
	if (len)
	{
		if (!ft_strncmp(c, "F ", 2) || !ft_strncmp(c, "C ", 2))
			return (1);
	}
	return (0);
}

static
int	ft_do_checks(char *alpha, char *line)
{
	char	*bck;

	bck = line;
	while (*bck == 32)
		bck++;
	if (*bck == '\n' || !*bck)
		return (0);
	if (ft_isdigit(*bck))
		return (-1);
	if (ft_isallowed(bck) && !alpha[(int)(*bck)])
	{
		alpha[(int)(*bck)] = 1;
		return (1);
	}
	else
		return (-2);
	return (0);
}

static
char	*ft_check_init(t_data *data, char **line, int *valid)
{
	char	*alpha;

	alpha = ft_calloc(256, sizeof(char));
	if (!alpha)
		the_end(data, "Could't malloc ft_check_init", 1);
	*valid = 0;
	*line = NULL;
	return (alpha);
}

void	ft_check_head(t_data *data, int fd, int err, int chk)
{
	char	*line;
	char	*alpha;
	int		valid;

	alpha = ft_check_init(data, &line, &valid);
	while (get_next_line(fd, &line))
	{
		if (!err)
		{
			chk = ft_do_checks(alpha, line);
			if (chk == 1)
				valid++;
			else if (chk == 1 && valid > 6)
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
		the_end(data, "Invalid head of .cub map file\n", 1);
}
