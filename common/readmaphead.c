/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmaphead.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:17:02 by graja             #+#    #+#             */
/*   Updated: 2022/02/09 15:31:01 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

static
int	ft_load_color(t_data *data, char *str, int flag)
{
	int		col;
	t_color	mycol;

	str++;
	while (*str == 32)
		str++;
	col = ft_str2col(str, &mycol, 0);
	if (col < 0)
		return (-1);
	if (flag)
		data->cfloor_near = mycol;
	else
		data->csky = col;
	return (0);
}

static
int	ft_set_textures(char **tex, char *str, int flag)
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
int	ft_load_data(t_data *data, char *str, char **tex)
{
	static int	err = 0;

	if (err)
		return (err);
	if (!ft_strncmp(str, "F ", 2))
		err = ft_load_color(data, str, 1);
	if (!ft_strncmp(str, "C ", 2))
		err = ft_load_color(data, str, 0);
	if (!ft_strncmp(str, "NO ", 3))
		err = ft_set_textures(tex, str, 1);
	if (!ft_strncmp(str, "SO ", 3))
		err = ft_set_textures(tex, str, 0);
	if (!ft_strncmp(str, "EA ", 3))
		err = ft_set_textures(tex, str, 2);
	if (!ft_strncmp(str, "WE ", 3))
		err = ft_set_textures(tex, str, 3);
	return (err);
}

static
void	ft_no_texture(t_data *data, char **tex, char *path, int err)
{
	if (path && err > 0)
	{
		write(2, "Wrong texture path: ", 39);
		write(2, path, ft_strlen(path));
		write(2, " <<<\n", 1);
		ft_free_tex(tex);
		the_end(data, "Please correct the header part in .cub file\n", 1);
	}
	else if (!path && err > 0)
	{
		ft_free_tex(tex);
		the_end(data, "Please correct the header part in .cub file\n", 1);
	}
	else if (err < 0)
	{
		ft_free_tex(tex);
		the_end(data, "Invalid color definition in .cub file\n", 1);
	}
}

void	ft_read_head(t_data *data, char *path, int fd, int err)
{
	char	*line;
	char	*bck;
	char	**tex;

	fd = ft_open_file(data, path);
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
			err = ft_load_data(data, bck, tex);
		free(line);
	}
	free(line);
	close(fd);
	if (err)
		ft_no_texture(data, tex, path, err);
	ft_load_textures(data, tex, 0);
	ft_free_tex(tex);
}
