/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:52:50 by ikaismou          #+#    #+#             */
/*   Updated: 2023/06/28 17:36:20 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_file(int fd, t_data *data);
static int	open_file(char *file, t_data *data);
static int	check_extention(char *path_file, char *extention);

int	parsing(char *file, t_data *data)
{	
	if (check_extention(file, "ebuc.") || open_file(file, data))
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
	if (!file->path_to_e || !file->path_to_n || !file->path_to_s || !file->path_to_w || !file->color_f_tmp || !file->color_s_tmp)
		return (1);
	return (0);
}

void	init_struct_file(t_file *file)
{
	file->map = NULL;
	file->path_to_n = NULL;
	file->path_to_s = NULL;
	file->path_to_e = NULL;
	file->path_to_w = NULL;
	file->color_f_tmp = NULL;
	file->color_s_tmp = NULL;
	file->head_map = NULL;
}

void	fill_map_tab(t_tmpmap **list, t_file *file)
{
	printf("\n////////////////////////////////////////////////\n");
	printf("DEBUT DE LA MAP\n");
	printf("////////////////////////////////////////////////\n");
	t_tmpmap *head;
	t_tmpmap *salam;
	head = *list;
	salam = *list;
	int i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	file->map = malloc(sizeof(char **) * (i + 1));
	i = 0;
	while (salam)
	{
		file->map[i] = ft_strdup(salam->line);
		i++;
		salam = salam->next;
	}
	file->map[i] = 0;
	i = 0;
	while (file->map[i])
	{
		printf("%s", file->map[i]);
		i++;
	}
	printf("\n");
}

static int	check_file(int fd, t_data *data)
{
	char	*line;
	int		flg;
	
	flg = 0;
	init_struct_file(data->head_file);
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
		if (flg)
		{
			if (line[0] == '\n')
			{
				free(line);
				continue ;
			}
			fill_struct_map(&data->head_file->head_map, line);
		}
		else if (fill_param(line, data->head_file, &flg))
				return (ft_putstr_fd("Error Parameters\n", 2), 1);
		free(line);
	}
	fill_map_tab(&data->head_file->head_map, data->head_file);
	return (0);
}

