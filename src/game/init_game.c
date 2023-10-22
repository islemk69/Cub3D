/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:33:32 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/17 17:57:59 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	random_next_frame(t_data *data);
static int	load_texture(t_data *d, t_file *file);
static int	close_window(t_data *data);

int	init_game(t_winmlx *winmlx, t_data *data)
{
	winmlx->mlx = mlx_init();
	if (!winmlx->mlx)
		return (1);
	winmlx->mlx_win = mlx_new_window(winmlx->mlx, WINWIDTH, WINHEIGHT, "Cub3d");
	if (!winmlx->mlx_win || load_texture(data, data->file))
		return (1);
	mlx_hook(data->winmlx->mlx_win, 17, 0, close_window, data);
	mlx_hook(data->winmlx->mlx_win, 2, 1L << 0, key_press_hook, data);
	mlx_hook(data->winmlx->mlx_win, 3, (1L << 1), key_release_hook, data);
	mlx_loop_hook(winmlx->mlx, random_next_frame, data);
	mlx_loop(winmlx->mlx);
	return (0);
}

static int	load_texture(t_data *d, t_file *file)
{
	d->ntex->img = mlx_xpm_file_to_image(d->winmlx->mlx, \
		file->path_to_n, &d->ntex->width, &d->ntex->height);
	d->stex->img = mlx_xpm_file_to_image(d->winmlx->mlx, \
		file->path_to_s, &d->stex->width, &d->stex->height);
	d->etex->img = mlx_xpm_file_to_image(d->winmlx->mlx, \
		file->path_to_e, &d->etex->width, &d->etex->height);
	d->wtex->img = mlx_xpm_file_to_image(d->winmlx->mlx, \
		file->path_to_w, &d->wtex->width, &d->wtex->height);
	if (!d->wtex->img || !d->ntex->img || !d->stex->img || !d->etex->img)
		return (1);
	d->ntex->addr = mlx_get_data_addr(d->ntex->img, \
		&d->ntex->bits_per_pixel, &d->ntex->line_length, &d->ntex->endian);
	d->stex->addr = mlx_get_data_addr(d->stex->img, \
		&d->stex->bits_per_pixel, &d->stex->line_length, &d->stex->endian);
	d->etex->addr = mlx_get_data_addr(d->etex->img, \
		&d->etex->bits_per_pixel, &d->etex->line_length, &d->etex->endian);
	d->wtex->addr = mlx_get_data_addr(d->wtex->img, \
		&d->wtex->bits_per_pixel, &d->wtex->line_length, &d->wtex->endian);
	return (0);
}

static int	random_next_frame(t_data *data)
{
	data->winmlx->img = mlx_new_image(data->winmlx->mlx, 1920, 1080);
	if (!data->winmlx->img)
		return (ft_free_all(data, 1), exit(0), 1);
	data->winmlx->addr = mlx_get_data_addr(data->winmlx->img, \
		&data->winmlx->bits_per_pixel, &data->winmlx->line_length, \
		&data->winmlx->endian);
	move(data);
	ray_cast(data, data->scene);
	drawmap(data, 0, 0, 0);
	mlx_put_image_to_window(data->winmlx->mlx, data->winmlx->mlx_win, \
		data->winmlx->img, 0, 0);
	mlx_destroy_image(data->winmlx->mlx, data->winmlx->img);
	return (0);
}

static int	close_window(t_data *data)
{
	ft_free_all(data, 0);
	exit(0);
}
