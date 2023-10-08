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
    data->head_file->map[(int)data->head_player->py / 30][(int)data->head_player->px / 30] = 'N';
}

// void rotate_player(t_data *data, int direction)
// {
//     data->head_player->angle += direction * 5;
//     if (data->head_player->angle > 360)
//         data->head_player->angle -= 360;
//     else if (data->head_player->angle < 0)
// 	{
//         data->head_player->angle += 360;
// 	}
// 	printf("OH%d\n", data->head_player->angle);
// }

 bool is_collision(t_data *data, int newX, int newY)
 {
     int map_posX = newX / 30;
     int map_posY = newY / 30;

     // Vérifier si la position est à l'intérieur d'une cellule de mur
     if (data->head_file->map[map_posY][map_posX] == '1')
         return true;

     return false;
 }


// void cast_rays(t_data *data) {
//     int num_rays = 30;  // Nombre de rayons à lancer
//     float fov = 60.0;   // Champ de vision en degrés
//     float angle_increment = fov / num_rays;

//     for (int i = 0; i < num_rays; i++) {
//         // Calcule l'angle du rayon en fonction du champ de vision et de l'itération
//         float ray_angle = data->head_player->angle - (fov / 2) + i * angle_increment;

//         // Convertit l'angle en radians
//         float ray_angle_rad = ray_angle * M_PI / 180.0;

//         // Initialise les coordonnées du rayon à la position du joueur
//         float ray_x = data->head_player->posx;
//         float ray_y = data->head_player->posy;

//         // Initialise les coordonnées du point d'impact potentiel
//         float hit_x = ray_x;
//         float hit_y = ray_y;

//         // Avance le rayon jusqu'à ce qu'il atteigne une nouvelle case
// 		while (1) {
// 			// Obtient les indices de la case actuelle dans la grille
// 			int map_x = (int)(hit_x / 30);
// 			int map_y = (int)(hit_y / 30);

// 			// Vérifie si le rayon est sorti de la grille

// 			// Vérifie si la case actuelle est un mur
// 			if (data->head_file->map[map_y][map_x] == '1') {
// 				// Dessine une ligne du joueur au point de collision avec le mur
// 				draw_line(data, data->head_player->posx, data->head_player->posy, (int)hit_x, (int)hit_y, H_RED);
// 				break;  // Sort de la boucle interne
// 			}

// 			hit_x += cos(ray_angle_rad) * 0.1;
// 			hit_y += sin(ray_angle_rad) * 0.1;
// 		}
//     }
// }


//int ft_key_hook(int keycode, t_data *data)
//{
//    if (keycode == 65362) // haut
//    {
//        data->head_player->px += data->head_player->pdx;
//        data->head_player->py += data->head_player->pdy;
//    }
//    else if (keycode == 65364) // bas
//    {
//        data->head_player->px -= data->head_player->pdx;
//        data->head_player->py -= data->head_player->pdy;
//    }
//	else if (keycode == 65363) // droite
//    {
//        data->head_player->pa += 0.1;
//        if (data->head_player->pa > 2 * PI)
//            data->head_player->pa -= 2 * PI;
//        data->head_player->pdx = cos(data->head_player->pa) * 5;
//        data->head_player->pdy = sin(data->head_player->pa) * 5;
//    }
//	else if (keycode == 65361) // gauche
//    {
//        data->head_player->pa -= 0.1;
//        if (data->head_player->pa < 0)
//            data->head_player->pa += 2 * PI;
//        data->head_player->pdx = cos(data->head_player->pa) * 5;
//        data->head_player->pdy = sin(data->head_player->pa) * 5;
//    }
//	return (0);
//}

int ft_key_hook(int keycode, t_data *data)
{
    float moveX, moveY;
    int newX, newY;

    if (keycode == 65362) // haut
    {
        moveX = data->head_player->pdx;
        moveY = data->head_player->pdy;

        newX = data->head_player->px + moveX;
        newY = data->head_player->py;

        if (!is_collision(data, newX, newY))
            data->head_player->px = newX;

        newX = data->head_player->px;
        newY = data->head_player->py + moveY;

        if (!is_collision(data, newX, newY))
            data->head_player->py = newY;
    }
    else if (keycode == 65364) // bas
    {
        moveX = -data->head_player->pdx;
        moveY = -data->head_player->pdy;

        newX = data->head_player->px + moveX;
        newY = data->head_player->py;

        if (!is_collision(data, newX, newY))
            data->head_player->px = newX;

        newX = data->head_player->px;
        newY = data->head_player->py + moveY;

        if (!is_collision(data, newX, newY))
            data->head_player->py = newY;
    }
    else if (keycode == 65363) // droite
    {
        data->head_player->pa += 0.1;
        if (data->head_player->pa > 2 * M_PI)
            data->head_player->pa -= 2 * M_PI;
        data->head_player->pdx = cos(data->head_player->pa) * 5;
        data->head_player->pdy = sin(data->head_player->pa) * 5;
    }
    else if (keycode == 65361) // gauche
    {
        data->head_player->pa -= 0.1;
        if (data->head_player->pa < 0)
            data->head_player->pa += 2 * M_PI;
        data->head_player->pdx = cos(data->head_player->pa) * 5;
        data->head_player->pdy = sin(data->head_player->pa) * 5;
    }
    return (0);
}


void draw_line(t_data *data, int x1, int y1, int x2, int y2, int color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps;

    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    } else {
        steps = abs(dy);
    }

    float xIncrement = (float)dx / (float)steps;
    float yIncrement = (float)dy / (float)steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        my_mlx_pixel_put(data->head_winmlx, round(x), round(y), color);
        x += xIncrement;
        y += yIncrement;
    }
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


float dist(float ax, float ay, float bx, float by, float ang)
{
    (void)ang;
    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void drawRays2D(t_data *data)
{
    int dof, mx, my, r;
    float rx, ry, ra, xo, yo;
    ra = data->head_player->pa - DR * 30;
    if (ra < 0)
        ra += 2 * PI;
    if (ra > 2 * PI)
        ra -= 2 * PI;
    // check horizontal lines
    rx = 0;
    ry = 0;
    xo = 0;
    yo = 0;


    for (r = 0; r < 60; r++)
    {
        dof = 0;
        float disH = 1000000, hx=data->head_player->px, hy=data->head_player->py;
        float aTan = -1 / tan(ra);
        if (ra > PI) // looking up
        {
            ry = (float)(((int)data->head_player->py / 30) * 30) - 0.0001;
            rx = (data->head_player->py - ry) * aTan + data->head_player->px;
            yo = -30;
            xo = -yo * aTan;
        }
        if (ra < PI) // looking down
        {
            ry = (float)(((int)data->head_player->py / 30) * 30) + 30;
            rx = (data->head_player->py - ry) * aTan + data->head_player->px;
            yo = 30;
            xo = -yo * aTan;
        }
        if (ra == 0 || ra == PI) //looking straight left or right
        {
            rx = data->head_player->px;
            ry = data->head_player->py;
            dof = 8;
        }

        while (dof < 8)
        {
            mx = (int)(rx / 30);
            my = (int)(ry / 30);

            // Check if my and mx are within the bounds of the map
            if (my >= 0 && my < mapY && mx >= 0 && mx < mapX && data->head_file->map[my][mx] == '1')
            {
                hx = rx;
                hy = ry;
                disH = dist(data->head_player->px, data->head_player->px, hx, hy, ra);
                dof = 8;
                
            }
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }

        //check vertical lines
        dof = 0;
        float disV = 1000000, vx=data->head_player->px, vy=data->head_player->py;
        float nTan = -tan(ra);

        if (ra > P2 && ra < P3) // looking left
        {
            rx = (float)(((int)data->head_player->px / 30) * 30) - 0.0001;
            ry = (data->head_player->px - rx) * nTan + data->head_player->py;
            xo = -30;
            yo = -xo * nTan;
        }
        if (ra < P2 || ra > P3) // looking right
        {
            rx = (float)(((int)data->head_player->px / 30) * 30) + 30;
            ry = (data->head_player->px - rx) * nTan + data->head_player->py;
            xo = 30;
            yo = -xo * nTan;
        }
        if (ra == 0 || ra == PI) // looking straight up and down 
        {
            rx = data->head_player->px;
            ry = data->head_player->py;
            dof = 8;
        }

        while (dof < 8)
        {
            mx = (int)(rx / 30);
            my = (int)(ry / 30);

            // Check if my and mx are within the bounds of the map
            if (my >= 0 && my < mapY && mx >= 0 && mx < mapX && data->head_file->map[my][mx] == '1')
            {
                vx = rx;
                vy = ry;
                disV = dist(data->head_player->px, data->head_player->px, vx, vy, ra);
                dof = 8;
            }
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        if (disV < disH){rx = vx; ry = vy;};
        if (disH < disV){rx = hx; ry = hy;};
        // Dessiner le rayon
        int lineEndX = rx; // Utiliser les coordonnées finales
        int lineEndY = ry;
        draw_line(data, data->head_player->px, data->head_player->py, lineEndX, lineEndY, H_RED);
        ra += DR;
        if (ra < 0)
            ra += 2 * PI;
        if (ra > 2 * PI)
            ra -= 2 * PI;
        // Dessiner le rayon

    }

}



static int	random_next_frame(t_data *data)
{


	data->head_winmlx->img = mlx_new_image(data->head_winmlx->mlx, 1920, 1080);
	data->head_winmlx->addr = mlx_get_data_addr(data->head_winmlx->img, &data->head_winmlx->bits_per_pixel, &data->head_winmlx->line_length, &data->head_winmlx->endian);
        reset_player_position_on_map(data);
    drawmap(data);
	drawplayer(data, data->head_player->px, data->head_player->py);
    drawRays2D(data);
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
	data->head_player->pa = 0;
    data->head_player->px = (get_pos(1, data->head_file->map) * 30) + 15;
	data->head_player->py = (get_pos(0, data->head_file->map) * 30) + 15;
    data->head_player->pdx = cos(data->head_player->pa) * 5;
    data->head_player->pdy = sin(data->head_player->pa) * 5;
	winmlx->mlx = mlx_init();
	winmlx->mlx_win = mlx_new_window(winmlx->mlx, 1920, 1080, "Cub3d");
	mlx_hook(data->head_winmlx->mlx_win, 2, 1L << 0, ft_key_hook, data);
	mlx_loop_hook(winmlx->mlx, random_next_frame, data);
	mlx_loop(winmlx->mlx);
	return (0);
}