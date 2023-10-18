/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:42:39 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/18 12:38:48 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_empty(char *line)
{
	if (*line == '\n')
		return (1);
	return (0);
}

int	check_char(char *str, int *p, t_file *file)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != ' ' && \
		str[i] != '\n' && str[i] != 'N' && str[i] != 'S' && \
		str[i] != 'E' && str[i] != 'W')
			return (1);
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			file->orientation = str[i];
			*p += 1;
		}
		i++;
	}
	return (0);
}

void	replace_space(char *line)
{
	while (*line)
	{
		if (*line == ' ')
			*line = 'x';
		line++;
	}
}

int	only_wall(char *str)
{
	while (*str && *str != '\n')
	{
		if (*str != '1')
		{
			if (*str != 'x')
				return (1);
		}
		str++;
	}
	return (0);
}

size_t	ft_tablen(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}
