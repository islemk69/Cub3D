/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:22:07 by ikaismou          #+#    #+#             */
/*   Updated: 2022/12/24 14:17:32 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(long long unsigned int nb, long long unsigned int taille,
		char	*base, int *len)
{
	if (nb > (taille - 1))
		ft_putnbr_base((nb / taille), taille, base, len);
	ft_putchar(base[nb % taille], len);
}

void	ft_putnbr(int nb, int *len)
{
	unsigned int	n;

	if (nb < 0)
	{
		ft_putchar('-', len);
		n = -nb;
	}
	else
		n = nb;
	return (ft_putnbr_base(n, 10, "0123456789", len));
}
