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

int	get_pixel_color(t_texture *texture, int x, int y)
{
	return (*(int *)(texture->addr + (y * texture->line_length \
					+ x * (texture->bits_per_pixel / 8))));
}

float   get_texture_scale(t_texture *texture)
{
	return (float)texture->width / 32.0;
}

//void	draw_texture(t_texture *texture, t_data *data, int r)
//{
//	int		i;
//	float	c;
//
//	i = -1;
//	while (++i < data->scene->line_off)
//	{
//		my_mlx_pixel_put(data->winmlx, r, i, data->file->color_sky_hex);
//	}
//	i = -1;
//	while (++i < data->scene->line_h)
//	{
//		c = get_pixel_color(texture, (int)data->scene->tx \
//			, (int)(data->scene->ty));
//		my_mlx_pixel_put(data->winmlx, r, i + data->scene->line_off, c);
//		data->scene->ty += data->scene->ty_step;
//	}
//	i = data->scene->line_off + data->scene->line_h - 1;
//	while (++i < 1080)
//	{
//		my_mlx_pixel_put(data->winmlx, r, i, data->file->color_floor_hex);
//	}
//}

void draw_texture(t_texture *texture, t_data *data, int r)
{
	int i;
	float c;
	float scale = get_texture_scale(texture);

	i = -1;
	while (++i < data->scene->line_off)
		my_mlx_pixel_put(data->winmlx, r, i, data->file->color_sky_hex);
	while (++i < data->scene->line_h + data->scene->line_off)
	{
		c = get_pixel_color(texture, (int)(data->scene->tx * scale), (int)(data->scene->ty * scale));
		my_mlx_pixel_put(data->winmlx, r, i, c);
		data->scene->ty += data->scene->ty_step;
	}
	while (++i < 1080)
		my_mlx_pixel_put(data->winmlx, r, i, data->file->color_floor_hex);
}


//void	draw_textured_column(t_data *data, int r, float ra)
//{
//	if (data->scene->h_redded)
//	{
//		data->scene->tx = (int)(data->scene->rx) % TILE_SIZE;
//		if (ra > 180)
//			data->scene->tx = 31 - data->scene->tx;
//		if (ra >= 0 && ra < PI)
//        {
////            data->scene->tx = 31 - data->scene->tx;
//            draw_texture(data->stex, data, r);
//        }
//		else
//			draw_texture(data->ntex, data, r);
//	}
//	else
//	{
//		data->scene->tx = (int)(data->scene->ry) % TILE_SIZE;
//		if (ra > 90 && ra < 270)
//			data->scene->tx = 31 - data->scene->tx;
//		if (ra >= PI / 2 && ra < 3 * PI / 2)
//        {
////            data->scene->tx = 31 - data->scene->tx;
//            draw_texture(data->wtex, data, r);
//        }
//
//		else
//			draw_texture(data->etex, data, r);
//	}
//}

void draw_textured_column(t_data *data, int r, float ra)
{
	t_texture *texture;

	if (data->scene->h_redded)
	{
		if (ra >= 0 && ra < PI)
		{
			texture = data->stex;
			data->scene->tx = (int)data->scene->rx % TILE_SIZE;
			data->scene->tx = 31 - data->scene->tx;
		}
		else
		{
			texture = data->ntex;
			data->scene->tx = TILE_SIZE - ((int)data->scene->rx % TILE_SIZE) - 1;
			data->scene->tx = 31 - data->scene->tx;
		}
	}
	else
	{
		if (ra >= PI / 2 && ra < 3 * PI / 2)
		{
			texture = data->wtex;
			data->scene->tx = TILE_SIZE - ((int)data->scene->ry % TILE_SIZE) - 1;
		}
		else
		{
			texture = data->etex;
			data->scene->tx = (int)data->scene->ry % TILE_SIZE;
		}
	}

	draw_texture(texture, data, r);
}


//void	draw_scene(t_data *data, t_scene *scene, int r, float ra)
//{
//	scene->ca = data->player->pa - ra;
//	if (scene->ca < 0)
//		scene->ca += 2 * PI;
//	if (scene->ca > 2 * PI)
//		scene->ca -= 2 * PI;
//	scene->dist = scene->dist * cos(scene->ca);
//	scene->line_h = (46 * WINHEIGHT) / scene->dist;
//	scene->ty_step = 32.0 / (float)scene->line_h;
//	scene->ty_off = 0;
//	if (scene->line_h > WINHEIGHT)
//	{
//		scene->ty_off = (scene->line_h - WINHEIGHT) / 2.0;
//		scene->line_h = WINHEIGHT;
//	}
//	scene->line_off = WINHEIGHT / 2 - (scene->line_h / 2);
//	scene->ty = scene->ty_off * scene->ty_step;
//	scene->tx = 0;
//	draw_textured_column(data, r, ra);
//}

void draw_scene(t_data *data, t_scene *scene, int r, float ra)
{
	float scale_factor;
	t_texture *texture;

	if (data->scene->h_redded)
	{
		texture = (ra >= 0 && ra < PI) ? data->stex : data->ntex;
	}
	else
	{
		texture = (ra >= PI / 2 && ra < 3 * PI / 2) ? data->wtex : data->etex;
	}

	scale_factor = get_texture_scale(texture);
	scene->ca = data->player->pa - ra;
	if (scene->ca < 0)
		scene->ca += 2 * PI;
	if (scene->ca > 2 * PI)
		scene->ca -= 2 * PI;
	scene->dist = scene->dist * cos(scene->ca);
	scene->line_h = (46 * WINHEIGHT) / scene->dist;
	scene->ty_step = (float)texture->height / (float)scene->line_h;
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

