/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:29:25 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/20 16:11:42 by blakehal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	put_texture(t_texture *texture, t_data *data, int r);
static void	draw_s_and_n_texture(t_data *data, float ra, t_texture **texture);
static void	draw_e_and_w_texture(t_data *data, float ra, t_texture **texture);
static void	draw_textured_column(t_data *data, int r, float ra);

void	draw_scene(t_data *data, t_scene *scene, int r, float ra)
{
	float		scale_factor;
	t_texture	*tmp_texture;

	define_which_texture(data, &tmp_texture, ra);
	scale_factor = get_texture_scale(tmp_texture);
	scene->ca = data->player->pa - ra;
	if (scene->ca < 0)
		scene->ca += 2 * PI;
	if (scene->ca > 2 * PI)
		scene->ca -= 2 * PI;
	scene->dist = scene->dist * cos(scene->ca);
	scene->line_h = (46 * WINHEIGHT) / scene->dist;
	scene->ty_step = (float)tmp_texture->height / (float)scene->line_h;
	scene->ty_step /= scale_factor;
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

static void	draw_textured_column(t_data *data, int r, float ra)
{
	t_texture	*texture;

	draw_s_and_n_texture(data, ra, &texture);
	draw_e_and_w_texture(data, ra, &texture);
	put_texture(texture, data, r);
}

static void	draw_s_and_n_texture(t_data *data, float ra, t_texture **texture)
{
	if (data->scene->h_redded)
	{
		if (ra >= 0 && ra < PI)
		{
			*texture = data->stex;
			data->scene->tx = (int)data->scene->rx % TILE_SIZE;
			data->scene->tx = 31 - data->scene->tx;
		}
		else
		{
			*texture = data->ntex;
			data->scene->tx = TILE_SIZE - \
			((int)data->scene->rx % TILE_SIZE) - 1;
			data->scene->tx = 31 - data->scene->tx;
		}
	}
}

static void	draw_e_and_w_texture(t_data *data, float ra, t_texture **texture)
{
	if (!data->scene->h_redded)
	{
		if (ra >= PI / 2 && ra < 3 * PI / 2)
		{
			*texture = data->wtex;
			data->scene->tx = TILE_SIZE - \
			((int)data->scene->ry % TILE_SIZE) - 1;
		}
		else
		{
			*texture = data->etex;
			data->scene->tx = (int)data->scene->ry % TILE_SIZE;
		}
	}
}

static void	put_texture(t_texture *texture, t_data *data, int r)
{
	int		i;
	float	c;
	float	scale;

	scale = get_texture_scale(texture);
	i = -1;
	while (++i < data->scene->line_off)
		my_mlx_pixel_put(data->winmlx, r, i, data->file->color_sky_hex);
	i--;
	while (++i < data->scene->line_h + data->scene->line_off)
	{
		c = get_pixel_color(texture, (int)(data->scene->tx * scale), \
		(int)(data->scene->ty * scale));
		my_mlx_pixel_put(data->winmlx, r, i, c);
		data->scene->ty += data->scene->ty_step;
	}
	i--;
	while (++i < 1080)
		my_mlx_pixel_put(data->winmlx, r, i, data->file->color_floor_hex);
}
