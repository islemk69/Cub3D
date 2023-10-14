/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:46:36 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/14 17:43:49 by ikaismou         ###   ########.fr       */
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
	data->file->map[(int)data->player->py / 30] \
		[(int)data->player->px / 30] = 'N';
}

void	drawsquare(t_data *data, int color, int x, int y)
{
	int	i;
	int	j;
	int	save;

	save = x;
	i = 0;
	while (i < 30)
	{
		j = 0;
		x = save;
		while (j < 30)
		{
			if (j == 0 || j == 29 || i == 29 || i == 0)
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

void	drawplayer(t_data *data, int posx, int posy)
{
	int	i;
	int	j;
	int	saveposx;
	int	saveposy;

	saveposx = posx - 10 / 2;
	saveposy = posy - 10 / 2;
	i = -1;
	while (++i < 10)
	{
		j = -1;
		posx = saveposx;
		while (++j < 10)
		{
			my_mlx_pixel_put(data->winmlx, posx, saveposy + i, H_YELLOW);
			posx++;
		}
		posy++;
	}
}

int	is_player(char p)
{
	if (p == 'N' || p == 'S' || p == 'E' || p == 'W')
		return (1);
	return (0);
}

void	drawmap(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (data->file->map[++i])
	{
		j = -1;
		x = 0;
		while (data->file->map[i][++j])
		{
			if (data->file->map[i][j] == '1')
				drawsquare(data, H_BLACK, x, y);
			else if (data->file->map[i][j] == '0')
				drawsquare(data, H_WHITE, x, y);
			else if (is_player(data->file->map[i][j]))
				drawsquare(data, H_PINK, x, y);
			x += 30;
		}
		y += 30;
	}
	reset_player_position_on_map(data);
	drawplayer(data, data->player->px, data->player->py);
}
