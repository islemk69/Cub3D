/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:29:25 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/16 16:59:53 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_pixel_color(t_texture *texture, int x, int y)
{
	return (*(int *)(texture->addr + (y * texture->line_length \
		+ x * (texture->bits_per_pixel / 8))));
}

void	draw_texture(t_texture *texture, t_data *data, int r)
{
	int		i;
	float	c;

	i = -1;
	while (++i < data->scene->line_off)
	{
		my_mlx_pixel_put(data->winmlx, r, i, data->file->color_sky_hex);
	}
	i = -1;
	while (++i < data->scene->line_h)
	{
		c = get_pixel_color(texture, (int)data->scene->tx \
			, (int)(data->scene->ty));
		my_mlx_pixel_put(data->winmlx, r, i + data->scene->line_off, c);
		data->scene->ty += data->scene->ty_step;
	}
	i = data->scene->line_off + data->scene->line_h - 1;
	while (++i < 1080)
	{
		my_mlx_pixel_put(data->winmlx, r, i, data->file->color_floor_hex);
	}
}

void	draw_textured_column(t_data *data, int r, float ra)
{
	if (data->scene->h_redded)
	{
		data->scene->tx = (int)(data->scene->rx) % TILE_SIZE;
		if (ra > 180)
			data->scene->tx = 31 - data->scene->tx;
		if (ra >= 0 && ra < PI)
			draw_texture(data->stex, data, r);
		else
			draw_texture(data->ntex, data, r);
	}
	else
	{
		data->scene->tx = (int)(data->scene->ry) % TILE_SIZE;
		if (ra > 90 && ra < 270)
			data->scene->tx = 31 - data->scene->tx;
		if (ra >= PI / 2 && ra < 3 * PI / 2)
			draw_texture(data->wtex, data, r);
		else
			draw_texture(data->etex, data, r);
	}
}

void	draw_scene(t_data *data, t_scene *scene, int r, float ra)
{
	scene->ca = data->player->pa - ra;
	if (scene->ca < 0)
		scene->ca += 2 * PI;
	if (scene->ca > 2 * PI)
		scene->ca -= 2 * PI;
	scene->dist = scene->dist * cos(scene->ca);
	scene->line_h = (46 * WINHEIGHT) / scene->dist;
	scene->ty_step = 32.0 / (float)scene->line_h;
	scene->ty_off = 0;
	if (scene->line_h > WINHEIGHT)
	{
		scene->ty_off = (scene->line_h - WINHEIGHT) / 2.0;
		scene->line_h = WINHEIGHT;
	}
	scene->line_off = WINHEIGHT / 2 - (scene->line_h / 2);
	scene->ty = scene->ty_off * scene->ty_step;
	scene->tx = 0;
	draw_textured_column(data, r, ra);
}
