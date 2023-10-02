/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:41:21 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/02 13:16:50 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"



int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_putstr_fd("Error Number of Args\n", 2), 1);
	data.head_file = malloc(sizeof(t_file));
	if (parsing(argv[1], &data))
		return (free(data.head_file), 1);
	data.head_winmlx = malloc(sizeof(t_winmlx));
	int i = 0;
	while (data.head_file->map[i])
	{
		printf("%s\n", data.head_file->map[i]);
		i++;
	}
	ft_init(data.head_winmlx, &data);
	// ft_free_tab(data.head_file->map);
	// free(data.head_file);
	// free(data.head_winmlx);
}