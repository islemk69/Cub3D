/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:33:32 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/03 16:19:23 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		data->head_player->posy -= 2;
		if (data->head_player->posy % 10 == 0 && data->head_player->posy != data->head_player->startposy)
		{
			printf("MOVE !\n");
			data->head_file->map[data->head_player->posy / 10][data->head_player->posx / 10] = 'N';
			if (data->head_file->map[(data->head_player->posy / 10) + 1][data->head_player->posx / 10] != '1')
				data->head_file->map[(data->head_player->posy / 10) + 1][data->head_player->posx / 10] = '0';
		}
	}
	else if (keycode == 65363) // droite
	{
		data->head_player->posx += 2;
		if (data->head_player->posx % 10 == 0 && data->head_player->posx != data->head_player->startposx)
		{
			printf("MOVE !\n");
			data->head_file->map[data->head_player->posy / 10][data->head_player->posx / 10] = 'N';
			if (data->head_file->map[data->head_player->posy / 10][(data->head_player->posx / 10) - 1] != '1')
			data->head_file->map[data->head_player->posy / 10][(data->head_player->posx / 10) - 1] = '0';
		}
	}
	else if (keycode == 65364) // bas
	{
		data->head_player->posy += 2;
		if (data->head_player->posy % 10 == 0 && data->head_player->posy != data->head_player->startposy)
		{
			printf("MOVE !\n");
			data->head_file->map[data->head_player->posy / 10][data->head_player->posx / 10] = 'N';
			if (data->head_file->map[(data->head_player->posy / 10) - 1][data->head_player->posx / 10] != '1')
				data->head_file->map[(data->head_player->posy / 10) - 1][data->head_player->posx / 10] = '0';
		}
	}
	else if (keycode == 65361) // gauche
	{
		data->head_player->posx -= 2;
		if (data->head_player->posx % 10 == 0 && data->head_player->posx != data->head_player->startposx)
		{
			printf("MOVE !\n");
			data->head_file->map[data->head_player->posy / 10][data->head_player->posx / 10] = 'N';
			if (data->head_file->map[data->head_player->posy / 10][(data->head_player->posx / 10) + 1] != '1')
				data->head_file->map[data->head_player->posy / 10][(data->head_player->posx / 10) + 1] = '0';
		}
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

static int	random_next_frame(t_data *data)
{
// 	// if (data->head_winmlx->mlx == NULL || data->head_winmlx->mlx_win == NULL || data->head_winmlx->grass == NULL) {
//     //     printf("One of the pointers is NULL\n");
//     //     exit(1);
//     // }
	
	int i = 0;
	int j;
	int x = 0;
	int y = 0;
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
	mlx_put_image_to_window(data->head_winmlx->mlx, data->head_winmlx->mlx_win, data->head_winmlx->img, 0, 0);
	mlx_destroy_image(data->head_winmlx->mlx, data->head_winmlx->img);
	return (0);
}

// void load_img(t_winmlx *winmlx)
// {
// 	winmlx->grass = mlx_xpm_file_to_image(winmlx->mlx, "src/xpm/grass.xpm",
// 			&winmlx->img_width, &winmlx->img_height);
// 	winmlx->wall = mlx_xpm_file_to_image(winmlx->mlx, "src/xpm/wall.xpm",
// 			&winmlx->img_width, &winmlx->img_height);
// 	winmlx->perso = mlx_xpm_file_to_image(winmlx->mlx, "src/xpm/perso.xpm",
// 			&winmlx->img_width, &winmlx->img_height);
// 	if (winmlx->grass == NULL) {
//         printf("Failed to load image\n");
// 		perror("Failed to load image");
//         exit(1);
//     }
//     printf("Image loaded successfully\n");
// }


int get_pos(char c, char **map)
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
				if (c == 'x')
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
	data->head_player->posx = get_pos('x', data->head_file->map) * 10;
	data->head_player->posy = get_pos('y', data->head_file->map) * 10;
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