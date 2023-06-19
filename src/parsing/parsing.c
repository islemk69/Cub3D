/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:52:50 by ikaismou          #+#    #+#             */
/*   Updated: 2023/06/19 16:58:33 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_file(int fd);
static int	open_file(char *file);
static int	check_extention(char *path_file, char *extention);

int	parsing(char *file)
{	
	if (check_extention(file, "reb.") || open_file(file))
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

static int	open_file(char *file)
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
	check_file(fd);
	return (0);
}

//Debut du parsing de la map

static int	check_file(int fd)
{
	char	*line;

	while (42)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			break;
		}
		printf("line : %s\n", line);
		free(line);
	}
	return (0);
}