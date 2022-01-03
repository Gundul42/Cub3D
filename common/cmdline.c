/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 11:48:58 by graja             #+#    #+#             */
/*   Updated: 2021/09/16 17:48:39 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

int	ft_cmd_fractal(char *str)
{
	if (!ft_strncmp(str, "-mandel", 8))
		return (1);
	else if (!ft_strncmp(str, "-julia", 7))
		return (2);
	else if (!ft_strncmp(str, "-ship", 6))
		return (3);
	else
		return (0);
}

int	ft_cmd_resolution(t_data *data, char *str)
{
	int	val;

	val = 0;
	if (!ft_strncmp(str, "-high", 6))
		val = 1;
	else if (!ft_strncmp(str, "-medium", 8))
		val = 2;
	else if (!ft_strncmp(str, "-low", 5))
		val = 3;
	if (val == 1)
		ft_init_window(data, 1200, 800, 1000);
	else if (val == 2)
		ft_init_window(data, 900, 600, 500);
	else if (val == 3)
		ft_init_window(data, 450, 300, 255);
	else
		return (1);
	return (0);
}

int	ft_cmd_julia(t_data *data, char *str)
{
	if (ft_strlen(str) > 3 && !ft_strncmp(str, "-jr", 3))
		data->juliareal = ft_atof(str + 3);
	else if (ft_strlen(str) > 3 && !ft_strncmp(str, "-ji", 3))
		data->juliaimg = ft_atof(str + 3);
	else
		return (1);
	return (0);
}
