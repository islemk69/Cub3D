/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:44:29 by ikaismou          #+#    #+#             */
/*   Updated: 2023/06/28 17:28:58 by ikaismou         ###   ########.fr       */
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

int	check_color(char **color_split)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	j = 0;
	while (color_split[i])
	{
		j = 0;
		while (color_split[i][j])
		{
			if (!ft_isdigit(color_split[i][j]))
				return (printf("attention %c\n", color_split[i][j]), 1);
			j++;
		}
		nb = ft_atoi(color_split[i]);
		if (nb < 0 || nb > 255)
			return (printf("check_color\n"), 1);
		i++;
	}
	if (i != 3)
		return (printf("check_color\n"), 1);
	return (0);
}

int	get_colors(char *color, int mod, t_file *file)
{
	char	**color_split;
	int		i;
	
	i = 0;
	color_split = ft_split2(color);
	if (check_color(color_split))
		return (printf("get_colors\n"), 1);
	while (color_split[i])
	{
		if (mod)
		{
			file->color_s_tmp = "s";
			file->color_sky[i] = atoi(color_split[i]);
		}
		else
		{
			file->color_f_tmp = "s";
			file->color_floor[i] = atoi(color_split[i]);
		}
		i++;
	}
	return (0);
}

//rempli les parametres et check si cellesci sont bien formatte

int fill_param(char *line, t_file *file, int *flg)
{
	char	**line_split;
	
	line_split = ft_split(line, ' ');
	if (is_empty(line_split[0]) && !line_split[1])
		return (0);
	if (line_split[1])
	{
		if (!ft_strncmp(line_split[0], "WE\0", 3) && !file->path_to_w)
			file->path_to_w = ft_strdup(line_split[1]);
		else if (!ft_strncmp(line_split[0], "EA\0", 3) && !file->path_to_e)
			file->path_to_e = ft_strdup(line_split[1]);
		else if (!ft_strncmp(line_split[0], "SO\0", 3) && !file->path_to_s)
			file->path_to_s = ft_strdup(line_split[1]);
		else if (!ft_strncmp(line_split[0], "NO\0", 3) && !file->path_to_n)
			file->path_to_n = ft_strdup(line_split[1]);
		else if (!ft_strncmp(line_split[0], "C\0", 2) && !file->color_s_tmp)
		{
			if (get_colors(line_split[1], 1, file))
				return (printf("holala\n"), 1);
		}
		else if (!ft_strncmp(line_split[0], "F\0", 2) && !file->color_f_tmp)
		{
			if (get_colors(line_split[1], 0, file))
				return (1);
		}
		else
			return (printf("fill_param1 %s\n", line_split[1]), 1);
	}
	else
		return (printf("fill_param2\n"), 1);
	if (!complete_param(file))
	{
		printf("PARAMETRES : \n%s\n%s\n%s\n%s\n", file->path_to_e, file->path_to_s, file->path_to_n, file->path_to_w);
		int i = 0;
		while (i < 3)
		{
			printf("%d\n", file->color_floor[i]);
			i++;
		}
		printf("\n");
		i = 0;
		while (i < 3)
		{
			printf("%d\n", file->color_sky[i]);
			i++;
		}
		printf("////////////////////////////////////////////////\n");
		printf("CHECK PARAM OK\n");
		printf("////////////////////////////////////////////////\n");
		*flg = 1;
	}
	return (0);
}