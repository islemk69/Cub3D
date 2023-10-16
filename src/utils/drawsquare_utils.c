/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsquare_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:15:20 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/16 16:15:23 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	reset_player_position_on_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->file->map[++i])
	{
		j = -1;
		while (data->file->map[i][++j])
		{
			if (data->file->map[i][j] == 'N')
				data->file->map[i][j] = '0';
		}
	}
	data->file->map[(int)data->player->py / TILE_SIZE] \
		[(int)data->player->px / TILE_SIZE] = 'N';
}

void	drawsquare(t_data *data, int color, int x, int y)
{
	int	i;
	int	j;
	int	save;

	save = x;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		x = save;
		while (j < TILE_SIZE)
		{
			if (j == 0 || j == 31 || i == 31 || i == 0)
				my_mlx_pixel_put(data->winmlx, x, y, H_GREY);
			else
				my_mlx_pixel_put(data->winmlx, x, y, color);
			j++;
			x++;
		}
		y++;
		i++;
	}
}

int	is_player(char p)
{
	if (p == 'N' || p == 'S' || p == 'E' || p == 'W')
		return (1);
	return (0);
}
