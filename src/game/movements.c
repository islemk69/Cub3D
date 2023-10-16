/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:28:48 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/16 16:12:03 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_key_and_set_new_angle(t_data *data, float rotateSpeed);
void	check_collision(t_data *data, float newX, float newY, \
float c_margin);
void	check_key_and_set_new_position(t_data *data, float moveSpeed, \
float *newX, float *newY);

void	check_esc_key(t_data *data)
{
	if (data->player->key_states[65307])
	{
		ft_free_all(data, 1);
		exit(0);
	}
}

void	move(t_data *data)
{
	float	move_speed;
	float	rotate_speed;
	float	collision_margin;
	float	newx;
	float	newy;

	move_speed = 0.4;
	rotate_speed = 0.02;
	collision_margin = 6.0;
	newx = data->player->px;
	newy = data->player->py;
	check_key_and_set_new_position(data, move_speed, &newx, &newy);
	check_collision(data, newx, newy, collision_margin);
	check_key_and_set_new_angle(data, rotate_speed);
	check_esc_key(data);
}

void	check_key_and_set_new_angle(t_data *data, float rotateSpeed)
{
	if (data->player->key_states[65363])
	{
		data->player->pa += rotateSpeed;
		if (data->player->pa > 2 * PI)
			data->player->pa -= 2 * PI;
		data->player->pdx = cos(data->player->pa) * 5;
		data->player->pdy = sin(data->player->pa) * 5;
	}
	if (data->player->key_states[65361])
	{
		data->player->pa -= rotateSpeed;
		if (data->player->pa < 0)
			data->player->pa += 2 * PI;
		data->player->pdx = cos(data->player->pa) * 5;
		data->player->pdy = sin(data->player->pa) * 5;
	}
}

void	check_collision(t_data *data, float newX, float newY, \
float c_margin)
{
	if (!is_collision(data, newX, data->player->py) && \
	!is_collision(data, newX - c_margin, data->player->py - c_margin) && \
	!is_collision(data, newX - c_margin, data->player->py + c_margin) && \
	!is_collision(data, newX + c_margin, data->player->py - c_margin) && \
	!is_collision(data, newX + c_margin, data->player->py + c_margin))
		data->player->px = newX;
	if (!is_collision(data, data->player->px, newY) && \
	!is_collision(data, data->player->px - c_margin, newY - c_margin) && \
	!is_collision(data, data->player->px - c_margin, newY + c_margin) && \
	!is_collision(data, data->player->px + c_margin, newY - c_margin) && \
	!is_collision(data, data->player->px + c_margin, newY + c_margin))
		data->player->py = newY;
}

void	check_key_and_set_new_position(t_data *data, float moveSpeed, \
float *newX, float *newY)
{
	if (data->player->key_states[119])
	{
		*newX += data->player->pdx * moveSpeed;
		*newY += data->player->pdy * moveSpeed;
	}
	if (data->player->key_states[115])
	{
		*newX -= data->player->pdx * moveSpeed;
		*newY -= data->player->pdy * moveSpeed;
	}
	if (data->player->key_states[97])
	{
		*newX -= cos(data->player->pa + PI / 2) * moveSpeed * 3;
		*newY -= sin(data->player->pa + PI / 2) * moveSpeed * 3;
	}
	if (data->player->key_states[100])
	{
		*newX += cos(data->player->pa + PI / 2) * moveSpeed * 3;
		*newY += sin(data->player->pa + PI / 2) * moveSpeed * 3;
	}
}
