/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:55:37 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/15 17:12:24 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_file(t_file *file)
{
	if (file->map)
		ft_free_tab(file->map);
	if (file->path_to_n)
		free(file->path_to_n);
	if (file->path_to_s)
		free(file->path_to_s);
	if (file->path_to_e)
		free(file->path_to_e);
	if (file->path_to_w)
		free(file->path_to_w);

}

void	free_struct(t_data *data)
{
	if(data->file)
		free(data->file);
	if(data->winmlx)
	{
		free(data->winmlx->mlx);
		free(data->winmlx);
	}
	if(data->player)
		free(data->player);
	if(data->scene)
		free(data->scene);
	if(data->ntex)
		free(data->ntex);
	if(data->stex)
		free(data->stex);
	if(data->wtex)
		free(data->wtex);
	if(data->etex)
		free(data->etex);
}

void	ft_free_all(t_data *data)
{
	free_file(data->file);
	free_struct(data);
}