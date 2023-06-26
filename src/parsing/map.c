/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:08:29 by ikaismou          #+#    #+#             */
/*   Updated: 2023/06/20 14:08:50 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    fill_struct_map(t_tmpmap **map, char *line)
{
    t_tmpmap *cell;
    cell = create_cell(line);  
    ft_lstad_back(map, cell);
}