/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:43:51 by graja             #+#    #+#             */
/*   Updated: 2021/09/17 18:07:00 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/fractol.h"

int	the_end(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->palette);
	free(data->breakpts);
	free(data);
	exit (0);
	return (0);
}

void	ft_print_error(t_data *data, char **argv)
{
	if (!data)
		printf(" >>> ERROR: Out of memory <<<\n");
	else
	{
		free(data);
		printf("\nMissing or invalid arguments:\n %s", argv[0]);
		printf(" (chosing one fractal set is mandatory)\n\n");
		printf("	-mandel	: shows Mandelbrot set\n");
		printf("	-julia	: shows Julia set at");
		printf(" [-jr][-ji]\n");
		printf("	-jr	: real_part of julia konstant\n");
		printf("	-ji 	: imaginary_part of julia konstant\n");
		printf("	-ship	: shows Burning Ship set\n\n");
		printf("	-high	: high resolution preset\n");
		printf("	-medium	: medium resolution preset\n");
		printf("	-low	: low resolution preset\n");
	}
	exit (1);
}

int	ft_get_cmdline(int argc, char **argv, t_data *f)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	if (!f || argc < 2)
		ft_print_error(f, argv);
	while (i <= (argc - 1))
	{
		if (!f->type)
			f->type = ft_cmd_fractal(argv[i]);
		error = ft_cmd_resolution(f, argv[i]);
		error = error && ft_cmd_julia(f, argv[i]);
		if (!f->type || (i > 1 && error))
			ft_print_error(f, argv);
		i++;
	}
	ft_init_window(f, f->x, f->y, f->i);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*img;

	img = ft_blank(NULL);
	if (!ft_get_cmdline(argc, argv, img))
		return (1);
	img->mlx = mlx_init();
	if (!img->mlx)
		return (1);
	img->breakpts = ft_init_colors();
	img->palette = ft_init_palette(img);
	img->win = mlx_new_window(img->mlx, img->x, img->y,
			"Fractol V1.125 (c) Gundul");
	img->img = mlx_new_image(img->mlx, img->x, img->y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	ft_draw_fractal(img);
	mlx_key_hook(img->win, ft_key_hook, img);
	mlx_hook(img->win, 17, 1L << 2, the_end, img);
	mlx_mouse_hook(img->win, ft_mouse_hook, img);
	mlx_loop_hook(img->mlx, ft_loop_hook, img);
	mlx_loop(img->mlx);
	return (0);
}
