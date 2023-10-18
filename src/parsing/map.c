/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:08:29 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/18 13:26:11 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	fill_struct_map(t_tmpmap **map, char *line)
{
	t_tmpmap	*cell;

	cell = create_cell(line);
	if (!cell)
		return (1);
	ft_lstad_back(map, cell);
	return (0);
}

int	fill_map_tab(t_tmpmap **list, t_file *file)
{
	int			i;
	t_tmpmap	*head;

	head = *list;
	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	file->map = malloc(sizeof(char **) * (i + 1));
	if (!file->map)
		return (1);
	i = 0;
	head = *list;
	while (head)
	{
		file->map[i] = ft_strdup(head->line);
		if (!file->map[i])
			return (1);
		i++;
		head = head->next;
	}
	file->map[i] = 0;
	return (0);
}

int	get_border(char **str, int index)
{
	if (!index)
	{
		while (only_wall(str[index]))
			index++;
		return (index);
	}
	while (only_wall(str[index]))
		index--;
	return (index);
}

int	check_wall(t_file *file, int i, int j)
{
	while (file->map[i])
	{
		j = 0;
		while (file->map[i][j])
		{
			if (file->map[i][j] == '0' && (!file->map[i - 1][j]
				|| file->map[i - 1][j] == '\n'
				|| !file->map[i + 1][j] || file->map[i + 1][j] == '\n'
				|| !file->map[i][j + 1] || file->map[i][j + 1] == '\n'
				|| !file->map[i][j - 1] || file->map[i][j - 1] == '\n'))
				return (1);
			else if (file->map[i][j] == 'x')
			{
				if ((i > 0 && file->map[i - 1][j] == '0')
					|| (file->map[i + 1] && file->map[i + 1][j] == '0')
					|| (j > 0 && file->map[i][j - 1] == '0')
					|| (file->map[i][j + 1] && file->map[i][j + 1] == '0'))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_map(t_file *file)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (file->map[i])
	{
		if (check_char(file->map[i], &p, file))
			return (1);
		if (ft_strchr(file->map[i], ' '))
			replace_space(file->map[i]);
		i++;
	}
	if (p != 1)
		return (1);
	if (only_wall(file->map[0])
		|| only_wall(file->map[ft_strlen_dtab(file->map) - 1])
		|| check_wall(file, 0, 0) || check_player(file->map))
		return (1);
	return (0);
}
