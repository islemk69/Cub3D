/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:43:07 by ccrottie          #+#    #+#             */
/*   Updated: 2023/10/01 19:09:23 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fill_tab(char const *s, char c, char *tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	tab = ft_calloc((i + 2), sizeof(char));
	if (!tab)
		return (NULL);
	while (j < i)
	{
		tab[j] = s[j];
		j++;
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_freeall(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**ft_alloc_tab(char const *s, char c, char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			tab[j] = ft_fill_tab(&s[i], c, tab[j]);
			if (!tab[j])
				return (ft_freeall(tab));
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**tab;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			j++;
		while (s[i] && s[i] != c)
			i++;
	}
	tab = malloc(sizeof(char *) * (j + 1));
	if (!tab)
		return (NULL);
	tab = ft_alloc_tab(s, c, tab);
	if (tab)
		tab[j] = NULL;
	return (tab);
}

