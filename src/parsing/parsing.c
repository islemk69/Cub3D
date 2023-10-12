/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:52:50 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/01 17:36:38 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_file(int fd, t_file *file);
static int	open_file(char *file, t_data *data);
static int	check_extention(char *path_file, char *extention);

int	parsing(char *file, t_data *data)
{	
	if (check_extention(file, "ebuc.") || open_file(file, data))
		return (1);
	if ( parse_map(data->head_file))
		return (ft_putstr_fd("Error Map\n", 2), 1);
	return (0);
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

static int	open_file(char *file, t_data *data)
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
	if (check_file(fd, data->head_file))
		return (1);
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
		if (line)
			free(line);
		line = get_next_line(fd);
		if (!line)
		{
			if (complete_param(file))
				return (ft_putstr_fd("Error Parameters\n", 2), 1);
			fill_map_tab(&listmap, file);
			return (free(line), lstclear(&listmap), 0);
		}
		if (flg)
		{
			if (line[0] == '\n')
				continue ;
			fill_struct_map(&listmap, line);
		}
		else if (fill_param(line, file, &flg))
			return (ft_putstr_fd("Error Parameters\n", 2), free(line),1);
	}
}
