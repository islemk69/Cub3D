/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:52:50 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/15 14:04:57 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	open_file(char *file, t_data *data, int flg);
static int	check_extention(char *path_file, char *extention);
static void	set_sky_and_floor_color(t_data *data);
static int	check_path(t_data *data);

int	parsing(char *file, t_data *data)
{
	if (check_extention(file, "buc.") || open_file(file, data, 1))
		return (1);
	if (parse_map(data->file))
		return (ft_putstr_fd("Error Map\n", 2), 1);
	set_sky_and_floor_color(data);
	if (check_path(data))
		return (ft_putstr_fd("Error path\n", 2), 1);
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

static void	set_sky_and_floor_color(t_data *data)
{
	int	r;
	int	g;
	int	b;

	r = data->file->color_sky[0];
	g = data->file->color_sky[1];
	b = data->file->color_sky[2];
	data->file->color_sky_hex = (r * 65536) + (g * 256) + b;
	r = data->file->color_floor[0];
	g = data->file->color_floor[1];
	b = data->file->color_floor[2];
	data->file->color_floor_hex = (r * 65536) + (g * 256) + b;
}

static int	check_path(t_data *data)
{
	if (open_file(data->file->path_to_e, data, 0) || \
	open_file(data->file->path_to_w, data, 0) || \
	open_file(data->file->path_to_s, data, 0) || \
	open_file(data->file->path_to_n, data, 0))
		return (1);
	return (0);
}
