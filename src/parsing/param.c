/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:44:29 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/15 19:52:55 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int			complete_param(t_file *file);
static int	get_colors(char *color, int mod, t_file *file);
static int	check_color(char **color_split, char *color, int i, int nb);

int	fill_param(t_file *file, char **l_split)
{
	if (!ft_strncmp(l_split[0], "WE\0", 3) && !file->path_to_w)
		file->path_to_w = ft_strndup(l_split[1], ft_strlen(l_split[1]) - 1);
	else if (!ft_strncmp(l_split[0], "EA\0", 3) && !file->path_to_e)
		file->path_to_e = ft_strndup(l_split[1], ft_strlen(l_split[1]) - 1);
	else if (!ft_strncmp(l_split[0], "SO\0", 3) && !file->path_to_s)
		file->path_to_s = ft_strndup(l_split[1], ft_strlen(l_split[1]) - 1);
	else if (!ft_strncmp(l_split[0], "NO\0", 3) && !file->path_to_n)
		file->path_to_n = ft_strndup(l_split[1], ft_strlen(l_split[1]) - 1);
	else if (!ft_strncmp(l_split[0], "C\0", 2) && !file->color_s_tmp)
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

int	param(char *line, t_file *file, int *flg)
{
	char	**line_split;

	line_split = ft_split(line, ' ');
	if (is_empty(line_split[0]) && !line_split[1])
		return (ft_free_tab(line_split), 0);
	if (line_split[1])
	{
		if (fill_param(file, line_split))
			return (ft_free_tab(line_split), 1);
	}
	else
		return (ft_free_tab(line_split), 1);
	if (!complete_param(file))
		*flg = 1;
	return (ft_free_tab(line_split), 0);
}

int	complete_param(t_file *file)
{
	if (!file->path_to_e || !file->path_to_n || !file->path_to_s
		|| !file->path_to_w || !file->color_f_tmp || !file->color_s_tmp)
		return (1);
	return (0);
}

static int	get_colors(char *color, int mod, t_file *file)
{
	char	**color_split;
	int		i;

	i = -1;
	color_split = ft_split2(color);
	if (check_color(color_split, color, 0, 0))
		return (ft_free_tab(color_split), 1);
	while (color_split[++i])
	{
		if (mod)
		{
			file->color_s_tmp = "s";
			file->color_sky[i] = ft_atoi(color_split[i]);
		}
		else
		{
			file->color_f_tmp = "s";
			file->color_floor[i] = ft_atoi(color_split[i]);
		}
	}
	ft_free_tab(color_split);
	return (0);
}

static int	check_color(char **color_split, char *color, int i, int nb)
{
	if (color[0] == ',' || color[ft_strlen(color) - 2] == ',')
		return (1);
	while (color[i] != '\n')
	{
		printf("%c", color[i]);
		if (color[i] == ',' && color[i + 1] && color[i + 1] == ',')
			return (1);
		else if (color[i] != ',' && !ft_isdigit(color[i]))
			return (1);
		i++;
	}
	printf("\n");
	i = -1;
	while (color_split[++i])
	{
		nb = ft_atoi(color_split[i]);
		if (nb < 0 || nb > 255)
			return (1);
	}
	if (i != 3)
		return (1);
	return (0);
}
