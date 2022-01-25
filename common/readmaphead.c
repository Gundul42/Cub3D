/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmaphead.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:17:02 by graja             #+#    #+#             */
/*   Updated: 2022/01/25 15:36:14 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
int	ft_loadColor(t_data *data, char *str, int flag)
{
	int		col;
	t_color	mycol;

	str++;
	while (*str == 32)
		str++;
	col = ft_str2col(str, &mycol);
	if (col < 0)
		return (1);
	if (flag)
		data->cfloor_near = mycol;
	else
		data->csky = col;
	return (0);
}

static
int	ft_setTexture(char **tex, char *str, int flag)
{
	str += 2;
	while (*str == 32)
		str++;
	if (!ft_strlen(str))
		return (1);
	tex[flag] = ft_strdup(str);
	if (!tex[flag])
		return (1);
	return (0);
}

static
int	ft_loadData(t_data *data, char *str, char **tex)
{
	static int	err = 0;

	if (err)
		return (1);
	if (!ft_strncmp(str, "F ", 2))
		err = ft_loadColor(data, str, 1);
	if (!ft_strncmp(str, "C ", 2))
		err = ft_loadColor(data, str, 0);
	if (!ft_strncmp(str, "NO ", 3))
		err = ft_setTexture(tex, str, 1);
	if (!ft_strncmp(str, "SO ", 3))
		err = ft_setTexture(tex, str, 0);
	if (!ft_strncmp(str, "EA ", 3))
		err = ft_setTexture(tex, str, 2);
	if (!ft_strncmp(str, "WE ", 3))
		err = ft_setTexture(tex, str, 3);
	return (err);
}

static
void	ft_noTex(t_data *data, char **tex, char *path)
{
	if (!path)
		path = "maps/test.cub";
	write(2, "Wrong color or texture definition in: ", 39);
	write(2, path, ft_strlen(path));
	write(2, "\n", 1);
	ft_freeTex(tex);
	the_end(data, "Please correct the map\n", 1);
}

void	ft_readHead(t_data *data, char *path, int fd, int err)
{
	char	*line;
	char	*bck;
	char	**tex;

	fd = ft_openFile(data, path);
	line = NULL;
	tex = ft_calloc(4, sizeof(char *));
	if (!tex)
		the_end(data, "Couldn't malloc tex\n", 1);
	while (get_next_line(fd, &line))
	{
		bck = line;
		while (*bck == 32)
			bck++;
		if (*bck && !ft_isdigit(*bck))
			err = ft_loadData(data, bck, tex);
		free(line);
	}
	free(line);
	close(fd);
	if (err)
		ft_noTex(data, tex, path);
	ft_loadTextures(data, tex);
}

/*
 * this is only temp used for loading textures
 * con be freed after use or in case of file not found
 */
void	ft_freeTex(char **tex)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (tex[i])
			free(tex[i]);
		i++;
	}
	free(tex);
}
