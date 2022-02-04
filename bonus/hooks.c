/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:16:10 by graja             #+#    #+#             */
/*   Updated: 2022/02/04 10:21:22 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

static
int	ft_checktime(struct timeb start, struct timeb end, int *r)
{
	int			diff;
	static int	fps = 0;

	diff = (int)(1000.0 * (end.time - start.time)
			+ (end.millitm - start.millitm));
	if (diff < 999)
		return (fps);
	fps = *r;
	*r = 0;
	return (fps);
}

static
void	ft_print_fps(t_data *img, int fps)
{
	char	*num;

	ft_draw_map_bck(img);
	ft_draw2dmap(img);
	ft_map_heading(img);
	num = ft_itoa(fps);
	mlx_string_put(img->mlx, img->win2, 380, 10, 0, num);
	mlx_string_put(img->mlx, img->win2, 400, 10, 0, "FPS");
	free(num);
}

int	ft_sprite_hook(t_data *img)
{
	static struct timeb	start;
	static struct timeb	end;
	static int			runner = 0;

	if (!runner)
		ftime(&start);
	runner++;
	mlx_do_sync(img->mlx);
	ft_draw_background(img);
	ft_draw_fov_bonus(img);
	ft_update_sprite_data(img);
	ft_show_sprites(img);
	mlx_put_image_to_window(img->mlx, img->win2, img->img2, 0, 0);
	if (img->m_map)
		mlx_put_image_to_window(img->mlx, img->win2, img->img1,
			img->win_x - (img->win_x / img->minimap * 1.5), img->minimap / 2);
	if (img->mouse)
		ft_mouse_rot_player(img);
	if (img->chkdoor)
		ft_opendoor(img, img->doorx, img->doory);
	ftime(&end);
	ft_print_fps(img, ft_checktime(start, end, &runner));
	return (0);
}

int	ft_key_hook_bonus(int code, t_data *data)
{
	if (code == 65307)
		the_end(data, NULL, 0);
	if (code == 32)
		the_doors(data);
	if (code == 109)
		data->m_map = !data->m_map;
	if (code == 114)
		data->mouse = !data->mouse;
	if (code == 43)
		ft_map_zoom(data, 1);
	if (code == 35)
		ft_map_zoom(data, 0);
	if (code == 119 || code == 65362)
		ft_move_bonus_player(data, 1);
	if (code == 115 || code == 65364)
		ft_move_bonus_player(data, 2);
	if (code == 100)
		ft_move_bonus_player(data, 3);
	if (code == 97)
		ft_move_bonus_player(data, 4);
	if (code == 65361)
		ft_rotate_player(data, 0);
	if (code == 65363)
		ft_rotate_player(data, 1);
	return (code);
}
