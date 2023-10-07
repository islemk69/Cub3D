/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:33:32 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/07 13:02:02 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    my_mlx_pixel_put(t_winmlx *draw, int x, int y, int color)
{
    if ((x >= 0 && x < 900) && (y >= 0 && y < 900))
        ((int *)draw->addr)[y * (draw->line_length >> 2) + x] = color;
}

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
                data->head_file->map[i][j] = '0';
            j++;
        }
        i++;
    }
    data->head_file->map[data->head_player->posy / 30][data->head_player->posx / 30] = 'N';
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

bool is_collision(t_data *data, int newX, int newY)
{
    int mapX = newX / 30;
    int mapY = newY / 30;

    // Vérifier si la position est à l'intérieur d'une cellule de mur
    if (data->head_file->map[mapY][mapX] == '1')
        return true;

    return false;
}

int ft_key_hook(int keycode, t_data *data)
{
    if (keycode == 65362) // haut
    {
<<<<<<< HEAD
        float moveX = 2 * cos(data->head_player->angle * M_PI / 180);
        float moveY = 2 * sin(data->head_player->angle * M_PI / 180);
=======
        float moveX = 5 * cos(data->head_player->angle * M_PI / 180);
        float moveY = 5 * sin(data->head_player->angle * M_PI / 180);
>>>>>>> 6d8fb609f7bef287cf0be388f289f21e6cbaa3a1

        int newX = data->head_player->posx + moveX;
        int newY = data->head_player->posy;

        // Vérifiez d'abord le mouvement en X
        if (!is_collision(data, newX, newY))
            data->head_player->posx = newX;

        newX = data->head_player->posx;  // Mettez à jour la valeur de newX après le mouvement
        newY = data->head_player->posy + moveY;

        // Vérifiez ensuite le mouvement en Y
        if (!is_collision(data, newX, newY))
            data->head_player->posy = newY;

<<<<<<< HEAD
        printf("posx = %d\n", data->head_player->posx);
        printf("posy = %d\n", data->head_player->posy);
=======
    }
    else if (keycode == 65364) // bas
    {
        float moveX = -6 * cos(data->head_player->angle * M_PI / 180);
        float moveY = -6 * sin(data->head_player->angle * M_PI / 180);

        int newX = data->head_player->posx + moveX;
        int newY = data->head_player->posy;

        if (!is_collision(data, newX, newY))
            data->head_player->posx = newX;

        newX = data->head_player->posx;
        newY = data->head_player->posy + moveY;

        if (!is_collision(data, newX, newY))
            data->head_player->posy = newY;
>>>>>>> 6d8fb609f7bef287cf0be388f289f21e6cbaa3a1
    }
    else if (keycode == 65364) // bas
    {
        float moveX = -2 * cos(data->head_player->angle * M_PI / 180);
        float moveY = -2 * sin(data->head_player->angle * M_PI / 180);

        int newX = data->head_player->posx + moveX;
        int newY = data->head_player->posy;

        if (!is_collision(data, newX, newY))
            data->head_player->posx = newX;

        newX = data->head_player->posx;
        newY = data->head_player->posy + moveY;

        if (!is_collision(data, newX, newY))
            data->head_player->posy = newY;
    }
	else if (keycode == 65363) // droite
		rotate_player(data, 1);
<<<<<<< HEAD

	}
//	else if (keycode == 65364) // bas
//	{
//		data->head_player->posy += 2;
//	}
=======
>>>>>>> 6d8fb609f7bef287cf0be388f289f21e6cbaa3a1
	else if (keycode == 65361) // gauche
		rotate_player(data, -1);
	return (0);
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
            my_mlx_pixel_put(data->head_winmlx, posx, saveposy + i, H_YELLOW);
            j++;
            posx++;
        }
        posy++;
        i++;
    }
}


void draw_line(t_data *data, int x1, int y1, int x2, int y2, int color) {
    // Algorithme de tracé de ligne (Bresenham)
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        my_mlx_pixel_put(data->head_winmlx, x1, y1, color);

        if (x1 == x2 && y1 == y2) {
            break;
        }

        int err2 = 2 * err;
        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

<<<<<<< HEAD
void draw_part_of_circle(t_data *data, int x, int y, float angle)
{
    const int RADIUS = 10;
    const float ARC_ANGLE = M_PI / 3;

    float startAngle = angle + ARC_ANGLE / 2;
    float endAngle = angle - ARC_ANGLE / 2;

    int tipX = x + RADIUS * cos(angle);
    int tipY = y + RADIUS * sin(angle);
    draw_line(data, x, y, tipX, tipY, H_BLACK);

    for (float currentAngle = endAngle; currentAngle <= startAngle; currentAngle += 0.01)
    {
        for (int r = 0; r <= RADIUS; r++)
        {
            int pointX = x + r * cos(currentAngle);
            int pointY = y + r * sin(currentAngle);
            my_mlx_pixel_put(data->head_winmlx, pointX, pointY, H_BLACK);
        }
    }

    int startX = x + RADIUS * cos(startAngle);
    int startY = y + RADIUS * sin(startAngle);
    draw_line(data, x, y, startX, startY, H_BLACK);

    int endX = x + RADIUS * cos(endAngle);
    int endY = y + RADIUS * sin(endAngle);
    draw_line(data, x, y, endX, endY, H_BLACK);
=======

void cast_rays(t_data *data) {
    int num_rays = 30;  // Nombre de rayons à lancer
    float fov = 60.0;   // Champ de vision en degrés
    float angle_increment = fov / num_rays;

    for (int i = 0; i < num_rays; i++) {
        // Calcule l'angle du rayon en fonction du champ de vision et de l'itération
        float ray_angle = data->head_player->angle - (fov / 2) + i * angle_increment;

        // Convertit l'angle en radians
        float ray_angle_rad = ray_angle * M_PI / 180.0;

        // Initialise les coordonnées du rayon à la position du joueur
        float ray_x = data->head_player->posx;
        float ray_y = data->head_player->posy;

        // Initialise les coordonnées du point d'impact potentiel
        float hit_x = ray_x;
        float hit_y = ray_y;

        // Avance le rayon jusqu'à ce qu'il atteigne une nouvelle case
		while (1) {
			// Obtient les indices de la case actuelle dans la grille
			int map_x = (int)(hit_x / 30);
			int map_y = (int)(hit_y / 30);

			// Vérifie si le rayon est sorti de la grille

			// Vérifie si la case actuelle est un mur
			if (data->head_file->map[map_y][map_x] == '1') {
				// Dessine une ligne du joueur au point de collision avec le mur
				draw_line(data, data->head_player->posx, data->head_player->posy, (int)hit_x, (int)hit_y, H_RED);
				break;  // Sort de la boucle interne
			}

			hit_x += cos(ray_angle_rad) * 0.1;
			hit_y += sin(ray_angle_rad) * 0.1;
		}
    }
>>>>>>> 6d8fb609f7bef287cf0be388f289f21e6cbaa3a1
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
				my_mlx_pixel_put(data->head_winmlx, x, y, H_GREY);
			else
				my_mlx_pixel_put(data->head_winmlx, x, y, color);
			j++;
			x++;
		}
		y++;
		i++;
	}
}

void drawmap(t_data *data)
{
    int x = 0;
	int y = 0;
    int i = 0;
	int j;
    while(data->head_file->map[i])
	{
		j = 0;
		x = 0;
		while (data->head_file->map[i][j])
		{
			if (data->head_file->map[i][j] == '1')
				drawsquare(data, H_BLACK, x, y);
			else if (data->head_file->map[i][j] == '0')
				drawsquare(data, H_WHITE, x, y);
			else if (data->head_file->map[i][j] == 'N')
				drawsquare(data, H_PINK, x, y);
			x+=30;
			j++;
		}
		y+=30;
		i++;
	}
<<<<<<< HEAD
    draw_part_of_circle(data, data->head_player->posx, data->head_player->posy, data->head_player->angle * M_PI / 180);
=======
}

static int	random_next_frame(t_data *data)
{

    reset_player_position_on_map(data);
	data->head_winmlx->img = mlx_new_image(data->head_winmlx->mlx, 1920, 1080);
	data->head_winmlx->addr = mlx_get_data_addr(data->head_winmlx->img, &data->head_winmlx->bits_per_pixel, &data->head_winmlx->line_length, &data->head_winmlx->endian);
    drawmap(data);
	drawplayer(data, data->head_player->posx, data->head_player->posy);
	cast_rays(data);
>>>>>>> 6d8fb609f7bef287cf0be388f289f21e6cbaa3a1
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
	data->head_player->angle = -90;
    data->head_player->posx = (get_pos(1, data->head_file->map) * 30) + 15;
	data->head_player->posy = (get_pos(0, data->head_file->map) * 30) + 15;
	winmlx->mlx = mlx_init();
	winmlx->mlx_win = mlx_new_window(winmlx->mlx, 1920, 1080, "Cub3d");
	mlx_hook(data->head_winmlx->mlx_win, 2, 1L << 0, ft_key_hook, data);
	mlx_loop_hook(winmlx->mlx, random_next_frame, data);
	mlx_loop(winmlx->mlx);
	return (0);
}