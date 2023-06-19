/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:20:21 by ikaismou          #+#    #+#             */
/*   Updated: 2022/11/26 14:56:31 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*m;

	i = 0;
	j = 0;
	m = malloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2))) + 1);
	if (!m || !s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		m[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		m[i] = s2[j];
		j++;
		i++;
	}
	m[i] = '\0';
	return (m);
}
