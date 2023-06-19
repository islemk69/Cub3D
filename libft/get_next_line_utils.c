/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:39:43 by ikaismou          #+#    #+#             */
/*   Updated: 2023/01/04 15:47:21 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*m;

	i = -1;
	j = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (free(s1), NULL);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (free(s1), (NULL));
	m = malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!m)
		return (free(s1), NULL);
	if (s1)
		while (s1[++i] != '\0')
			m[i] = s1[i];
	while (s2[j] != '\0')
		m[i++] = s2[j++];
	m[i] = '\0';
	return (free(s1), m);
}
