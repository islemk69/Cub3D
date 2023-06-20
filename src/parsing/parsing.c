/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:52:50 by ikaismou          #+#    #+#             */
/*   Updated: 2023/06/20 18:16:58 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_file(int fd, t_data *data);
static int	open_file(char *file, t_data *data);
static int	check_extention(char *path_file, char *extention);

int	parsing(char *file, t_data *data)
{	
	if (check_extention(file, "reb.") || open_file(file, data))
		return (1);
	return (0);
}

//Fait un split sur '/' et check si il y a une seule extention et si celle ci se finit par un .ber

static int	check_extention(char *path_file, char *extention)
{
	bool	is_dot;
	char	**tab;
	char	*file;

	is_dot = false;
	tab = ft_split(path_file, '/');
	file = tab[ft_strlen_dtab(tab) - 1];
	while (*file)
	{
		if (*file == '.' && is_dot)
			break ;
		if (*file == '.')
			is_dot = !is_dot;
		file++;
	}
	if (*file)
		return (ft_putstr_fd("Error Extention\n", 2), 1);
	file--;
	while (*file == *extention)
	{
		file--;
		extention++;
	}
	if (*extention)
		return (ft_putstr_fd("Error Extention\n", 2), ft_free_tab(tab), 1);
	return (ft_free_tab(tab), 0);
}

//Check si le fichier existe, si les droit sont dispo et ouvre le fichier

static int	open_file(char *file, t_data *data)
{
	int	fd;

	if (access(file, F_OK ) != -1) 
	{
        if (access(file, R_OK) == -1) 
			return (ft_putstr_fd("Error Pemission File\n", 2), 1);
    } 
	else 
		return (ft_putstr_fd("Error File not Found\n", 2), 1);
	fd = open(file, O_RDONLY);
	if (fd < 1)
		return (ft_putstr_fd("Error Failed to Open File\n", 2), 1);
	if (check_file(fd, data))
	{
		return (1);
	}
	return (0);
}

//Debut du parsing de la map

int complete_param(t_file *file)
{
	if (!file->path_to_e || !file->path_to_n || !file->path_to_s || !file->path_to_w)
		return (1);
	return (0);
}

static int	check_file(int fd, t_data *data)
{
	char	*line;
	
	data->head_file->map = NULL;
	data->head_file->path_to_n = NULL;
	data->head_file->path_to_s = NULL;
	data->head_file->path_to_e = NULL;
	data->head_file->path_to_w = NULL;
	data->head_file->color_floor = 0;
	data->head_file->color_sky = 0;
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
		{
			if (complete_param(data->head_file))
				return (ft_putstr_fd("Error Parameters\n", 2), 1);
			free(line);
			break;
		}
		if (fill_param(line, data->head_file))
			return (ft_putstr_fd("Error Parameters\n", 2), 1);
		free(line);
	}
	
	return (0);
}

