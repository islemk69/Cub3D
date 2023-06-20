/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:44:29 by ikaismou          #+#    #+#             */
/*   Updated: 2023/06/20 18:18:10 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//check si la ligne est vide et ignore celle ci

int	is_empty(char *line)
{
	if (*line == '\n')
		return (1);
	return (0);
}

//rempli les parametres et check si cellesci sont bien formatte

int fill_param(char *line, t_file *file)
{
	char	**line_split;
	
	line_split = ft_split(line, ' ');
	if (is_empty(line_split[0]) && !line_split[1])
		return (0);
	if (line_split[1] && line_split[1][0] == '.' && line_split[1][1] == '/')
	{
		if (!ft_strncmp(line_split[0], "WE\0", 3) && !file->path_to_w)
			file->path_to_w = ft_strdup(line_split[1]);
		else if (!ft_strncmp(line_split[0], "EA\0", 3) && !file->path_to_e)
			file->path_to_e = ft_strdup(line_split[1]);
		else if (!ft_strncmp(line_split[0], "SO\0", 3) && !file->path_to_s)
			file->path_to_s = ft_strdup(line_split[1]);
		else if (!ft_strncmp(line_split[0], "NO\0", 3) && !file->path_to_n)
			file->path_to_n = ft_strdup(line_split[1]);
		else
			return (1);
	}
	else
		return (1);
	return (0);
}