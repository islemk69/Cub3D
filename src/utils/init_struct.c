/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:22:37 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/13 16:36:21 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    my_mlx_pixel_put(t_winmlx *draw, int x, int y, int color)
{
    if ((x >= 0 && x < 1920) && (y >= 0 && y < 1080))
        ((int *)draw->addr)[y * (draw->line_length >> 2) + x] = color;
}

static int	alloc_struct(t_data *data)
{
	data->file = ft_calloc(1, sizeof(t_file));
	ft_bzero(data->file, sizeof(t_file));
	data->player = ft_calloc(1, sizeof(t_player));
	ft_bzero(data->player, sizeof(t_player));
	data->winmlx = ft_calloc(1, sizeof(t_winmlx));
	ft_bzero(data->winmlx, sizeof(t_winmlx));
	data->ntex = ft_calloc(1, sizeof(t_texture));
	ft_bzero(data->ntex, sizeof(t_texture));
	data->stex = ft_calloc(1, sizeof(t_texture));
	ft_bzero(data->stex, sizeof(t_texture));
	data->etex = ft_calloc(1, sizeof(t_texture));
	ft_bzero(data->etex, sizeof(t_texture));
	data->wtex = ft_calloc(1, sizeof(t_texture));
	ft_bzero(data->wtex, sizeof(t_texture));
	data->scene = ft_calloc(1, sizeof(t_scene));
	ft_bzero(data->scene, sizeof(t_scene));
	if (!data->file || !data->player | !data->winmlx || !data->ntex
		|| !data->stex || !data->wtex || !data->etex || !data->scene)
		return (1);
	return (0);
}

static int	get_pos(int mod, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' \
				|| map[i][j] == 'W')
			{
				if (mod)
					return (j);
				else
					return (i);
			}
		}
	}
	return (0);
}

static void	getdimention(t_file *file)
{
	int	i;
	int	current_length;

	i = -1;
	while (file->map[++i] != NULL)
	{
		current_length = 0;
		while (file->map[i][current_length] != '\0')
			++current_length;
		if (current_length > file->wmap)
			file->wmap = current_length;
		++file->hmap;
	}
}

int	init_struct(t_data *data, int flg)
{
	if (!flg)
	{
		if (alloc_struct(data))
			return (1);
		return (0);
	}
	if (data->file->orientation == 'N')
		data->player->pa = 3 * PI / 2;
	else if (data->file->orientation == 'S')
		data->player->pa = PI / 2;
	else if (data->file->orientation == 'E')
		data->player->pa = 0;
	else if (data->file->orientation == 'W')
		data->player->pa = PI;
	data->player->px = (get_pos(1, data->file->map) * 30) + 15;
	data->player->py = (get_pos(0, data->file->map) * 30) + 15;
	data->player->pdx = cos(data->player->pa) * 5;
	data->player->pdy = sin(data->player->pa) * 5;
	getdimention(data->file);
	data->file->wmap -= 1;
	if (data->file->hmap > data->file->wmap)
		data->file->greather = data->file->hmap;
	else
		data->file->greather = data->file->wmap;
	return (0);
}
