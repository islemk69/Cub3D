/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:28:48 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/13 19:02:52 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int key_press_hook(int keycode, t_data *data)
{
    (void)data;
	printf("%d\n", keycode);
    if (keycode >= 0 && keycode < 65365)
        data->player->key_states[keycode] = true;
    return (0);
}

int key_release_hook(int keycode, t_data *data)
{
    (void)data;
    if (keycode >= 0 && keycode < 65365)
        data->player->key_states[keycode] = false;
    return (0);
}

bool is_collision(t_data *data, float newX, float newY)
{
    int map_posX = newX / 30;
    int map_posY = newY / 30;

    // Vérifier si la position ajustée est à l'intérieur d'une cellule de mur
    if (map_posX >= 0 && map_posY >= 0 &&
        map_posY < data->file->hmap && map_posX < data->file->wmap &&
        data->file->map[map_posY][map_posX] == '1')
    {
        return true;
    }

    return false;
}

void move(t_data *data)
{
    float moveSpeed = 0.4;
    float rotateSpeed = 0.02;
	float collisionMargin = 6.0;

    if (data->player->key_states[119]) // W
    {
        float newX = data->player->px + data->player->pdx * moveSpeed;
        float newY = data->player->py + data->player->pdy * moveSpeed;
        if (!is_collision(data, newX, newY) &&
            !is_collision(data, newX - collisionMargin, newY - collisionMargin) &&
            !is_collision(data, newX - collisionMargin, newY + collisionMargin) &&
            !is_collision(data, newX + collisionMargin, newY - collisionMargin) &&
            !is_collision(data, newX + collisionMargin, newY + collisionMargin))
        {
            data->player->px = newX;
            data->player->py = newY;
        }
    }
     if (data->player->key_states[115]) // S
    {
        float newX = data->player->px - data->player->pdx * moveSpeed;
        float newY = data->player->py - data->player->pdy * moveSpeed;
        if (!is_collision(data, newX, newY) &&
            !is_collision(data, newX - collisionMargin, newY - collisionMargin) &&
            !is_collision(data, newX - collisionMargin, newY + collisionMargin) &&
            !is_collision(data, newX + collisionMargin, newY - collisionMargin) &&
            !is_collision(data, newX + collisionMargin, newY + collisionMargin))
        {
            data->player->px = newX;
            data->player->py = newY;
        }
    }
    if (data->player->key_states[97]) // A
    {
        float newX = data->player->px - cos(data->player->pa + PI/2) * moveSpeed * 3;
        float newY = data->player->py - sin(data->player->pa + PI/2) * moveSpeed * 3;
        if (!is_collision(data, newX, newY) &&
            !is_collision(data, newX - collisionMargin, newY - collisionMargin) &&
            !is_collision(data, newX - collisionMargin, newY + collisionMargin) &&
            !is_collision(data, newX + collisionMargin, newY - collisionMargin) &&
            !is_collision(data, newX + collisionMargin, newY + collisionMargin))
        {
            data->player->px = newX;
            data->player->py = newY;
        }
    }
    if (data->player->key_states[100]) // D
    {
        float newX = data->player->px + cos(data->player->pa + PI/2) * moveSpeed * 3;
        float newY = data->player->py + sin(data->player->pa + PI/2) * moveSpeed * 3;
        if (!is_collision(data, newX, newY) &&
            !is_collision(data, newX - collisionMargin, newY - collisionMargin) &&
            !is_collision(data, newX - collisionMargin, newY + collisionMargin) &&
            !is_collision(data, newX + collisionMargin, newY - collisionMargin) &&
            !is_collision(data, newX + collisionMargin, newY + collisionMargin))
        {
            data->player->px = newX;
            data->player->py = newY;
        }
    }

    if (data->player->key_states[65363]) // rotation camera fleche droite
    {
        data->player->pa += rotateSpeed;
        if (data->player->pa > 2 * PI)
            data->player->pa -= 2 * PI;
        data->player->pdx = cos(data->player->pa) * 5;
        data->player->pdy = sin(data->player->pa) * 5;
    }
    if (data->player->key_states[65361]) // rotation camera fleche gauche
    {
        data->player->pa -= rotateSpeed;
        if (data->player->pa < 0)
            data->player->pa += 2 * PI;
        data->player->pdx = cos(data->player->pa) * 5;
        data->player->pdy = sin(data->player->pa) * 5;
    }
}
