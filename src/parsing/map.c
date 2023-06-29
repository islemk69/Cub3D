/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:08:29 by ikaismou          #+#    #+#             */
/*   Updated: 2023/06/29 15:15:08 by ikaismou         ###   ########.fr       */
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

int	check_char(char *str, int *p)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != ' ' && str[i] != '\n' && str[i] != 'N' && str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
			return (printf("le char %c\n", str[i]), 1);
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			printf("je susi passe\n");
			*p += 1;
		}
		i++;
	}
	return (0);
}

int parse_map(t_file *file)
{
	int i = 0;
	int p = 0;
	while (file->map[i])
	{
		if (check_char(file->map[i], &p))
			return(1);
		i++;
	}
	if (p != 1)
		return (1);
	return (0);
}