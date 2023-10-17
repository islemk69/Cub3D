/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:41:21 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/17 17:05:41 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_putstr_fd("Error Number of Args\n", 2), 1);
	if (init_struct(&data, 0))
		return (ft_free_all(&data, 0), 1);
	if (parsing(argv[1], &data))
		return (ft_free_all(&data, 1), 1);
	if (init_struct(&data, 1))
		return (ft_free_all(&data, 1), 1);
	if (init_game(data.winmlx, &data))
		return (ft_free_all(&data, 1), 1);
	return (0);
}
