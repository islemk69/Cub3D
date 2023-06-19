/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:29:26 by ikaismou          #+#    #+#             */
/*   Updated: 2022/11/18 16:04:02 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	begin(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j] && set[j] != s1[i])
			j++;
		if (set[j] == 0)
			break ;
		i++;
	}
	return (i);
}

static int	last(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
		i++;
	i--;
	while (i > 0)
	{
		j = 0;
		while (set[j] && set[j] != s1[i])
			j++;
		if (set[j] == 0)
			break ;
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;
	int	length1;

	start = begin(s1, set);
	end = last(s1, set) + 1;
	length1 = end - start;
	return (ft_substr(s1, start, length1));
}
