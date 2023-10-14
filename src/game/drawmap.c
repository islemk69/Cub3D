/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:46:36 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/14 18:37:04 by ikaismou         ###   ########.fr       */
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

void drawplayer(t_data *data)
{
    int playerSize = 10;
    int squareSize = 30;
    int centerX = (data->file->wmap / 2) * squareSize;  // Centre X de la minimap
    int centerY = (data->file->hmap / 2) * squareSize;  // Centre Y de la minimap

    // Ajoutez les coordonnées de la caméra pour ajuster la position du joueur
    int x = centerX - playerSize / 2 + (data->player->px - (int)data->player->px) * squareSize;
    int y = centerY - playerSize / 2 + (data->player->py - (int)data->player->py) * squareSize;

    int i, j;
    for (i = 0; i < playerSize; i++)
    {
        int saveX = x;
        for (j = 0; j < playerSize; j++)
        {
            my_mlx_pixel_put(data->winmlx, saveX, y, H_YELLOW);
            saveX++;
        }
        y++;
    }
}


int	is_player(char p)
{
	if (p == 'N' || p == 'S' || p == 'E' || p == 'W')
		return (1);
	return (0);
}

void drawmap(t_data *data)
{
	int mapSize = 10;
	int squareSize = 30;
    int startX = (int)data->player->px / squareSize - mapSize / 2;
    int startY = (int)data->player->py / squareSize - mapSize / 2;

    if (startX < 0)
        startX = 0;
    if (startY < 0)
        startY = 0;

    int i, j, x, y;
    y = 0;
    for (i = startY; i < startY + mapSize && i < data->file->hmap; i++)
    {
        x = 0;
        for (j = startX; j < startX + mapSize && j < data->file->wmap; j++)
        {
            if (data->file->map[i][j] == '1')
                drawsquare(data, H_BLACK, x, y);
            else if (data->file->map[i][j] == '0')
                drawsquare(data, H_WHITE, x, y);
            else if (is_player(data->file->map[i][j]))
               	drawsquare(data, H_PINK, x, y);
            x += squareSize;
        }
        y += squareSize;
    }
    reset_player_position_on_map(data);
	drawplayer(data);
}