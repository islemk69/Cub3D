/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_vertical.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:28:45 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/15 14:44:19 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	looking_vertical(t_scene *scene, t_data *data)
{
	float	n_tan;

	n_tan = -tan(scene->ra);
	if (scene->ra > P2 && scene->ra < P3)
	{
		scene->rx = (float)(((int)data->player->px / TILE_SIZE) * \
		TILE_SIZE) - 0.0001;
		scene->ry = (data->player->px - scene->rx) * n_tan + data->player->py;
		scene->xo = -TILE_SIZE;
		scene->yo = -scene->xo * n_tan;
	}
	else if (scene->ra < P2 || scene->ra > P3)
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

size_t	ft_tablen(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	check_vertical_line(t_scene *s, t_data *d)
{
	s->dof = 0;
	s->vx = d->player->px;
	s->vy = d->player->py;
	s->disV = 1000000;
	looking_vertical(s, d);
	while (s->dof < d->file->greather)
	{
		s->mx = (int)(s->rx / TILE_SIZE);
		s->my = (int)(s->ry / TILE_SIZE);
		if (s->mx >= 0 && s->my >= 0 && s->mx < (int)ft_strlen(d->file->map[s->my]) && s->my < (int)ft_tablen(d->file->map) && d->file->map[s->my][s->mx] == '1')
		{
			s->vx = s->rx;
			s->vy = s->ry;
			s->disV = dist(d->player->px, d->player->py, s->vx, s->vy);
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
