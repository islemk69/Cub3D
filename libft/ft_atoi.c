/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:45:48 by ikaismou          #+#    #+#             */
/*   Updated: 2022/11/19 10:32:52 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	overflow(int sign)
{
	if (sign == -1)
		return (0);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		if (!ft_isdigit(str[i + 1]))
			return (0);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result != (result * 10 + (str[i] - '0')) / 10)
			return ((int)overflow(sign));
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * sign);
}
