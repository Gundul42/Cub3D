/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:29:11 by graja             #+#    #+#             */
/*   Updated: 2022/02/03 19:52:42 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS3D_H
# define BONUS3D_H
# include "./cube3d.h"
# include <sys/timeb.h>

int		ft_sprite_hook(t_data *img);
void	ft_draw_one_sprite(t_data *data, t_ray ray);
void	ft_draw_3d_sprite(t_data *data, t_ray ray, int i);
void	ft_drawSprite(t_data *data, t_point p1, t_point p2, t_ray ray);
float	ft_ray_correct(t_data *data, t_ray ray);
t_point	ft_sprite_center(t_data *data, t_point inp, float alpha, int flag);
t_ray	ft_Sprite_ray(t_data *d, float alpha);
void	ft_show_sprites(t_data *data);
void	ft_init_sprites(t_data *data);
void	ft_dump_sprite(t_sprite s);
void	ft_update_sprite_data(t_data *data);
void	ft_move_bonus_player(t_data *data, int flag);
int		ft_key_hook_bonus(int code, t_data *data);
void	ft_draw_fov_bonus(t_data *data);
int		ft_opendoor(t_data *data, size_t x, size_t y);
void	the_doors(t_data *data);
int		ft_player_in_door(t_data *data, int *chk);
int		ft_get_sprite_pixel(t_data *data, int x, int y, int i);
void	ft_sort_sprites(t_data *data);
float	ft_find_alpha(t_data *data, int i);
int		ft_check_door_time(struct timeb start, struct timeb end);
void	ft_get_next_door(t_data *data, size_t *x, size_t *y);

#endif
