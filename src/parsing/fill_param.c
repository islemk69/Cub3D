/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:44:05 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/18 13:28:32 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	alloc_texture(char **path, char **l_split)
{
	*path = ft_strndup(l_split[1], ft_strlen(l_split[1]) - 1);
	if (!*path)
		return (1);
	return (0);
}

static int	fill_texture_param(t_file *file, char **l_split)
{
	if (!ft_strncmp(l_split[0], "WE\0", 3) && !file->path_to_w)
	{
		if (alloc_texture(&file->path_to_w, l_split))
			return (1);
	}
	else if (!ft_strncmp(l_split[0], "EA\0", 3) && !file->path_to_e)
	{
		if (alloc_texture(&file->path_to_e, l_split))
			return (1);
	}
	else if (!ft_strncmp(l_split[0], "SO\0", 3) && !file->path_to_s)
	{
		if (alloc_texture(&file->path_to_s, l_split))
			return (1);
	}
	else if (!ft_strncmp(l_split[0], "NO\0", 3) && !file->path_to_n)
	{
		if (alloc_texture(&file->path_to_n, l_split))
			return (1);
	}
	else
		return (1);
	return (0);
}

static int	fill_color_param(t_file *file, char **l_split)
{
	if (!ft_strncmp(l_split[0], "C\0", 2) && !file->color_s_tmp)
	{
		if (l_split[1] && get_colors(l_split[1], 1, file))
			return (1);
	}
	else if (!ft_strncmp(l_split[0], "F\0", 2) && !file->color_f_tmp)
	{
		if (l_split[1] && get_colors(l_split[1], 0, file))
			return (1);
	}
	else
		return (1);
	return (0);
}

int	check_player(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]) && ((map[i][j + 1]
				&& map[i][j + 1] == '\n')
				|| !map[i][j - 1] || !map[i + 1][j]
				|| !map[i - 1][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	fill_param(t_file *file, char **l_split)
{
	if (fill_texture_param(file, l_split) && fill_color_param(file, l_split))
		return (1);
	return (0);
}
