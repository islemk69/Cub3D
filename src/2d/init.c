/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blakehal <blakehal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:33:32 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/14 17:00:00 by blakehal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool key_states[65365] = {false};

void    my_mlx_pixel_put(t_winmlx *draw, int x, int y, int color)
{
    if ((x >= 0 && x < WINDOW_WIDTH) && (y >= 0 && y < WINDOW_HEIGHT))
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
    data->head_file->map[(int)data->head_player->py / TILE_SIZE][(int)data->head_player->px / TILE_SIZE] = 'N';
}

 bool is_collision(t_data *data, int newX, int newY)
 {
     int map_posX = newX / TILE_SIZE;
     int map_posY = newY / TILE_SIZE;

     // Vérifier si la position est à l'intérieur d'une cellule de mur
     if (data->head_file->map[map_posY][map_posX] == '1')
         return true;

     return false;
 }

int key_press_hook(int keycode, t_data *data)
{
    (void)data;
    if (keycode >= 0 && keycode < 65365)
        key_states[keycode] = true;
    return (0);
}

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
	while (i < TILE_SIZE)
	{
		j = 0;
		x = save;
		while (j < TILE_SIZE)
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
			x+=TILE_SIZE;
			j++;
		}
		y+=TILE_SIZE;
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
    float rx, ry, ra, xo, yo, disT;
    ra = data->head_player->pa - DR * TILE_SIZE;
    if (ra < 0)
        ra += 2 * PI;
    if (ra > 2 * PI)
        ra -= 2 * PI;
    rx = 0;
    ry = 0;
    xo = 0;
    yo = 0;

    float midHeight = WINDOW_HEIGHT / 2;

    for (r = 0; r < WINDOW_WIDTH; r++)
    {
        dof = 0;
        float disH = 100000000, hx=data->head_player->px, hy=data->head_player->py;
        float aTan = -1 / tan(ra);

        if (ra > PI) // looking up
        {
            ry = (float)(((int)data->head_player->py / TILE_SIZE) * TILE_SIZE) - 0.0001;
            rx = (data->head_player->py - ry) * aTan + data->head_player->px;
            yo = -TILE_SIZE;
            xo = -yo * aTan;
        }
        else if (ra < PI) // looking down
        {
            ry = (float)(((int)data->head_player->py / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
            rx = (data->head_player->py - ry) * aTan + data->head_player->px;
            yo = TILE_SIZE;
            xo = -yo * aTan;
        }
        else //looking straight left or right
        {
            rx = data->head_player->px;
            ry = data->head_player->py;
            dof = data->head_file->greather;
        }

        while (dof < data->head_file->greather)
        {
            mx = (int)(rx / TILE_SIZE);
            my = (int)(ry / TILE_SIZE);

            if (mx >= 0 && mx < data->head_file->wmap && my >= 0 && my < data->head_file->hmap && data->head_file->map[my][mx] == '1')
            {
                hx = rx;
                hy = ry;
                disH = dist(data->head_player->px, data->head_player->py, hx, hy, ra);
                dof = data->head_file->greather;
            }
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }

        // Check vertical lines
        dof = 0;
        float disV = 1000000, vx=data->head_player->px, vy=data->head_player->py;
        float nTan = -tan(ra);

        if (ra > P2 && ra < P3) // looking left
        {
            rx = (float)(((int)data->head_player->px / TILE_SIZE) * TILE_SIZE) - 0.0001;
            ry = (data->head_player->px - rx) * nTan + data->head_player->py;
            xo = -TILE_SIZE;
            yo = -xo * nTan;
        }
        else if (ra < P2 || ra > P3) // looking right
        {
            rx = (float)(((int)data->head_player->px / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
            ry = (data->head_player->px - rx) * nTan + data->head_player->py;
            xo = TILE_SIZE;
            yo = -xo * nTan;
        }
        else // looking straight up and down
        {
            rx = data->head_player->px;
            ry = data->head_player->py;
            dof = data->head_file->greather;
        }

        while (dof < data->head_file->greather)
        {
            mx = (int)(rx / TILE_SIZE);
            my = (int)(ry / TILE_SIZE);

            if (mx >= 0 && mx < data->head_file->wmap && my >= 0 && my < data->head_file->hmap && data->head_file->map[my][mx] == '1')
            {
                vx = rx;
                vy = ry;
                disV = dist(data->head_player->px, data->head_player->py, vx, vy, ra);
                break ;
            }
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }

        // Choisir le rayon à dessiner
        int h_redded = 0;
        if (disV < disH)
        {
            rx = vx;
            ry = vy;
            disT = disV;
            h_redded = 1;
        }
        else
        {
            rx = hx;
            ry = hy;
            disT = disH;
        }
        float  ca = data->head_player->pa - ra;
        if (ca < 0)
            ca += 2 * PI;
        if (ca > 2 * PI)
            ca -= 2 * PI;
        disT = disT * cos(ca);
//        float ca = FixAng(data->head_player->pa - ra);
//        disT = disT * cos(degToRad(ca));
        float lineH = (TILE_SIZE * WINDOW_HEIGHT) / disT;  // Calcul de la hauteur de la colonne
        if (lineH > WINDOW_HEIGHT)
            lineH = WINDOW_HEIGHT;  // Limite la hauteur à la hauteur de la fenêtre

        int lineOff = midHeight - (lineH / 2);  // Calcul de la position de départ de la colonne

       for (int i = 0; i < 1080; i++)
        {
            if (i < lineOff) // Above the current column, draw sky
                my_mlx_pixel_put(data->head_winmlx, r, i, H_BLUE);
            else if (i >= lineOff && i < lineOff + lineH) // Within the current column, draw wall
            {
                if (h_redded == 1)
                    my_mlx_pixel_put(data->head_winmlx, r, i, H_REDDED);
                else
                    my_mlx_pixel_put(data->head_winmlx, r, i, H_RED);
            }
            else // Below the current column, draw ground
                my_mlx_pixel_put(data->head_winmlx, r, i, H_GREEN);
        }

//        draw_line(data, data->head_player->px, data->head_player->py, rx, ry, H_RED);
        ra += DR * (60.0 / 1920.0);
        if (ra < 0)
            ra += 2 * PI;
        if (ra > 2 * PI)
            ra -= 2 * PI;
    }
}


static int	random_next_frame(t_data *data)
{


	data->head_winmlx->img = mlx_new_image(data->head_winmlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->head_winmlx->addr = mlx_get_data_addr(data->head_winmlx->img, &data->head_winmlx->bits_per_pixel, &data->head_winmlx->line_length, &data->head_winmlx->endian);
    float moveSpeed = 0.8;
    float rotateSpeed = 0.05;

    if (key_states[65362]) // haut
    {
        float newX = data->head_player->px + data->head_player->pdx * moveSpeed;
        float newY = data->head_player->py + data->head_player->pdy * moveSpeed;

        if (!is_collision(data, newX, newY))
        {
            data->head_player->px = newX;
            data->head_player->py = newY;
        }
    }

    if (key_states[65364]) // bas
    {
        float newX = data->head_player->px - data->head_player->pdx * moveSpeed;
        float newY = data->head_player->py - data->head_player->pdy * moveSpeed;
        
        if (!is_collision(data, newX, newY))
        {
            data->head_player->px = newX;
            data->head_player->py = newY;
        }
    }

    if (key_states[65363]) // droite
    {
        data->head_player->pa += rotateSpeed;
        if (data->head_player->pa > 2 * M_PI)
            data->head_player->pa -= 2 * M_PI;
        data->head_player->pdx = cos(data->head_player->pa) * 5;
        data->head_player->pdy = sin(data->head_player->pa) * 5;
    }

    if (key_states[65361]) // gauche
    {
        data->head_player->pa -= rotateSpeed;
        if (data->head_player->pa < 0)
            data->head_player->pa += 2 * M_PI;
        data->head_player->pdx = cos(data->head_player->pa) * 5;
        data->head_player->pdy = sin(data->head_player->pa) * 5;
    }
    reset_player_position_on_map(data);
    drawRays2D(data);
    drawmap(data);
    drawplayer(data, data->head_player->px, data->head_player->py);
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

void getdimention(t_file *file) {
    // Vérification que la carte n'est pas vide
    if (file->map == NULL || file->map[0] == NULL) {
        fprintf(stderr, "Erreur : la carte est vide.\n");
        return;
    }

    // Initialisation des dimensions à 0
    file->wmap = 0;
    file->hmap = 0;

    // Parcours de la carte pour trouver les dimensions
    for (int i = 0; file->map[i] != NULL; ++i) {
        int current_length = 0;

        // Calcul de la longueur de la ligne actuelle
        while (file->map[i][current_length] != '\0') {
            ++current_length;
        }

        // Mise à jour de la largeur maximale
        if (current_length > file->wmap) {
            file->wmap = current_length;
        }

        // Mise à jour de la hauteur
        ++file->hmap;
    }
}


int ft_init(t_winmlx *winmlx, t_data *data)
{
	 if (data->head_file->orientation == 'N')
        data->head_player->pa = 3 * PI / 2;
    else if (data->head_file->orientation == 'S')
        data->head_player->pa = PI / 2;
    else if (data->head_file->orientation == 'E')
        data->head_player->pa = 0;
    else if (data->head_file->orientation == 'W')
        data->head_player->pa = PI;
    data->head_player->px = (get_pos(1, data->head_file->map) * 30) + 15;
	data->head_player->py = (get_pos(0, data->head_file->map) * 30) + 15;
    data->head_player->pdx = cos(data->head_player->pa) * 5;
    data->head_player->pdy = sin(data->head_player->pa) * 5;
    getdimention(data->head_file);
    printf("%d\n", data->head_file->hmap);
    data->head_file->wmap -= 1;
     printf("%d\n", data->head_file->wmap);
    if (data->head_file->hmap > data->head_file->wmap)
        data->head_file->greather = data->head_file->hmap;
    else
    {
        data->head_file->greather = data->head_file->wmap;
    }
	winmlx->mlx = mlx_init();
	winmlx->mlx_win = mlx_new_window(winmlx->mlx, 1920, 1080, "Cub3d");
	mlx_hook(data->head_winmlx->mlx_win, 2, 1L << 0, ft_key_hook, data);
	mlx_loop_hook(winmlx->mlx, random_next_frame, data);
	mlx_loop(winmlx->mlx);
	return (0);
}