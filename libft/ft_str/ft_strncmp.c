/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blakehal <blakehal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:24:46 by blakehal          #+#    #+#             */
/*   Updated: 2022/11/12 14:33:46 by blakehal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_bis;
	unsigned char	*s2_bis;
	size_t			i;

	i = 0;
	s1_bis = (unsigned char *)s1;
	s2_bis = (unsigned char *)s2;
	while (i != n && (s1_bis[i] != '\0' || s2_bis[i] != '\0'))
	{
		if (s1_bis[i] != s2_bis[i])
		{
			return (s1_bis[i] - s2_bis[i]);
		}
		i++;
	}
	return (0);
}
