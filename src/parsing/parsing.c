/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:52:50 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/15 18:03:42 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_file(int fd, t_file *file);
static int	open_file(char *file, t_data *data, int flg);
static int	check_extention(char *path_file, char *extention);
static void set_sky_and_floor_color(t_data *data);

int	check_path(t_data *data)
{
	if (open_file(data->file->path_to_e, data, 0) 
		|| open_file(data->file->path_to_w, data, 0)
		|| open_file(data->file->path_to_s, data, 0) 
		|| open_file(data->file->path_to_n, data, 0))
		return (1);
	return (0);
}

int	parsing(char *file, t_data *data)
{	
	if (check_extention(file, "ebuc.") || open_file(file, data, 1))
		return (1);
	if (parse_map(data->file))
		return (ft_putstr_fd("Error Map\n", 2), 1);
    set_sky_and_floor_color(data);
	if (check_path(data))
		return (ft_putstr_fd("Error path\n", 2), 1);
	return (0);
}

static   void set_sky_and_floor_color(t_data *data)
{
    int r;
    int g;
    int b;

    r = data->file->color_sky[0];
    g = data->file->color_sky[1];
    b = data->file->color_sky[2];
    data->file->color_sky_hex = (r * 65536) + (g * 256) + b;
    r = data->file->color_floor[0];
    g = data->file->color_floor[1];
    b = data->file->color_floor[2];
    data->file->color_floor_hex = (r * 65536) + (g * 256) + b;
}

//Fait un split sur '/' et check si il y a une seule extention et si celle 
//ci se finit par un .ber

static int	check_extention(char *path_file, char *extention)
{
	char	**tab;
	char	*file;

	tab = ft_split(path_file, '/');
	file = tab[ft_strlen_dtab(tab) - 1];
	while (*file)
		file++;
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

static int	open_file(char *file, t_data *data, int flg)
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

void ontest(char *line)
{
	printf("%s\n", line);
}

static int	check_file(int fd, t_file *file)
{
	char	*line;
	int		flg;

	flg = 0;
	line = NULL;
	t_tmpmap *listmap;
	listmap = NULL;
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
		{
			if (complete_param(file))
				return (free(line), ft_putstr_fd("Error Parameters\n", 2), 1);
			fill_map_tab(&listmap, file);
			return (free(line), lstclear(&listmap), 0);
		}
		if (flg)
		{
			if (line[0] == '\n')
			{
				free(line);
				continue ;
			}
			fill_struct_map(&listmap, line);
		}
		else if (param(line, file, &flg))
		{
			free(line);
			return (ft_putstr_fd("Error Parameters\n", 2) ,1);
		}
		free(line);
	}
}
