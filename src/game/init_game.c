/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:33:32 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/13 17:41:18 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	random_next_frame(t_data *data)
{
	data->winmlx->img = mlx_new_image(data->winmlx->mlx, 1920, 1080);
	data->winmlx->addr = mlx_get_data_addr(data->winmlx->img, &data->winmlx->bits_per_pixel, &data->winmlx->line_length, &data->winmlx->endian);
    move(data);
    ray_cast(data, data->scene);
    drawmap(data);
    mlx_put_image_to_window(data->winmlx->mlx, data->winmlx->mlx_win, data->winmlx->img, 0, 0);
    mlx_destroy_image(data->winmlx->mlx, data->winmlx->img);
    return (0);
}


int load_texture(t_data *data)
{
    data->ntex->img = mlx_xpm_file_to_image(data->winmlx->mlx, \
        "src/xpm/north.xpm", &data->ntex->width, &data->ntex->height);
    data->ntex->addr = mlx_get_data_addr(data->ntex->img, \
        &data->ntex->bits_per_pixel, &data->ntex->line_length, &data->ntex->endian);
	data->stex->img = mlx_xpm_file_to_image(data->winmlx->mlx, \
        "src/xpm/sud.xpm", &data->stex->width, &data->stex->height);\
	data->stex->addr = mlx_get_data_addr(data->stex->img, \
        &data->stex->bits_per_pixel, &data->stex->line_length, &data->stex->endian);
	data->etex->img = mlx_xpm_file_to_image(data->winmlx->mlx, \
        "src/xpm/est.xpm", &data->etex->width, &data->etex->height);\
	data->etex->addr = mlx_get_data_addr(data->etex->img, \
        &data->etex->bits_per_pixel, &data->etex->line_length, &data->etex->endian);
	data->wtex->img = mlx_xpm_file_to_image(data->winmlx->mlx, \
        "src/xpm/ouest.xpm", &data->wtex->width, &data->wtex->height);\
	data->wtex->addr = mlx_get_data_addr(data->wtex->img, \
        &data->wtex->bits_per_pixel, &data->wtex->line_length, &data->wtex->endian);
    return (0);
}

int init_game(t_winmlx *winmlx, t_data *data)
{
	winmlx->mlx = mlx_init();
	winmlx->mlx_win = mlx_new_window(winmlx->mlx, 1920, 1080, "Cub3d");
    load_texture(data);
	mlx_hook(data->winmlx->mlx_win, 2, 1L << 0, key_press_hook, data);
    mlx_hook(data->winmlx->mlx_win, 3, (1L<<1), key_release_hook, data);
	mlx_loop_hook(winmlx->mlx, random_next_frame, data);
	mlx_loop(winmlx->mlx);
	return (0);
}