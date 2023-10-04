/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:33:32 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/04 14:13:03 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void reset_player_position_on_map(t_data *data)
{
    int i = 0;
    int j = 0;

    while (data->head_file->map[i])
    {
        j = 0;
        while (data->head_file->map[i][j])
        {
            if (data->head_file->map[i][j] == 'N')
                data->head_file->map[i][j] = '0'; // Réinitialisez la position précédente du joueur à une case vide
            j++;
        }
        i++;
    }

    // Mettez à jour la nouvelle position du joueur sur la carte
    data->head_file->map[data->head_player->posy / 10][data->head_player->posx / 10] = 'N';
}

void rotate_player(t_data *data, int direction)
{
    data->head_player->angle += direction * 5;
    if (data->head_player->angle > 360)
        data->head_player->angle -= 360;
    else if (data->head_player->angle < 0)
	{
        data->head_player->angle += 360;
	}
	printf("OH%d\n", data->head_player->angle);
}

int ft_key_hook(int keycode, t_data *data)
{
	(void)data;
	printf("%d\n", keycode);
	if (keycode == 65307)
	{
		printf("salut");
	}
    else if (keycode == 65362) // haut
    {
        float moveX = 2 * cos(data->head_player->angle * M_PI / 180);
        float moveY = 2 * sin(data->head_player->angle * M_PI / 180);
        data->head_player->posx += moveX;
        data->head_player->posy += moveY;
        printf("posx = %d\n", data->head_player->posx);
        printf("posy = %d\n", data->head_player->posy);

//        if ((data->head_player->posx % 10 == 0 && data->head_player->posx != data->head_player->startposx) ||
//            (data->head_player->posy % 10 == 0 && data->head_player->posy != data->head_player->startposy))
//        {
//            printf("MOVE !\n");
//            data->head_file->map[data->head_player->posy / 10][data->head_player->posx / 10] = 'N';
//
//            if (data->head_file->map[data->head_player->posy / 10][data->head_player->posx / 10] != '1')
//                data->head_file->map[data->head_player->posy / 10][data->head_player->posx / 10] = '0';
//        }
    }
	else if (keycode == 65363) // droite
	{
		rotate_player(data, 1);

	}
	else if (keycode == 65364) // bas
	{
		data->head_player->posy += 2;
//		if (data->head_player->posy % 10 == 0 && data->head_player->posy != data->head_player->startposy)
//		{
//			printf("MOVE !\n");
//			data->head_file->map[data->head_player->posy / 10][data->head_player->posx / 10] = 'N';
//			if (data->head_file->map[(data->head_player->posy / 10) - 1][data->head_player->posx / 10] != '1')
//				data->head_file->map[(data->head_player->posy / 10) - 1][data->head_player->posx / 10] = '0';
//		}
	}
	else if (keycode == 65361) // gauche
	{
		rotate_player(data, -1);

	}
	printf("%d\n", data->head_player->posy);
	printf("%d\n", data->head_player->posx);
	return (0);
}

void    my_mlx_pixel_put(t_winmlx *draw, int x, int y, int color)
{
    if ((x >= 0 && x < 900) && (y >= 0 && y < 900))
        ((int *)draw->addr)[y * (draw->line_length >> 2) + x] = color;
}

void drawsquare(t_data *data, int color, int x, int y)
{
	int i = 0;
	int j;
	int save = x;
	while (i < 10)
	{
		j = 0;
		x = save;
		while (j < 10)
		{
			my_mlx_pixel_put(data->head_winmlx, x, y, color);
			j++;
			x++;
		}
		y++;
		i++;
	}
}

int only_space(char *str)
{
	while (*str)
	{
		if (*str != 'x')
			return (0);
		str++;
	}
	return (1);
}

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;

    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1)
    {
        my_mlx_pixel_put(data->head_winmlx, x0, y0, color);  // Dessinez le pixel à cette position

        if (x0 == x1 && y0 == y1)
            break;

        e2 = err;

        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_arrow(t_data *data, int x, int y, float angle)
{
    int tipX = x + (10 * cos(angle));  // Calculez la position de la pointe de la flèche
    int tipY = y + (10 * sin(angle));

    int wing1X = tipX - (5 * cos(angle + M_PI / 4));  // Calculez la position de la première aile
    int wing1Y = tipY - (5 * sin(angle + M_PI / 4));

    int wing2X = tipX - (5 * cos(angle - M_PI / 4));  // Calculez la position de la deuxième aile
    int wing2Y = tipY - (5 * sin(angle - M_PI / 4));

    draw_line(data, x, y, tipX, tipY, H_BLACK);  // Dessinez la tige
    draw_line(data, tipX, tipY, wing1X, wing1Y, H_BLACK);  // Dessinez la première aile
    draw_line(data, tipX, tipY, wing2X, wing2Y, H_BLACK);  // Dessinez la deuxième aile
}



static int	random_next_frame(t_data *data)
{
	int i = 0;
	int j;
	int x = 0;
	int y = 0;
    reset_player_position_on_map(data);
	data->head_winmlx->img = mlx_new_image(data->head_winmlx->mlx, 900, 900);
	data->head_winmlx->addr = mlx_get_data_addr(data->head_winmlx->img, &data->head_winmlx->bits_per_pixel, &data->head_winmlx->line_length, &data->head_winmlx->endian);
	// mlx_clear_window(data->head_winmlx->mlx, data->head_winmlx->mlx_win);
	while(data->head_file->map[i])
	{
		j = 0;
		x = 0;
		while (data->head_file->map[i][j])
		{
			if (data->head_file->map[i][j] == '1')
				drawsquare(data, H_RED, x, y);
			else if (data->head_file->map[i][j] == '0')
				drawsquare(data, H_GREEN, x, y);
			else if (data->head_file->map[i][j] == 'N')
			{
				drawsquare(data, H_PINK, x, y);
				my_mlx_pixel_put(data->head_winmlx, data->head_player->posx , data->head_player->posy, H_BLACK);
			}
			x+=10;
			j++;
		}
		y+=10;
		i++;
	}
//	int u = data->head_player->posx + cos(data->head_player->angle * M_PI / 180) * 10;
//	int v = data->head_player->posy + sin(data->head_player->angle * M_PI / 180) * 10;
//	my_mlx_pixel_put(data->head_winmlx, u , v, H_BLACK);
    draw_arrow(data, data->head_player->posx, data->head_player->posy, data->head_player->angle * M_PI / 180);
	mlx_put_image_to_window(data->head_winmlx->mlx, data->head_winmlx->mlx_win, data->head_winmlx->img, 0, 0);
	mlx_destroy_image(data->head_winmlx->mlx, data->head_winmlx->img);
	return (0);
}


int get_pos(int mod, char **map)
{
	int i = 0;
	int j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W')
			{
				if (mod)
					return (j);
				else
					return (i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int ft_init(t_winmlx *winmlx, t_data *data)
{
	(void)data;
	data->head_player = malloc(sizeof(t_player));
	data->head_player->angle = 400;
	data->head_player->posx = 10;
	data->head_player->posy = 10;
    data->head_player->posx = get_pos(1, data->head_file->map) * 10;
	data->head_player->posy = get_pos(0, data->head_file->map) * 10;
	data->head_player->startposx = data->head_player->posx;
	data->head_player->startposy = data->head_player->posy;
	winmlx->mlx = mlx_init();
	winmlx->mlx_win = mlx_new_window(winmlx->mlx, 900, 900, "Cub3d");
	// load_img(winmlx);
	mlx_hook(data->head_winmlx->mlx_win, 2, 1L << 0, ft_key_hook, data);
	mlx_loop_hook(winmlx->mlx, random_next_frame, data);
	mlx_loop(winmlx->mlx);
	return (0);
}