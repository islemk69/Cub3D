/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:33:32 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/14 16:56:52 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	random_next_frame(t_data *data)
{
	data->winmlx->img = mlx_new_image(data->winmlx->mlx, 1920, 1080);
	data->winmlx->addr = mlx_get_data_addr(data->winmlx->img, \
		&data->winmlx->bits_per_pixel, &data->winmlx->line_length, \
		&data->winmlx->endian);
	move(data);
	ray_cast(data, data->scene);
	drawmap(data);
	mlx_put_image_to_window(data->winmlx->mlx, data->winmlx->mlx_win, \
		data->winmlx->img, 0, 0);
	mlx_destroy_image(data->winmlx->mlx, data->winmlx->img);
	return (0);
}

int	load_texture(t_data *d)
{
	d->ntex->img = mlx_xpm_file_to_image(d->winmlx->mlx, \
		"src/xpm/north.xpm", &d->ntex->width, &d->ntex->height);
	d->ntex->addr = mlx_get_data_addr(d->ntex->img, \
		&d->ntex->bits_per_pixel, &d->ntex->line_length, &d->ntex->endian);
	d->stex->img = mlx_xpm_file_to_image(d->winmlx->mlx, \
		"src/xpm/sud.xpm", &d->stex->width, &d->stex->height);
	d->stex->addr = mlx_get_data_addr(d->stex->img, \
		&d->stex->bits_per_pixel, &d->stex->line_length, &d->stex->endian);
	d->etex->img = mlx_xpm_file_to_image(d->winmlx->mlx, \
		"src/xpm/est.xpm", &d->etex->width, &d->etex->height);
	d->etex->addr = mlx_get_data_addr(d->etex->img, \
		&d->etex->bits_per_pixel, &d->etex->line_length, &d->etex->endian);
	d->wtex->img = mlx_xpm_file_to_image(d->winmlx->mlx, \
		"src/xpm/ouest.xpm", &d->wtex->width, &d->wtex->height);
	d->wtex->addr = mlx_get_data_addr(d->wtex->img, \
		&d->wtex->bits_per_pixel, &d->wtex->line_length, &d->wtex->endian);
	return (0);
}

int	init_game(t_winmlx *winmlx, t_data *data)
{
	winmlx->mlx = mlx_init();
	winmlx->mlx_win = mlx_new_window(winmlx->mlx, 1920, 1080, "Cub3d");
	load_texture(data);
	mlx_hook(data->winmlx->mlx_win, 2, 1L << 0, key_press_hook, data);
	mlx_hook(data->winmlx->mlx_win, 3, (1L << 1), key_release_hook, data);
	mlx_loop_hook(winmlx->mlx, random_next_frame, data);
	mlx_loop(winmlx->mlx);
	return (0);
}
