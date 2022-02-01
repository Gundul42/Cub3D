/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flormich <flormich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:16:10 by graja             #+#    #+#             */
/*   Updated: 2022/01/31 11:59:22 by flormich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus3d.h"

/* Flags:
 * 		1 = up
 * 		2 = down
 * 		3 = right
 * 		4 = left
 *
 * 		first save player position, then calculate the new positions
 * 		then check data->map[xyz] == 0 ? Only if true, save the new
 * 		player position.
*/
void	ft_moveBonusPlayer(t_data *data,int flag)
{
	float	newx;
	float	newy;

	newx = data->px;
	newy = data->py;
	data->run = 1;
	if (flag == 1 || flag == 2)
		ft_forbac(data, &newx, &newy, flag);
	if (flag == 3 || flag == 4)
		ft_leftright(data, &newx, &newy, flag);
	newx += data->px;
	newy += data->py;
	if (data->map[(size_t)(newy)][(size_t)(newx)] == 0 ||
		data->map[(size_t)(newy)][(size_t)(newx)] == 2 ||
		data->map[(size_t)(newy)][(size_t)(newx)] == 3)
	{
		data->px = newx;
		data->py = newy;
	}
}

static
int	ft_checktime(struct timeb start, struct timeb end, int *r)
{
	int	diff;
	static int	fps = 0;

	diff = (int)(1000.0 * (end.time - start.time) +
			(end.millitm - start.millitm));
	if (diff < 999)
		return (fps);
	fps = *r;
	*r = 0;
	return (fps);
}

int	ft_sprite_hook(t_data *img)
{
	static struct timeb	start;
	static struct timeb	end;
	static int	runner = 0;
	int			fps;
	char		*num;

	if (!runner)
		ftime(&start);
	runner++;
	mlx_do_sync(img->mlx);
	ft_draw_background(img);
	ft_draw2dmap(img);
	if (img->run)
	{
		ft_drawFovBonus(img);
		ft_updateSpriteData(img);
		ft_showSprites(img);
	}
	mlx_put_image_to_window(img->mlx, img->win2, img->img2, 0, 0);
	if (img->mMap)
		mlx_put_image_to_window(img->mlx, img->win2, img->img1,
			img->win_x - (img->win_x / img->minimap * 1.5), img->minimap / 2);
	if (img->mouse)
		ft_mouseRotPlayer(img);
	if (img->chkdoor)
		ft_opendoor(img, 3, 24);
	ftime(&end);
	fps = ft_checktime(start, end, &runner);
	num = ft_itoa(fps);
	mlx_string_put(img->mlx, img->win2, 380, 10, 0, num);
	mlx_string_put(img->mlx, img->win2, 400, 10, 0, "FPS");
	free(num);
	return (0);
}

int	ft_key_hook_bonus(int code, t_data *data)
{
	//printf("Key: %d)\n", code);
	if (code == 65307)
		the_end(data, NULL, 0);
	if (code == 99)
		data->correct = !data->correct;
	if (code == 32)
	{
		data->chkdoor = 1;
		data->doors[24][3] = 2;
	}
	if (code == 109)
		data->mMap = !data->mMap;
	if (code == 114)
		data->mouse = !data->mouse;
	if (code == 43)
		ft_MapZoom(data, 1);
	if (code == 35)
		ft_MapZoom(data, 0);
	if (code == 119 || code == 65362)
		ft_moveBonusPlayer(data, 1);		// W
	if (code == 115 || code == 65364)
		ft_moveBonusPlayer(data, 2);		// S
	if (code == 100)
		ft_moveBonusPlayer(data, 3);		// A
	if (code == 97)
		ft_moveBonusPlayer(data, 4);		// D
	if (code == 65361)
		ft_rotatePlayer(data, 0);	// cursor right
	if (code == 65363)
		ft_rotatePlayer(data, 1);	// cursor left
	return (code);
}

