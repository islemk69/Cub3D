/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
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

float	get_texture_scale(t_texture *texture)
{
	return ((float) texture->width / 32.0);
}

void	define_which_texture(t_data *data, t_texture **texture, float ra)
{
	if (data->scene->h_redded)
	{
		if (ra >= 0 && ra < PI)
			*texture = data->stex;
		else
			*texture = data->ntex;
	}
	else
	{
		if (ra >= PI / 2 && ra < 3 * PI / 2)
			*texture = data->wtex;
		else
			*texture = data->etex;
	}
}
