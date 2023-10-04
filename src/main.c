/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:41:21 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/04 14:00:00 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"



int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_putstr_fd("Error Number of Args\n", 2), 1);
	data.head_file = malloc(sizeof(t_file));
	if (parsing(argv[1], &data))
		return (free(data.head_file), 1);
	data.head_winmlx = malloc(sizeof(t_winmlx));
	int i = 0;
	while (data.head_file->map[i])
	{
		printf("%s\n", data.head_file->map[i]);
		i++;
	} 	
	ft_init(data.head_winmlx, &data);
	// ft_free_tab(data.head_file->map);
	// free(data.head_file);
	// free(data.head_winmlx);
}


// typedef struct  s_test
// {
//     int x;
//     int y;
//     int angle;
// }               t_test;

// void rotate_player(t_test *player, int direction)
// {
//     player->angle += direction * 5;
//     if (player->angle > 360)
//         player->angle -= 360;
//     else if (player->angle < 0)
//         player->angle += 360;
// }


// int key_hook(int keycode, t_test *player)
// {
//     if (keycode == 123) // Left arrow key
//         rotate_player(player, -1);
//     else if (keycode == 124) // Right arrow key
//         rotate_player(player, 1);
//     return (0);
// }



// int draw_player(t_test *player, void *mlx, void *win)
// {
// 	int x = player->x + cos(player->angle * M_PI / 180) * 10;
// 	int y = player->y + sin(player->angle * M_PI / 180) * 10;
// 	mlx_pixel_put(mlx, win, x, y, 0x00FF0000);
// 	return (0);
// }

// int main(void)
// {
//     t_test player;
//     void *mlx;
//     void *win;

// 	player.x = 200;
// 	player.y = 100;
// 	player.angle = 20;
//     mlx = mlx_init();
// 	if (mlx == NULL) {
//    		 printf("Failed to initialize MiniLibX\n");
// 		return 1;
// 	}
//     win = mlx_new_window(mlx, 800, 600, "Player Rotation");
// 	if (win == NULL) {
// 		printf("Failed to create window\n");
// 		return 1;
// 	}
//     mlx_hook(win, 2, 1L << 0, key_hook, &player);
//     mlx_loop_hook(mlx, draw_player, &player);
//     mlx_loop(mlx);
// }