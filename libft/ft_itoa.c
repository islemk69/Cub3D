/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:54:02 by ikaismou          #+#    #+#             */
/*   Updated: 2022/11/18 16:03:01 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	mallocsize(long n)
{
	int	cpt;

	cpt = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		cpt++;
	}
	while (n > 0)
	{
		n /= 10;
		cpt++;
	}
	return (cpt);
}

static char	*isequalzero(char *s)
{
	s[0] = 48;
	return (s);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*tab;
	long	nb;

	nb = n;
	i = mallocsize(nb);
	tab = (char *)malloc(sizeof(char) * i + 1);
	if (!tab)
		return (NULL);
	tab[i--] = '\0';
	if (nb == 0)
		return (isequalzero(tab));
	if (nb < 0)
	{
		tab[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		tab[i--] = (nb % 10) + 48;
		nb /= 10;
	}
	return (tab);
}
