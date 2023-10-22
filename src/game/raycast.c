/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:32:58 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/16 16:32:36 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	choose_line(t_scene *scene);

void	ray_cast(t_data *data, t_scene *scene)
{
	int		r;

	scene->ra = data->player->pa - DR * TILE_SIZE;
	r = -1;
	while (++r < 1920)
	{
		check_horizontal_line(scene, data);
		check_vertical_line(scene, data);
		choose_line(scene);
		draw_scene(data, scene, r, scene->ra);
		scene->ra += DR * (FOV_ANGLE / 1920.0);
		if (scene->ra < 0)
			scene->ra += 2 * PI;
		if (scene->ra > 2 * PI)
			scene->ra -= 2 * PI;
	}
}

static void	choose_line(t_scene *scene)
{
	scene->h_redded = 1;
	if (scene->dis_v < scene->dis_h)
	{
		scene->rx = scene->vx;
		scene->ry = scene->vy;
		scene->dist = scene->dis_v;
		scene->h_redded = 0;
	}
	else
	{
		scene->rx = scene->hx;
		scene->ry = scene->hy;
		scene->dist = scene->dis_h;
	}
}

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
