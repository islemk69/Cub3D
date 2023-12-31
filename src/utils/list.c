/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:50:18 by ikaismou          #+#    #+#             */
/*   Updated: 2023/10/16 17:27:37 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_tmpmap	*lstlast(t_tmpmap *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_tmpmap	*create_cell(char *line)
{
	t_tmpmap	*cell;

	cell = malloc(sizeof(t_tmpmap));
	if (!cell)
		return (NULL);
	cell->line = ft_strdup(line);
	cell->next = NULL;
	return (cell);
}

void	ft_lstad_back(t_tmpmap **lst, t_tmpmap *new)
{
	t_tmpmap	*last;

	if (lst)
	{
		if (*lst)
		{
			last = lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

int	lstsize(t_tmpmap *lst)
{
	int			i;
	t_tmpmap	*cpy;

	cpy = lst;
	i = 0;
	while (cpy)
	{
		cpy = cpy->next;
		i++;
	}
	return (i);
}

void	lstclear(t_tmpmap **lst)
{
	t_tmpmap	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free((*lst)->line);
			free(*lst);
			*lst = tmp;
		}
	}
}
