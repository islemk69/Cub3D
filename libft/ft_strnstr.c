/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:49:11 by ikaismou          #+#    #+#             */
/*   Updated: 2022/11/16 12:52:13 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	else if (len == 0)
		return (NULL);
	while (haystack[i] && i < len)
	{
		k = i;
		j = 0;
		while (haystack[i + j] == needle[j] && k < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)(haystack + i));
			j++;
			k++;
		}
		i++;
	}
	return (NULL);
}
