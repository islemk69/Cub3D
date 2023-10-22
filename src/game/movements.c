/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:28:48 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/17 13:33:33 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_key_and_set_new_angle(t_data *data, float rotateSpeed);
static void	check_collision(t_data *data, float newX, float newY, \
float c_margin);
static void	check_key_and_set_new_position(t_data *data, float moveSpeed, \
float *newX, float *newY);
static void	check_esc_key(t_data *data);

void	move(t_data *data)
{
	float	move_speed;
	float	rotate_speed;
	float	collision_margin;
	float	newx;
	float	newy;

	move_speed = 0.6;
	rotate_speed = 0.04;
	collision_margin = 6.0;
	newx = data->player->px;
	newy = data->player->py;
	check_key_and_set_new_position(data, move_speed, &newx, &newy);
	check_collision(data, newx, newy, collision_margin);
	check_key_and_set_new_angle(data, rotate_speed);
	check_esc_key(data);
}

static void	check_key_and_set_new_angle(t_data *data, float rotateSpeed)
{
	if (data->player->key_states[RIGHT])
	{
		data->player->pa += rotateSpeed;
		if (data->player->pa > 2 * PI)
			data->player->pa -= 2 * PI;
		data->player->pdx = cos(data->player->pa) * 5;
		data->player->pdy = sin(data->player->pa) * 5;
	}
	if (data->player->key_states[LEFT])
	{
		data->player->pa -= rotateSpeed;
		if (data->player->pa < 0)
			data->player->pa += 2 * PI;
		data->player->pdx = cos(data->player->pa) * 5;
		data->player->pdy = sin(data->player->pa) * 5;
	}
}

static void	check_collision(t_data *data, float newX, float newY, \
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

static void	check_key_and_set_new_position(t_data *data, float moveSpeed, \
float *newX, float *newY)
{
	if (data->player->key_states[W])
	{
		*newX += data->player->pdx * moveSpeed;
		*newY += data->player->pdy * moveSpeed;
	}
	if (data->player->key_states[S])
	{
		*newX -= data->player->pdx * moveSpeed;
		*newY -= data->player->pdy * moveSpeed;
	}
	if (data->player->key_states[A])
	{
		*newX -= cos(data->player->pa + PI / 2) * moveSpeed * 3;
		*newY -= sin(data->player->pa + PI / 2) * moveSpeed * 3;
	}
	if (data->player->key_states[D])
	{
		*newX += cos(data->player->pa + PI / 2) * moveSpeed * 3;
		*newY += sin(data->player->pa + PI / 2) * moveSpeed * 3;
	}
}

static void	check_esc_key(t_data *data)
{
	if (data->player->key_states[ESC])
	{
		ft_free_all(data, 1);
		exit(0);
	}
}
