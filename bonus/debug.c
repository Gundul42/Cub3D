/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 09:43:46 by graja             #+#    #+#             */
/*   Updated: 2022/01/23 09:44:27 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

void	ft_dumpSprite(t_sprite s)
{
	printf("****************************************************\n");
	printf("Position            : x%5.2f -- y%5.2f\n", s.p.x, s.p.y);
	printf("angle to player     : %5.2f degrees\n", s.dir);
	printf("distance to player  : %5.2f pixels\n",s.dist);
	printf("code                : %d\n", s.code);
	printf("is walkable         : %d\n", s.walkable);
	printf("is collectable      : %d\n", s.collectable);
	printf("can move            : %d\n", s.canmove);
	printf("****************************************************\n\n");
}
