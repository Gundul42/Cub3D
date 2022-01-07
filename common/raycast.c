/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:15:47 by graja             #+#    #+#             */
/*   Updated: 2022/01/07 13:36:45 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_castRay(t_data *d, size_t x, size_t y)
{
	float	alpha;
	float	len;
	size_t	px;
	size_t	py;

	ft_getPlayerPos(d, &px, &py);
	alpha = atan2f(((float)y - (float)py), ((float)x - (float)px));
	alpha = ft_rad2deg(alpha);
	len = sqrtf(pow(((float)px - (float)x), 2) + pow(((float)py - (float)y), 2));
	ft_draw_angeled(d, px, py, alpha, len);
	printf("%4ld - %4ld, %4.2f, %7.2f\n", px, py, alpha, len);
}
