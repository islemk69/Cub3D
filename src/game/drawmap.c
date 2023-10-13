/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:46:36 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/13 15:48:44 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void reset_player_position_on_map(t_data *data)
{
    int i = 0;
    int j = 0;

    while (data->file->map[i])
    {
        j = 0;
        while (data->file->map[i][j])
        {
            if (data->file->map[i][j] == 'N')
                data->file->map[i][j] = '0';
            j++;
        }
        i++;
    }
    data->file->map[(int)data->player->py / 30][(int)data->player->px / 30] = 'N';
}


void drawsquare(t_data *data, int color, int x, int y)
{
	int i = 0;
	int j;
	int save = x;
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

void drawplayer(t_data *data, int posx, int posy) {
    int i = 0;
    int j;

    int squareSize = 10;  // Taille du carré du joueur
    int halfSize = squareSize / 2;  // Demi-taille pour le centrage

    int saveposx = posx - halfSize;  // Position initiale ajustée au centre horizontalement
    int saveposy = posy - halfSize;  // Position initiale ajustée au centre verticalement

    while (i < squareSize) {
        j = 0;
        posx = saveposx;
        while (j < squareSize) {
            my_mlx_pixel_put(data->winmlx, posx, saveposy + i, H_YELLOW);
            j++;
            posx++;
        }
        posy++;
        i++;
    }
}

void drawmap(t_data *data)
{
    int x = 0;
	int y = 0;
    int i = 0;
	int j;
    while(data->file->map[i])
	{
		j = 0;
		x = 0;
		while (data->file->map[i][j])
		{
			if (data->file->map[i][j] == '1')
				drawsquare(data, H_BLACK, x, y);
			else if (data->file->map[i][j] == '0')
				drawsquare(data, H_WHITE, x, y);
			else if (data->file->map[i][j] == 'N')
				drawsquare(data, H_PINK, x, y);
			x+=30;
			j++;
		}
		y+=30;
		i++;
	}
	reset_player_position_on_map(data);
    drawplayer(data, data->player->px, data->player->py);
}