/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:46:36 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/15 14:45:40 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	initialize_start_coords(t_data *data, int *startx, int *starty);
void	draw_square_based_on_map(t_data *data, char map_val, int x, int y);

#include <string.h>  // pour utiliser strlen

void drawmap(t_data *data, int i, int j, int x)
{
	int startx;
	int starty;
	int y;

	initialize_start_coords(data, &startx, &starty);
	y = 0;
	i = starty - 1;
	while (++i < starty + 10 && i < data->file->hmap)
	{
		x = 0;
		j = startx - 1;
		while (++j < startx + 10 && j < data->file->wmap && j < (int)strlen(data->file->map[i]))
		{
			draw_square_based_on_map(data, data->file->map[i][j], x, y);
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
	reset_player_position_on_map(data);
}


void	initialize_start_coords(t_data *data, int *startx, int *starty)
{
	*startx = (int)data->player->px / TILE_SIZE - 10 / 2;
	*starty = (int)data->player->py / TILE_SIZE - 10 / 2;
	if (*startx < 0)
		*startx = 0;
	if (*starty < 0)
		*starty = 0;
}

void	draw_square_based_on_map(t_data *data, char map_val, int x, int y)
{
	if (map_val == '1')
		drawsquare(data, H_BLACK, x, y);
	else if (map_val == '0')
		drawsquare(data, H_WHITE, x, y);
	else if (is_player(map_val))
		drawsquare(data, H_PINK, x, y);
}
