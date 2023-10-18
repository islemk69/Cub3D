/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:08:29 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/18 19:49:22 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

int	is_space(char *str)
{
	while (*str)
	{
		if (*str == 'x')
			str++;
		else if (*str == '\n')
			str++;
		else
			return (0);
	}
	return (1);
}

int	nb_of_space(char **str, int *i)
{
	int	cpt;

	cpt = 0;
	while (is_space(str[*i]))
	{
		(*i)++;
		cpt++;
	}
	return (cpt);
}
