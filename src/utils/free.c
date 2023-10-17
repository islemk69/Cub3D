/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:55:37 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/16 16:15:06 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_file(t_file *file)
{
	if(file)
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
}

void	free_struct(t_data *data)
{
	if (data->file)
		free(data->file);
	if (data->winmlx)
	{
		free(data->winmlx);
	}
	if (data->player)
		free(data->player);
	if (data->scene)
		free(data->scene);
	if (data->ntex)
		free(data->ntex);
	if (data->stex)
		free(data->stex);
	if (data->wtex)
		free(data->wtex);
	if (data->etex)
		free(data->etex);
}

void	free_mlx(t_data *data, int flg)
{

	if (data->ntex && data->ntex->img)
		mlx_destroy_image(data->winmlx->mlx, data->ntex->img);
	if (data->stex && data->stex->img)
		mlx_destroy_image(data->winmlx->mlx, data->stex->img);
	if (data->wtex && data->wtex->img)
		mlx_destroy_image(data->winmlx->mlx, data->wtex->img);
	if (data->etex && data->etex->img)
		mlx_destroy_image(data->winmlx->mlx, data->etex->img);
	if (data->winmlx->img && flg)
		mlx_destroy_image(data->winmlx->mlx, data->winmlx->img);
	if (data->winmlx)
	{
		if (data->ntex && data->winmlx->mlx_win)
			mlx_destroy_window(data->winmlx->mlx, data->winmlx->mlx_win);
		if (data->ntex && data->winmlx->mlx)
			mlx_destroy_display(data->winmlx->mlx);
		if (data->winmlx->mlx)
			free(data->winmlx->mlx);
	}
}

void	ft_free_all(t_data *data, int flg)
{
	free_mlx(data, flg);
	free_file(data->file);
	free_struct(data);
}
