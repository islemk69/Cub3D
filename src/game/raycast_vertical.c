/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_vertical.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:28:45 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/17 18:23:34 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	looking_vertical(t_scene *scene, t_data *data);
static void	init_vertical(t_scene *s, t_data *d);

void	check_vertical_line(t_scene *s, t_data *d)
{
	looking_vertical(s, d);
	init_vertical(s, d);
	while (s->dof < d->file->greather)
	{
		s->mx = (int)(s->rx / TILE_SIZE);
		s->my = (int)(s->ry / TILE_SIZE);
		if (s->mx >= 0 && s->mx < d->file->wmap && s->my >= 0
			&& s->my < d->file->hmap
			&& s->mx < (int)ft_strlen(d->file->map[s->my])
			&& s->my < (int)ft_tablen(d->file->map)
			&& d->file->map[s->my][s->mx] == '1')
		{
			s->vx = s->rx;
			s->vy = s->ry;
			s->dis_v = dist(d->player->px, d->player->py, s->vx, s->vy);
			break ;
		}
		else
		{
			s->rx += s->xo;
			s->ry += s->yo;
			s->dof += 1;
		}
	}
}

static void	init_vertical(t_scene *s, t_data *d)
{
	s->dof = 0;
	s->vx = d->player->px;
	s->vy = d->player->py;
	s->dis_v = 1000000;
}

static void	looking_vertical(t_scene *scene, t_data *data)
{
	float	n_tan;

	n_tan = -tan(scene->ra);
	if (scene->ra > PI / 2 && scene->ra < 3 * PI / 2)
	{
		scene->rx = (float)(((int)data->player->px / TILE_SIZE) * \
		TILE_SIZE) - 0.0001;
		scene->ry = (data->player->px - scene->rx) * n_tan + data->player->py;
		scene->xo = -TILE_SIZE;
		scene->yo = -scene->xo * n_tan;
	}
	else if (scene->ra < PI / 2 || scene->ra > 3 * PI / 2)
	{
		scene->rx = (float)(((int)data->player->px / TILE_SIZE) * \
		TILE_SIZE) + TILE_SIZE;
		scene->ry = (data->player->px - scene->rx) * n_tan + data->player->py;
		scene->xo = TILE_SIZE;
		scene->yo = -scene->xo * n_tan;
	}
	else
	{
		scene->rx = data->player->px;
		scene->ry = data->player->py;
		scene->dof = data->file->greather;
	}
}
