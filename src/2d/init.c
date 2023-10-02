/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:33:32 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/02 17:08:50 by ikaismou         ###   ########.fr       */
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
		printf("haut\n");
		if (data->head_file->map[(data->head_player->posy / 10) - 1][data->head_player->posx / 10] == '1')
		{
			return (0);			
		}
		data->head_player->posy -= 2;
		if (data->head_player->posy % 10 == 0 && data->head_player->posy != data->head_player->startposy)
		{
			data->head_file->map[data->head_player->posy / 10][data->head_player->posx / 10] = 'N';
			data->head_file->map[(data->head_player->posy / 10) + 1][data->head_player->posx / 10] = '0';
		}
	}
	else if (keycode == 65363) // droite
	{
		printf("droite\n");
		if (data->head_file->map[data->head_player->posy / 10][(data->head_player->posx / 10) + 1] == '1')
		{
			return (0);			
		}
		data->head_player->posx += 2;
		if (data->head_player->posx % 10 == 0 && data->head_player->posx != data->head_player->startposx)
		{
			data->head_file->map[data->head_player->posy / 10][data->head_player->posx / 10] = 'N';
			data->head_file->map[data->head_player->posy / 10][(data->head_player->posx / 10) - 1] = '0';
		}
	}
	else if (keycode == 65364) // bas
	{
		printf("bas\n");
		data->head_player->posy += 2;
	}
	else if (keycode == 65361) // gauche
	{
		if (data->head_file->map[data->head_player->posy / 10][(data->head_player->posx / 10) - 1] == '1')
		{
			return (0);			
		}
		data->head_player->posx -= 2;
		if (data->head_player->posx % 10 == 0 && data->head_player->posx != data->head_player->startposx)
		{
			data->head_file->map[data->head_player->posy / 10][data->head_player->posx / 10] = 'N';
			data->head_file->map[data->head_player->posy / 10][(data->head_player->posx / 10) - 1] = '0';
		}
	}
	return (0);
}

static int	random_next_frame(t_data *data)
{
	if (data->head_winmlx->mlx == NULL || data->head_winmlx->mlx_win == NULL || data->head_winmlx->grass == NULL) {
        printf("One of the pointers is NULL\n");
        exit(1);
    }
	mlx_clear_window(data->head_winmlx->mlx, data->head_winmlx->mlx_win);
	int i = 0;
	int j;
	int x = 0;
	int y = 0;
	while(data->head_file->map[i])
	{
		j = 0;
		x = 0;
		while (data->head_file->map[i][j])
		{
			if (data->head_file->map[i][j] == '0')
			{
				mlx_put_image_to_window(data->head_winmlx->mlx, data->head_winmlx->mlx_win,
						data->head_winmlx->grass, x, y);
			}
			else if (data->head_file->map[i][j] == '1')
			{
				mlx_put_image_to_window(data->head_winmlx->mlx, data->head_winmlx->mlx_win,
						data->head_winmlx->wall, x, y);
			}
			else if (data->head_file->map[i][j] == 'N')
			{
				mlx_put_image_to_window(data->head_winmlx->mlx, data->head_winmlx->mlx_win,
						data->head_winmlx->perso, x, y);
			}
			x+=10;
			j++;
		}
		y+=10;
		i++;
	}
		// mlx_put_image_to_window(data->head_winmlx->mlx, data->head_winmlx->mlx_win,
		// 				data->head_winmlx->perso, data->head_player->posx, data->head_player->posy);
	return (0);
}

void load_img(t_winmlx *winmlx)
{
	winmlx->grass = mlx_xpm_file_to_image(winmlx->mlx, "src/xpm/grass.xpm",
			&winmlx->img_width, &winmlx->img_height);
	winmlx->wall = mlx_xpm_file_to_image(winmlx->mlx, "src/xpm/wall.xpm",
			&winmlx->img_width, &winmlx->img_height);
	winmlx->perso = mlx_xpm_file_to_image(winmlx->mlx, "src/xpm/perso.xpm",
			&winmlx->img_width, &winmlx->img_height);
	if (winmlx->grass == NULL) {
        printf("Failed to load image\n");
		perror("Failed to load image");
        exit(1);
    }
    printf("Image loaded successfully\n");
}


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
	data->head_player->posx = get_pos('x', data->head_file->map) * 10;
	data->head_player->posy = get_pos('y', data->head_file->map) * 10;
	data->head_player->startposx = data->head_player->posx;
	data->head_player->startposy = data->head_player->posy;
	printf("%d  %d\n", data->head_player->posy, data->head_player->posx);
	winmlx->mlx = mlx_init();
	winmlx->mlx_win = mlx_new_window(winmlx->mlx, 900, 900, "Cub3d");
	load_img(winmlx);
	mlx_hook(data->head_winmlx->mlx_win, 2, 1L << 0, ft_key_hook, data);
	mlx_loop_hook(winmlx->mlx, random_next_frame, data);
	mlx_loop(winmlx->mlx);
	return (0);
}