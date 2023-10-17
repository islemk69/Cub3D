/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:04:31 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/17 14:27:34 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	open_file(char *file, t_data *data, int flg)
{
	int	fd;

	if (access(file, F_OK) != -1)
	{
		if (access(file, R_OK) == -1)
			return (ft_putstr_fd("Error Pemission File\n", 2), 1);
	}
	else
		return (ft_putstr_fd("Error File not Found\n", 2), 1);
	fd = open(file, O_RDONLY);
	if (fd < 1)
		return (ft_putstr_fd("Error Failed to Open File\n", 2), 1);
	if (flg)
	{
		if (check_file(fd, data->file))
			return (1);
	}
	return (0);
}

int	check_path(t_data *data)
{
	if (open_file(data->file->path_to_e, data, 0)
		|| open_file(data->file->path_to_w, data, 0)
		|| open_file(data->file->path_to_s, data, 0)
		|| open_file(data->file->path_to_n, data, 0))
		return (1);
	return (0);
}

//Check si le fichier existe, si les droit sont dispo et ouvre le fichier

int	check_map(char **map)
{
	size_t	i;

	i = 0;
	if (!map[0])
		return (1);
	while (map[i] && map[i][0] == '\n')
		i++;
	while (map[i] && map[i][0] == 'x')
		i++;
	while (map[i] && map[i][0] == '1')
		i++;
	if (map[i - 1][ft_strlen(map[i - 1]) - 1] == '\n')
		return (ft_putstr_fd("Error Pemission File\n", 2), 1);
	return (0);
}

int	check_file(int fd, t_file *file)
{
	char		*line;
	int			flg;
	t_tmpmap	*listmap;

	flg = 0;
	line = NULL;
	listmap = NULL;
	while (42)
	{
		if (line)
			free(line);
		line = get_next_line(fd);
		if (!line)
		{
			if (complete_param(file) || fill_map_tab(&listmap, file))
				return (ft_putstr_fd("Error Parameters\n", 2), 1);
			return (free(line), lstclear(&listmap), 0);
		}
		if (flg)
			if (fill_struct_map(&listmap, line))
				return (free(line), 1);
		if (!flg && param(line, file, &flg))
			return (ft_putstr_fd("Error Parameters\n", 2), free(line), 1);
	}
}
