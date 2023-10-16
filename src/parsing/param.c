/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:44:29 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/16 20:04:10 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int			complete_param(t_file *file);

int	param(char *line, t_file *file, int *flg)
{
	char	**line_split;

	line_split = ft_split(line, ' ');
	if (!line_split)
		return (ft_free_tab(line_split), 1);
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

int	get_colors(char *color, int mod, t_file *file)
{
	char	**color_split;
	int		i;

	i = -1;
	color_split = ft_split2(color);
	if (!color_split)
		return (ft_free_tab(color_split), 1);
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

int	check_color(char **color_split, char *color, int i, int nb)
{
	if (color[0] == ',' || color[ft_strlen(color) - 2] == ',')
		return (1);
	while (color[i] != '\n')
	{
		if (color[i] == ',' && color[i + 1] && color[i + 1] == ',')
			return (1);
		else if ((color[i] == ',' && color[i + 1] != ',' && color[i + 1]))
		{
			i++;
			continue ;
		}
		else if (!ft_isdigit(color[i]))
			return (1);
		i++;
	}
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
