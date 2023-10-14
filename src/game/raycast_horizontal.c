/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_horizontal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:29:27 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/14 16:36:45 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	looking_horizontal(t_scene *scene, t_data *d)
{
	float	a_tan;

	a_tan = -1 / tan(scene->ra);
	if (scene->ra > PI)
	{
		scene->ry = (float)(((int)d->player->py / 30) * 30) - 0.0001;
		scene->rx = (d->player->py - scene->ry) * a_tan + d->player->px;
		scene->yo = -30;
		scene->xo = -scene->yo * a_tan;
	}
	else if (scene->ra < PI)
	{
		scene->ry = (float)(((int)d->player->py / 30) * 30) + 30;
		scene->rx = (d->player->py - scene->ry) * a_tan + d->player->px;
		scene->yo = 30;
		scene->xo = -scene->yo * a_tan;
	}
	else
	{
		scene->rx = d->player->px;
		scene->ry = d->player->py;
		scene->dof = d->file->greather;
	}
}

void	check_horizontal_line(t_scene *s, t_data *d)
{
	s->dof = 0;
	s->disH = 100000000;
	s->hx = d->player->px;
	s->hy = d->player->py;
	looking_horizontal(s, d);
	while (s->dof < d->file->greather)
	{
		s->mx = (int)(s->rx / 30);
		s->my = (int)(s->ry / 30);
		if (s->mx >= 0 && s->mx < d->file->wmap && s->my >= 0 \
			&& s->my < d->file->hmap && d->file->map[s->my][s->mx] == '1')
		{
			s->hx = s->rx;
			s->hy = s->ry;
			s->disH = dist(d->player->px, d->player->py, s->hx, s->hy);
			s->dof = d->file->greather;
		}
		else
		{
			s->rx += s->xo;
			s->ry += s->yo;
			s->dof += 1;
		}
	}
}
