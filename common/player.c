/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 08:38:30 by graja             #+#    #+#             */
/*   Updated: 2022/01/17 08:38:39 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cube3d.h"

void	ft_initialize_player(t_data *d, size_t x, size_t y, char dir)
{
	d->px = x;
	d->py = y;
	if (dir == 'W')
		d->dir = 270.0;
	else if (dir == 'E')
		d->dir = 90.0;
	else if (dir == 'N')
		d->dir = 0.0;
	else if (dir == 'S')
		d->dir = 180.0;
}

void	ft_getPlayerPos(t_data *d, size_t *x, size_t *y)
{
	*x = d->px * d->tilesize;
	*y = d->py * d->tilesize;
}
