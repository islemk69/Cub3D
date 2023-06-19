/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:33:24 by ikaismou          #+#    #+#             */
/*   Updated: 2022/11/18 16:03:37 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(const char *s, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == c || s[i] == '\0') == 0
			&& (s[i + 1] == c || s[i + 1] == '\0') == 1)
			j++;
		i++;
	}
	return (j + 1);
}

static char	**freemalloc( char **str, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free(str[i]);
		i++;
	}
	free (str);
	return (NULL);
}

static int	ft_sizeword(const char *s, char c, int index)
{
	int	count;

	count = 0;
	while (s[index])
	{
		if (s[index] == c)
			return (count + 1);
		index++;
		count++;
	}
	return (count + 1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	j = 0;
	tab = (char **)malloc(sizeof(char *) * ft_countword(s, c));
	if (!tab || !s)
		return (NULL);
	while (s[k] && i < ft_countword(s, c) - 1)
	{
		while (s[k] == c)
			k++;
		tab[i] = (char *)malloc(sizeof (char) * ft_sizeword(s, c, k));
		if (!tab[i])
			return (freemalloc(tab, i - 1));
		j = 0;
		while (s[k] && s[k] != c)
			tab[i][j++] = s[k++];
		tab[i++][j] = 0;
	}
	tab[i] = 0;
	return (tab);
}
