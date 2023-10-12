/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:41:21 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/10 14:36:20 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void init_struct(t_data *data)
{
	data->head_file = ft_calloc(1, sizeof(t_file));
	ft_bzero(data->head_file, sizeof(t_file));
	data->head_player = ft_calloc(1, sizeof(t_player));
	ft_bzero(data->head_player, sizeof(t_player));
	data->head_winmlx = ft_calloc(1, sizeof(t_winmlx));
	ft_bzero(data->head_winmlx, sizeof(t_winmlx));
	data->north_texture = ft_calloc(1, sizeof(t_texture));
	ft_bzero(data->north_texture, sizeof(t_texture));
	data->south_texture = ft_calloc(1, sizeof(t_texture));
	ft_bzero(data->south_texture, sizeof(t_texture));
	data->east_texture = ft_calloc(1, sizeof(t_texture));
	ft_bzero(data->east_texture, sizeof(t_texture));
	data->west_texture = ft_calloc(1, sizeof(t_texture));
	ft_bzero(data->west_texture, sizeof(t_texture));
	data->ciel_texture = ft_calloc(1, sizeof(t_texture));
	ft_bzero(data->ciel_texture, sizeof(t_texture));
}


int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_putstr_fd("Error Number of Args\n", 2), 1);
	init_struct(&data);
	if (parsing(argv[1], &data))
		return (free(data.head_file), 1);
	ft_init(data.head_winmlx, &data);
	// ft_free_tab(data.head_file->map);
	// free(data.head_file);
	// free(data.head_winmlx);
}
