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
	data->file->map[(int)data->player->py / 32] \
		[(int)data->player->px / 32] = 'N';
}

void	drawsquare(t_data *data, int color, int x, int y)
{
	int	i;
	int	j;
	int	save;

	save = x;
	i = 0;
	while (i < 32)
	{
		j = 0;
		x = save;
		while (j < 32)
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

void	drawmap(t_data *data, int i, int j, int x)
{
	int	startx;
	int	starty;
	int	y;

	startx = (int)data->player->px / 32 - 10 / 2;
	starty = (int)data->player->py / 32 - 10 / 2;
	if (startx < 0)
		startx = 0;
	if (starty < 0)
		starty = 0;
	y = 0;
	i = starty - 1;
	while (++i < starty + 10 && i < data->file->hmap)
	{
		x = 0;
		j = startx - 1;
		while (++j < startx + 10 && j < data->file->wmap)
		{
			if (data->file->map[i][j] == '1')
				drawsquare(data, H_BLACK, x, y);
			else if (data->file->map[i][j] == '0')
				drawsquare(data, H_WHITE, x, y);
			else if (is_player(data->file->map[i][j]))
				drawsquare(data, H_PINK, x, y);
			x += 32;
		}
		y += 32;
	}
	reset_player_position_on_map(data);
}
