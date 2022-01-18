/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:29:11 by graja             #+#    #+#             */
/*   Updated: 2022/01/18 15:48:55 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS3D_H
# define BONUS3D_H
# include "./cube3d.h"

int		ft_isSprite(t_data *data, size_t x, size_t y);
int		ft_checkSpriteWE(t_data *data, t_point p, float alpha);
int		ft_checkSpriteNS(t_data *data, t_point p, float alpha);
void	ft_drawSpriteFov(t_data *data);
int	ft_sprite_hook(t_data *img);
t_ray	*ft_spriteRay(t_data *d, float alpha, t_ray *ray);

#endif
