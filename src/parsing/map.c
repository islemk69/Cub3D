/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:08:29 by ikaismou          #+#    #+#             */
/*   Updated: 2023/06/29 13:00:16 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	fill_struct_map(t_tmpmap **map, char *line)
{
	t_tmpmap	*cell;

	cell = create_cell(line);
	ft_lstad_back(map, cell);
}

void	fill_map_tab(t_tmpmap **list, t_file *file)
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
	i = 0;
	head = *list;
	while (head)
	{
		file->map[i] = ft_strdup(head->line);
		i++;
		head = head->next;
	}
	file->map[i] = 0;
	lstclear(list);
}
