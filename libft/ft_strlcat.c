/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:31:53 by ikaismou          #+#    #+#             */
/*   Updated: 2022/11/16 12:51:26 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncat(char	*dest, const char	*src, unsigned int nb)
{
	int	i;
	int	destlong;

	i = 0;
	destlong = ft_strlen(dest);
	while (src[i] && nb > 0)
	{
		dest[destlong + i] = src[i];
		i++;
		nb--;
	}
	dest[destlong + i] = 0;
	return (dest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;

	if (dstsize == 0)
		return (ft_strlen(src));
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	ft_strncat(dst, src, (dstsize - dstlen - 1));
	return (dstlen + srclen);
}
