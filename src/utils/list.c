/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:50:18 by ikaismou          #+#    #+#             */
/*   Updated: 2023/06/20 14:01:56 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// t_map	*lstlast(t_map *lst)
// {
// 	while (lst)
// 	{
// 		if (!lst->next)
// 			return (lst);
// 		lst = lst->next;
// 	}
// 	return (lst);
// }

// t_map	*create_cell(char *line)
// {
// 	t_map	*cell;

// 	cell = malloc(sizeof(t_map));
// 	if (!cell)
// 		return (cell);
// 	cell->line = line;
// 	return (cell);
// }

// void	ft_lstad_back(t_map **lst, t_map *new)
// {
// 	t_map	*last;

// 	if (lst)
// 	{
// 		if (*lst)
// 		{
// 			last = lstlast(*lst);
// 			last->next = new;
// 		}
// 		else
// 			*lst = new;
// 	}
// }

// int	lstsize(t_map *lst)
// {
// 	int		i;
// 	t_map	*cpy;

// 	cpy = lst;
// 	i = 0;
// 	while (cpy)
// 	{
// 		cpy = cpy->next;
// 		i++;
// 	}
// 	return (i);
// }

// void	lstclear(t_map **lst)
// {
// 	t_map	*tmp;

// 	if (lst)
// 	{
// 		while (*lst)
// 		{
// 			tmp = (*lst)->next;
// 			free(*lst);
// 			*lst = tmp;
// 		}
// 	}
// }