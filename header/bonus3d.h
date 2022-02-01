/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:29:11 by graja             #+#    #+#             */
/*   Updated: 2022/02/01 11:07:20 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS3D_H
# define BONUS3D_H
# include "./cube3d.h"
# include <sys/timeb.h>

int		ft_sprite_hook(t_data *img);
void	ft_drawOneSprite(t_data *data, t_ray ray);
void	ft_draw3DSprite(t_data *data, t_ray ray, int i);
void	ft_drawSprite(t_data *data, t_point p1, t_point p2, t_ray ray);
float	ft_rayCorrect(t_data *data, t_ray ray);
t_point	ft_spriteCenter(t_data *data, t_point inp, float alpha, int flag);
t_ray	ft_SpriteRay(t_data *d, float alpha);
void	ft_showSprites(t_data *data);
void	ft_initSprites(t_data *data);
void	ft_dumpSprite(t_sprite s);
void	ft_updateSpriteData(t_data *data);
void	ft_moveBonusPlayer(t_data *data,int flag);
int	ft_key_hook_bonus(int code, t_data *data);
void	ft_drawFovBonus(t_data *data);
int	ft_opendoor(t_data *data, size_t x, size_t y);
void	the_doors(t_data *data);
int	ft_player_in_door(t_data *data);

#endif
