/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:14:57 by ikaismou          #+#    #+#             */
/*   Updated: 2022/11/16 11:13:22 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (ptr[i] != (unsigned char)c && i < n)
			i++;
		else
		{
			if ((i < n))
				return ((void *)(s + i));
		}
	}
	return (NULL);
}
